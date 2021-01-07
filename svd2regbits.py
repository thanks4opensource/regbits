#!/usr/bin/env python3

# regbits: C++ templates for type-safe bit manipulation
# Copyright (C) 2020, 2021 Mark R. Rubin
#
# This file is part of regbits.
#
# The regbits program is free software: you can redistribute it
# and/or modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation, either version 3 of
# the License, or (at your option) any later version.
#
# The regbits program is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# (LICENSE.txt) along with the regbits program. If not, see
# <https://www.gnu.org/licenses/gpl.html>


#!/usr/bin/env python3

import argparse
import pprint # DEBUG
import os
import re
import sys


#
# Constants
#

VERSION = (0, 1, 2)

FIX_BAD_CHARS = {
    i :      i
        if   chr(i) in
             '0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz'
        else None
        for i in range(256) }




#
# Boilerplates
#

COPYRIGHT = '''%s %d.%d.%d
Copyright 2020 Mark R. Rubin aka "thanks4opensource"''' \
% (os.path.basename(sys.argv[0]), *VERSION)



HEADER = '''// Created by svd2regbits.py, version {ver}
// using Python XML module: {xml_lib}
//
// Source file: {svd_file}
// Device name: {mcu}
// SVD version: {svd_vers}
// description: {svd_desc}

#ifndef {upper}_HXX
#define {upper}_HXX

#include <stdint.h>

#include <regbits.hxx>


#if REGBITS_MAJOR_VERSION != 1
#error REGBITS_MAJOR_VERSION != 1
#endif

#if REGBITS_MINOR_VERSION < 1
#error REGBITS_MAJOR_VERSION == 1 but REGBITS_MINOR_VERSION < 1
#endif

#define {upper}_MAJOR_VERSION   {maj}
#define {upper}_MINOR_VERSION   {min}
#define {upper}_MICRO_VERSION   {mcr}



namespace {lower} {{

using namespace regbits;

'''



PERIPH_DEFINE_0 = '\n\n\n'
PERIPH_DEFINE_1 = "#define {upper}_PERIPH(TYPE, PERIPH, BASE)        \\\n"
PERIPH_DEFINE_2 = "    static volatile TYPE* const                     \\\n"
PERIPH_DEFINE_3 = "    PERIPH = reinterpret_cast<volatile TYPE*>(BASE)\n\n"
PERIPH_DEFINE   =   PERIPH_DEFINE_0 \
                  + PERIPH_DEFINE_1 \
                  + PERIPH_DEFINE_2 \
                  + PERIPH_DEFINE_3

PERIPH_UNDEF = "\n#undef {upper}_PERIPH\n"


ARM_NVIC_HEADER = '''

namespace arm {
enum class NvicIrqn {
''' + "    // ARM IRQs\n"

ARM_IRQS = (
    ('Reset'        , -15),
    ('NMI'          , -14),
    ('HardFault'    , -13),
    ('MemManage'    , -12),
    ('BusFault'     , -11),
    ('UsageFault'   , -10),
    ('Reserved1'    ,  -9),
    ('Reserved2'    ,  -8),
    ('Reserved3'    ,  -7),
    ('Reserved4'    ,  -6),
    ('SVCall'       ,  -5),
    ('Debug'        ,  -4),
    ('Reserved5'    ,  -3),
    ('PendSV'       ,  -2),
    ('SysTick'      ,  -1),
)

ARM_IRQ_NAMES = [irq[0] for irq in ARM_IRQS]

ARM_NVIC_FOOTER = '''}; // enum NvicIrqn
}  // namespace arm
'''



FOOTER = '''
}}  // namespace {mcu}

#endif  // #ifndef {upper}_HXX
'''




#
# Utils
#

def import_xml_lib(lib, fail_ok=False):
    global ET
    LIBS = ('xml', 'lxml', 'defusedxml', 'BeautifulSoup')
    if lib == 'auto':
        for lib in LIBS:
            if import_xml_lib(lib, fail_ok=True):
                return lib
        sys.stderr.write("Failed to import any of %s\n" % LIBS)
        return None
    try:
        if lib == 'xml':
            import xml.etree.ElementTree as ET
        elif lib == 'lxml':
            import lxml.etree as ET
        elif lib == 'defusedxml':
            import defusedxml.cElementTree as ET
        elif lib == 'BeautifulSoup':
            import BeautifulSoup as ET
        else:
            raise ImportError("Unknown xml parsing library \"%s\"" % lib)
    except ImportError as error:
        if fail_ok:
            return False
        else:
            sys.stderr.write("Import of %s lib failed: %s\n" % (lib, error))
            sys.exit(1)
    return lib



def get_enumerated_values(register, field):
    while True:
        if field is None:
            return None
        values = field.find('enumeratedValues')
        if values is None:
            return None
        derived_from = values.get('derivedFrom')
        if not derived_from:
            return values
        if '.' in derived_from:
            sys.stderr.write(  "Current version can't handle "
                               "<field><name>%s</name> "
                               "<enumeratedValues derivedFrom=\"%s\" /> "
                               "from different field/register/peripheral\n"
                             % (find_text(field, 'name'),
                                derived_from            )                  )
            return values
        field = register.find("./fields/field/[name='%s']" % derived_from)


def derived_from_by_name(root, node, element_type, child_name):
    # if root is None or node is None:
    #   return None
    child = node.find(child_name   )
    dfrm  = node.get ('derivedFrom')
    while child is None and dfrm is not None and node is not None:
        node  = root.find("./%s/[name='%s']" % (element_type, dfrm))
        if node is not None:
            dfrm  = node.get ('derivedFrom')
            child = node.find(child_name   )
    return child


def derived_from_stop_tag(root, element, element_type, stop_tag):
    while True:
        dfrm_name = element.get('derivedFrom')
        if not dfrm_name:
            return element
        if any([child.tag == stop_tag for child in element.iterfind('*')]):
            sys.stderr.write(  "Element %s of %s has derivedFrom=\"%s\" "
                               "but one of %s is in %s. Current converter "
                               "can't handle modified \"derivedFrom\", only "
                               "unmodified clones.\n"
                             % (find_text(element, 'name')            ,
                                root.tag                              ,
                                dfrm_name                             ,
                                [e.tag for e in element.iterfind('*')],
                                str(clone_tags)                       )        )
            # go all the way to most-derived element
            # return element
        dfrm = root.find("%s/[name='%s']" % (element_type, dfrm_name))
        if dfrm is None:
            sys.stderr.write(  "Can't find %s, <derivedFrom> of %s\n"
                             % (dfrm_name, find_text(element, 'name')))
            return element
        else:
            element = dfrm



def find_text(xml, name):
    found = xml.find(name)
    if found is None:
        return ''
    text = found.text
    if text is None:
        return  ''
    else:
        return text



def fixname(name):
    if not name:
        return name
    if name[0] in '0123456789':
        name = '_' + name
    if name.lower() in ('alignas',
                        'alignof',
                        'and',
                        'and_eq',
                        'asm',
                        'atomic_cancel',
                        'atomic_commit',
                        'atomic_noexcept',
                        'auto',
                        'bitand',
                        'bitor',
                        'bits',         # regbits
                        'bool',
                        'break',
                        'case',
                        'catch',
                        'char',
                        'char8',
                        'char16',
                        'char32',
                        'char64',
                        'char8_t',
                        'char16_t',
                        'char32_t',
                        'char64_t',
                        'class',
                        'compl',
                        'concept',
                        'const',
                        'consteval',
                        'constexpr',
                        'constinit',
                        'const_cast',
                        'continue',
                        'co_await',
                        'co_return',
                        'co_yield',
                        'decltype',
                        'default',
                        'delete',
                        'do',
                        'double',
                        'dynamic_cast',
                        'else',
                        'enum',
                        'explicit',
                        'export',
                        'extern',
                        'false',
                        'float',
                        'for',
                        'friend',
                        'goto',
                        'if',
                        'inline',
                        'int',
                        'int8_t',
                        'int16_t',
                        'int32_t',
                        'int64_t',
                        'long',
                        'mutable',
                        'mskd',         # regbits
                        'namespace',
                        'new',
                        'noexcept',
                        'not',
                        'not_eq',
                        'nullptr',
                        'operator',
                        'or',
                        'or_eq',
                        'pos',          # regbits
                        'private',
                        'protected',
                        'public',
                        'reflexpr',
                        'reg',          # regbits
                        'register',
                        'reinterpret_cast',
                        'requires',
                        'return',
                        'short',
                        'signed',
                        'sizeof',
                        'static',
                        'static_assert',
                        'static_cast',
                        'struct',
                        'switch',
                        'synchronized',
                        'template',
                        'this',
                        'thread_local',
                        'throw',
                        'true',
                        'try',
                        'typedef',
                        'typeid',
                        'typename',
                        'uchar',
                        'uchar_t',
                        'uchar8_t',
                        'uchar16_t',
                        'uchar32_t',
                        'uchar64_t',
                        'union',
                        'unsigned',
                        'using',
                        'uint',
                        'uint8_t',
                        'uint16_t',
                        'uint32_t',
                        'uint64_t',
                        'virtual',
                        'void',
                        'volatile',
                        'wchar',
                        'wchar_t',
                        'wchar8_t',
                        'wchar16_t',
                        'wchar32_t',
                        'wchar64_t',
                        'wuchar',
                        'wuchar_t',
                        'wuchar8_t',
                        'wuchar16_t',
                        'wuchar32_t',
                        'wuchar64_t',
                        'while',
                        'xor',
                        'xor_eq'): name = '_' + name
    name = name.translate(FIX_BAD_CHARS)
    return name



def remove_name_dim(name):
    name = name.replace('[%s]', '')
    name = name.replace( '%s' , '')
    return name


def snakecase(name):
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', name)


def camelcase(text):
    # Can't use .title() because messes up already camelcased strings
    text = snakecase(text)   # so will keep already camelcased
    # Don't remove underscore before digit(s): Replace '_' before digit(s)
    #   with '__' so camelcasing will leave one '_'
    text = re.sub('(_[0-9])', '_\\1', text)
    cced = ''.join([    s[0].upper() + s[1:].lower()
                        if   len(s) > 1
                        else s.upper()
                        if   len(s) > 0
                        else '_'
                    for s
                    in  text.split('_')     ])
    return cced


def get_struct_name(element):
    name = find_text(element, 'headerStructName')
    if not name:
        name = find_text(element, 'name')
    return camelcase(fixname(remove_name_dim(name)))


def despace(text):
    return " " .join(text.split())


def linebreak(outfile             ,
             indent               ,
             text                 ,
             extra_indent    =0   ,   # for field descriptions
             first_indent    =True,   # for interrupt descriptions
             strip_whitespace=True,   # SVD descriptions indented to <xxx>
             pad_first       =None):  # <field> description alignment
    spaces = " " * indent
    extra  = ''
    width  = hxx_width - (indent + 3)   # "// "
    first  = True
    if strip_whitespace and not opts.newlines:
        text = " ".join(text.split())
    if pad_first:
        space = text.find(" ")
        text  = "%s %s" % (text[:space].ljust(pad_first), text[space:])
    if opts.newlines:
        extra_indent -= 2
        if extra_indent < 0: extra_indent = 0
    for line in text.split('\n'):
        if first and not first_indent:
            saved  = spaces
            spaces = ''
        if not line:
            outfile.write("%s//\n" % spaces)
        while line:
            line  = line.strip()
            split = len(line)
            space = -1
            while split > width:
                space = line[:split].rfind(" ")
                if space is -1:
                    break
                split = space
            outfile.write("%s// %s%s\n" % (spaces, extra, line[:split]))
            if extra == '':
                extra  = " " * extra_indent
                width -=       extra_indent
            line   = line[split:].strip()
            if first:
                if not first_indent: spaces = saved
                first = False



def print_rbar(outfile, indent, rbar):
    if not rbar:
        return
    spaces = " " * indent
    if indent + len(rbar) <= hxx_width:
        outfile.write('%s%s\n' % (spaces, rbar))
    else:
        lines = rbar.split(',')
        outfile.write('%s%s,\n' % (spaces, lines[0].strip()))
        # len('REGBITS_ARRAY_RANGE(') == 20
        spaces = " " * (indent + 20)
        for line in lines[1:-1]:
            outfile.write('%s%s,\n' % (spaces, line.strip()))
        outfile.write('%s%s\n' % (spaces, lines[-1].strip()))



def parse_int(text):
    if not text:
        return 0
    try:
        if   len(text) == 1:  return int(text    )
        elif text[1] in 'Xx': return int(text, 16)
        else:                 return int(text    )
    except ValueError as error:
        sys.stderr.write("Can't parse number \"%s\": %s\n" % (text, error))
        return 0



def expand_dim_index(dim_index, location):
    dims = []
    toks = dim_index.split(',')
    for tok in toks:
        if '-' in tok:
            try:
                (beg, end) = map(int, tok.split('-'))
            except:
                sys.stderr.write(  "Can't parse \"%s\" in "
                                   "dimIndex \"%s\" %s"
                                 % (tok, dim_index, location))
            for num in range(beg, end + 1):
                dims.append(num)
        else:
            dims.append(tok)
    return dims



def indent(outfile, indent, text):
    outfile.write("%s%s" % (" " * indent, text))



def print_element(outfile, element, indentation):
    if element is not None:
        indent(outfile,
               indentation,
               "%s: %s\n" % (element.tag, despace(element.text)))


def do_padding(outfile        ,
               periph_in_svd  ,
               periph_size    ,
               register_name  ,
               register_size  ,
               register_offset,
               padding_number ,
               indentation    ):
    bad_address = None
    if register_size == 16 and register_offset & 0x1:
        bad_address      = register_offset
        register_offset &= ~0x1
    elif register_size == 32 and register_offset & 0x3 != 0:
        bad_address     =  register_offset
        register_offset &= ~0x3
    elif register_size == 64 and register_offset & 0x7 != 0:
        bad_address     =  register_offset
        register_offset &= ~0x7
    if bad_address:
        sys.stderr.write(  "Register %s in peripheral %s, size %d "
                           "bits at unaligned addressOffset %d==0x%x -- "
                           "changed to %d==0x%x\n"
                         % (register_name  ,
                            periph_in_svd  ,
                            register_size  ,
                            bad_address    ,
                            bad_address    ,
                            register_offset,
                            register_offset)                    )
    needed = register_offset - periph_size
    if needed < 0:
        sys.stderr.write(  "Peripheral %s size already %d==0x%x, "
                           "register %s addressOffset %d==0x%x\n"
                         % (periph_in_svd  ,
                            periph_size    ,
                            periph_size    ,
                            register_name  ,
                            register_offset,
                            register_offset)                      )
        return (periph_size, padding_number)
    elif needed > 0:
        outfile.write(  "\n%sprivate: uint8_t padding_%d"
                      % (" " * indentation, padding_number))
        padding_number += 1
        if needed > 1:
            outfile.write('[%d]; public:\n\n' % needed)
        else:
            outfile.write('; public:\n\n')
    return (register_offset, padding_number)



def register_finish(ancestors, struct_name, struct_bytes, datatype, array_size):
    if array_size > 1:
        msk = opts.align[1] - 1
        if   struct_bytes == 1: struct_bytes = 1
        elif struct_bytes == 2: struct_bytes = 2
        else                  : struct_bytes = (struct_bytes + msk) & ~msk;
        if datatype.startswith('uint'):
            declaration = "%s_%s[%d];" % (datatype.ljust(12) ,
                                          struct_name.lower(),
                                          array_size         )
        else:
            declaration = "%s   _%s[%d];" % (datatype           ,
                                             struct_name.lower(),
                                             array_size         )
        regbits_array_range =   "REGBITS_ARRAY_RANGE(%s::%s, %s, %s, "  \
                                "%s, _%s, %s)"                      \
                              % (ancestors          ,
                                 struct_name        ,
                                 struct_name.upper(),
                                 struct_name.lower(),
                                 datatype           ,
                                 struct_name.lower(),
                                 array_size         )
        total_size = ((struct_bytes * array_size) + 0x3) & ~0x3
        return ((declaration, regbits_array_range), total_size)
    else:
        msk = opts.align[0] - 1
        if   struct_bytes == 1: struct_bytes = 1
        elif struct_bytes == 2: struct_bytes = 2
        else                  : struct_bytes = (struct_bytes + msk) & ~msk;
        regbits_array_range = None
        if datatype.startswith('uint'):
            declaration = "%s%s;" % (datatype.ljust(12) ,struct_name.lower())
        else:
            declaration = "%s   %s;" % (datatype, struct_name.lower())
        return ((declaration, regbits_array_range), struct_bytes)



def pod_instead(outfile        ,
                periph_struct  ,
                register_struct,
                register_size  ,
                array_size     ):
    if register_size not in (8, 16, 32, 64):
        sys.stdout.write(  "WARNING: Cannot handle register size %d in "
                           "peripheral=%s register=%s -- skipping\n"
                         % (register_size, periph_struct, register_object))
        return
    pass
    return register_finish(periph_struct             ,
                           register_struct           ,
                           register_size // 8        ,
                           'uint%d_t' % register_size,
                           array_size                )



def do_register(outfile      ,
                indentation  ,
                periph_struct,
                register     ,
                register_name,
                register_size,
                array_size   ):
    register_struct = camelcase(register_name)
    register_object = register_name.lower()
    register_type   = register_object + '_t'
    register_desc   = find_text(register, 'description')

    if 'reg' in opts.debug:
        sys.stdout.write(  "periph %s with %s, %s, %s  %d,%d  \"%s\"\n"
                         % (periph_struct  ,
                            register_struct,
                            register_object,
                            register_type  ,
                            register_size  ,
                            array_size     ,
                            register_desc  )                           )

    fields = register.find('fields')
    if 'reg' in opts.debug:
        sys.stdout.write(  "%d fields\n"
                         % (-1 if fields is None else len(fields)))
    if fields is None or len(fields) == 0:
        return pod_instead(outfile        ,
                           periph_struct  ,
                           register_struct,   # register_object,
                           register_size  ,
                           array_size     )

    poses = {}
    offss = {}
    descs = {}
    bitss = {}
    mskds = {}
    valus = {}
    for field in fields.findall('field'):
        name = snakecase(find_text(field, 'name')).upper()
        if not name:
            sys.stderr.write(  "Field with missing name in peripheral "
                               "%s, register %s -- skipping\n"
                             % (periph_struct, register_name)          )
            continue
        dim        = parse_int(find_text(field, 'dim'         ))
        dim_incr   = parse_int(find_text(field, 'dimIncrement'))
        dim_index  =           find_text(field, 'dimIndex'    )
        if dim_incr <= 0: dim_incr = 1
        if '%' in name:
            name = name.replace('%S', '%s')  # upper() made uppercase
            if not dim:
                dim = 1   # for safety, shouldn't happen
            if dim_index:
                msg  =   "in peripheral %s, register %s, field %s" \
                       % (periph_struct, register_struct, name)
                dims = expand_dim_index(dim_index, msg)
            else:
                dims = tuple(range(0, dim * dim_incr, dim_incr))
            names     = []
            begs_wids = []
            for (ndx, dim) in enumerate(dims):
                names    .append(fixname(name % dim))
                begs_wids.append((ndx * dim_incr, dim_incr))
        else:
            names      = (fixname(name),)
            begin      = None
            width      = None
            bit_range  = field.find('bitRange' )
            bit_offset = field.find('bitOffset')
            bit_width  = field.find('bitWidth' )
            msb        = field.find('msb'      )
            lsb        = field.find('lsb'      )
            if bit_range is not None:
                (lft, rgt) = map(int, bit_range.text[1:-1].split(':'))
                begin      = rgt
                width      = 1 + lft - rgt
            elif not None in (bit_offset, bit_width):
                begin = int(bit_offset.text)
                width = int(bit_width .text)
            elif not None in (msb, lsb):
                begin = int(lsb.text)
                width = int(msb.text) - begin + 1
            if None in (begin, width):
                sys.stderr.write(  "peripheral %s, register %s, field %s: "
                                   "No bitRange or bitOffset+bitWidth -- "
                                   "skipping\n"
                                 % (periph_struct, register_struct, name)  )
                continue
            begs_wids = ((begin, width),)

        description = find_text(field, 'description')
        for (name, (begin, width)) in zip(names, begs_wids):
            # safety: have seen duplicate plain (not "%"/dim) names
            if name in poses:
                suffix  = 1
                orig    = name
                while name in poses:
                    name    = orig + str(suffix)
                    suffix += 1
            offss.setdefault(begin, [])
            offss[begin].append(name)
            poses[name ] = (begin, width)
            descs[name ] = description
            if width == 1:
                bitss[begin] = name
            else:
                mskds[begin] = name
            valus[name] = []
            # values = field.find('enumeratedValues')
            values = get_enumerated_values(register, field)
            if values is not None:
                if not begin in mskds:  # enumeratedValues for single bit fields
                    mskds[begin] = name
                for value in values.findall('enumeratedValue'):
                    base = fixname(snakecase(find_text(value, 'name'))).upper()
                    if not base:
                        sys.stderr.write(  "Peripheral %s, register %s: "
                                           "<enueratedValue> without <name> "
                                           "-- skipping\n"
                                         % (periph_struct, register_name)    )
                        continue
                    valu = find_text(value, 'value')
                    if not value:
                        sys.stderr.write(  "Peripheral %s, register %s: "
                                           "<enueratedValue> \"%s\" without "
                                           "<value> -- skipping\n"
                                         % (periph_struct, register_name, base))
                        continue
                    desc = find_text(value, 'description')
                    if base == "MASK": base = "MASK_MASK"  # dupe of uint32_t
                    if valu:                 valu = valu.lower()  # "X" and "b"
                    else:                    valu = '0'
                    if valu.startswith('#'): valu = '0b' + valu[1:]
                    if valu.startswith('0b') and 'x' in valu:
                        # both versions of "don't care" bits
                        # for self-documentation: not really needed,
                        #   (could just use zeros) and certainly
                        #   no need for all possible permutations
                        valus[name].append((valu.replace('x', '0'),
                                            base + '_0'           ,
                                            desc                  ))
                        valus[name].append((valu.replace('x', '1'),
                                            base + '_1'           ,
                                            desc                  ))
                    else:
                        valus[name].append((valu, base, desc))

    if 'reg' in opts.debug:
        sys.stdout.write('poses:\n'); pprint.pprint(poses)
        sys.stdout.write('offss:\n'); pprint.pprint(offss)
        sys.stdout.write('descs:\n'); pprint.pprint(descs)
        sys.stdout.write('bitss:\n'); pprint.pprint(bitss)
        sys.stdout.write('mskds:\n'); pprint.pprint(mskds)
        sys.stdout.write('valus:\n'); pprint.pprint(valus)

    # maybe make uintN_t instead of struct with poses,bitss,mskds, etc
    if     len(offss)            == 1               \
       and 0                     in offss           \
       and len  (offss[0])       == 1               \
       and poses[offss[0][0]][1] == register_size   \
       and not values                            :
        return pod_instead(outfile        ,
                           periph_struct  ,
                           register_struct,   # register_object,
                           register_size  ,
                           array_size     )

    # wait until now because pod gets with definition
    outfile.write('\n')
    if register_desc:
        linebreak(outfile, indentation, register_desc)
    indent(outfile, indentation, 'struct %s {\n' % register_struct)

    max_width = max([len(name) for name in poses.keys()])

    had_offset_desc = False
    for offs in sorted(offss.keys()):
        for name in offss[offs]:
            if descs[name] is not None:
                name_desc = "%s %s" % (name, descs[name])
                linebreak(outfile                   ,
                          indentation + 4           ,
                          name_desc                 ,
                          extra_indent=max_width + 4,
                          pad_first=max_width       )
                had_offset_desc = True
    if had_offset_desc: outfile.write('\n')

    indent(outfile                                            ,
           indentation + 4                                    ,
             "using              pos_t = Pos<uint%d_t, %s>;\n"
           % (register_size, register_struct)                 )
    indent(outfile, indentation + 4, "static constexpr   pos_t")
    first = True
    for offs in sorted(offss.keys()):
        for name in offss[offs]:
            if first:
                outfile.write('\n')
                first = False
            else:
                outfile.write(',\n')
            name += '_POS'
            indent(outfile                           ,
                     indentation + 4                 ,
                     "%-16s = pos_t(%2d)"
                   % (name.rjust(max_width + 4), offs))
    outfile.write(';\n')

    if bitss:
        max_width = max([len(name) for name in bitss.values()])
        ndx       = 0
        first     = True
        for offs in sorted(offss.keys()):
            for bit_name in offss[offs]:
                if bit_name not in bitss.values():
                    continue
                if first:
                    outfile.write('\n')
                    indent(outfile                           ,
                           indentation                       ,
                             "    using              "
                             "bits_t = Bits<uint%d_t, %s>;\n"
                           % (register_size, register_struct))
                    indent(outfile                      ,
                           indentation + 4              ,
                           "static constexpr   bits_t\n")
                    first = False
                else:
                    outfile.write(',\n')
                pos_name = bit_name + '_POS'
                indent(outfile                          ,
                       indentation + 4                  ,
                         "%s = bits_t(1, %s)"
                       % (bit_name.ljust(16)           ,
                          pos_name.rjust(max_width + 4)))
                ndx += 1
        if not first: outfile.write(';\n')

    if mskds:
        max_width = max([len(item[1]) for item in mskds.items()])
        enums     = []  # mskd_ts with less than max_mskd values (explicit each)
        rangs     = []  #    "     "   more (use REGBITS_MSKD_RANGE)
        outfile.write('\n')
        first = True
        for offs in sorted(offss.keys()):
            for name in offss[offs]:
                (begin, width) = poses[name]
                if begin in mskds and width > 1 or valus[name]:
                    if first:
                        indent(outfile                                  ,
                               indentation + 4                          ,
                               "static const uint%d_t\n" % register_size)
                        first = False
                    else:
                        outfile.write(',\n')
                    indent(outfile                                    ,
                           indentation + 4                            ,
                             "%s_MASK = 0x%08x"
                           % (name.rjust(max_width), (1 << width) - 1))
                    if width < opts.max_mskd or valus[name]:
                        enums.append(name)
                    else:
                        rangs.append(name)
        if not first:
            outfile.write(';\n')

        outfile.write('\n')
        indent(outfile                                               ,
               indentation + 4                                       ,
                 "using               mskd_t = Mskd<uint%d_t, %s>;\n"
               % (register_size, register_struct)                    )
        indent(outfile                                               ,
               indentation + 4                                       ,
                 "using               shft_t = Shft<uint%d_t, %s>;\n"
               % (register_size, register_struct)                    )

        if enums:
            outfile.write('\n')
            first       = True
            mskd_valus  = set()
            valu_pad = max([         max([len(val[0]) for val in vals])
                                if   vals
                                else 0
                            for vals
                            in  valus.values()                          ])
            valu_pad = max(valu_pad, opts.max_mskd + 2)
            max_name = 0
            for valu in valus:
                mskd_len = len(valu)
                if valus[valu]:
                    mskd_len += max([len(val[1]) for val in valus[valu]])
                if mskd_len > max_name: max_name = mskd_len
            for offs in sorted(offss.keys()):
                for mskd_name in offss[offs]:
                    if not mskd_name in enums:
                        continue
                    pos_name = mskd_name + '_POS'
                    for valu in valus[mskd_name]:
                        if first:
                            indent(outfile                       ,
                                   indentation + 4               ,
                                   "static constexpr    mskd_t\n")
                            first = False
                        else:
                            outfile.write(',\n')
                        if valu[2]:
                            linebreak(outfile       ,
                                     indentation + 4,
                                     valu[2]        )
                        mskd_valu = '%s_%s' % (mskd_name, valu[1])
                        if mskd_valu in mskd_valus:
                            plain  = mskd_valu
                            undupe = 1
                            while mskd_valu in mskd_valus:
                                mskd_valu = '%s_%d' % (plain, undupe)
                                undupe += 1
                        mskd_valus.add(mskd_valu)
                        indent(outfile                             ,
                               indentation + 4                     ,
                                 "%s = mskd_t(%s_MASK, %2s, %s)"
                               % (mskd_valu.ljust(max_name  + 1),
                                  mskd_name.rjust(max_width    ),
                                  valu[0]  .ljust(valu_pad     ),
                                  pos_name .rjust(max_width + 4)))
                    if valus[mskd_name]:
                        continue   # had "enumeratedValues" in SVD
                    # else generate numeric names for all field values
                    for enum in range(1 << poses[mskd_name][1]):
                        if first:
                            indent(outfile                       ,
                                   indentation + 4               ,
                                   "static constexpr    mskd_t\n")
                            first = False
                        else:
                            outfile.write(',\n')
                        indent(outfile                              ,
                               indentation + 4                      ,
                                 "%s = mskd_t(%s_MASK, %s, %s)"
                               % ( ('%s_%02d' % (mskd_name, enum))
                                  .ljust(max_name + 1)           ,
                                  mskd_name.rjust(max_width     ),
                                  ('0x%x' % enum).ljust(valu_pad),
                                  pos_name.rjust(max_width  + 4 )))
            if not first:
                outfile.write(';\n')

        if rangs:
            outfile.write('\n')
            for offs in sorted(offss.keys()):
                for mskd_name in offss[offs]:
                    if not mskd_name in rangs:
                        continue
                    constexpr = mskd_name.upper()
                    runtime   = mskd_name.lower()
                    if mskd_name.lower() in ('pos', 'bits', 'mskd'):
                        constexpr += '_FUNC'
                        runtime   += '_func'
                    if constexpr == register_struct:
                        constexpr += '_'
                    if register_size <= opts.unsigned_width:
                        indent(outfile                            ,
                               indentation + 4                    ,
                                 "REGBITS_MSKD_RANGE(\"%s:%s\",\n"
                               % (periph_struct, register_struct) )
                    else:
                        indent(outfile                            ,
                               indentation + 4                    ,
                                 "REGBITS_MSKD_UNSGN(\"%s:%s\",\n"
                               % (periph_struct, register_struct) )
                        indent(outfile                      ,
                               indentation + 23             ,
                               "uint%d_t,\n" % register_size)
                    indent(outfile, indentation + 23, "%s,\n"      % constexpr)
                    indent(outfile, indentation + 23, "%s,\n"      % runtime  )
                    indent(outfile, indentation + 23, "%s_MASK,\n" % mskd_name)
                    indent(outfile, indentation + 23, "%s_POS,\n"  % mskd_name)
                    indent(outfile, indentation + 23, "%s_MASK)\n" % mskd_name)

    indent(outfile, indentation, "};  // struct %s\n" % register_struct)
    indent(outfile, indentation,   "using %s = Reg<uint%d_t, %s>;\n"
                                 % (register_type,
                                    register_size,
                                    register_struct)                    )

    return register_finish(periph_struct     ,
                           register_struct   ,
                           register_size // 8,
                           register_type     ,
                           array_size        )



def do_cluster(outfile       ,
               indentation   ,
               periph_in_svd ,
               periph_struct ,
               periph_size   ,
               padding_number,
               cluster       ,
               cluster_struct,
               cluster_dim   ,
               is_peripheral ,
               registers     ,
               default_size  ,
               dim_increment ):

    if cluster_struct != periph_struct:
        outfile.write('\n\n')

    cluster_desc = find_text(cluster, 'description')
    if cluster_desc:
        linebreak(outfile, indentation, cluster_desc)
        del cluster_desc

    indent(outfile, indentation, "struct %s {" % cluster_struct)
    if is_peripheral: outfile.write('\n'             )
    else:             outfile.write("   // cluster\n")

    indentation += 4

    cluster_dflt = parse_int(find_text(cluster,'size'))
    if cluster_dflt:
        default_size = cluster_dflt
        del cluster_dflt

    if registers is None:
        # can only happen when called with peripheral, not cluster
        return (periph_size, padding_number)

    # sort registers by <addressOffset>
    #
    register_infos = []
    for register in   tuple(registers.findall('register')) \
                    + tuple(registers.findall('cluster' )):
        reg_svd_name = find_text(register, 'name')
        if not reg_svd_name:
            sys.stderr.write(  "Peripheral %s, cluster %s: Register "
                               "without <name> -- skipping\n"
                             % (periph_in_svd                   ,
                                     '(none)'
                                if   cluster_struct == periph_struct
                                else cluser_struct              )    )
            continue
        alternate_group = find_text(register, 'alternateGroup') # TODO del
        register_name   = reg_svd_name
        if alternate_group:
            register_name += '_' + alternate_group
        del alternate_group

        dim             = parse_int(find_text(register, 'dim'          ))
        dim_incr        = parse_int(find_text(register, 'dimIncrement' ))
        register_size   = parse_int(find_text(register, 'size'         ))
        register_offset = parse_int(find_text(register, 'addressOffset'))
        register_desc   =           find_text(register, 'description'   )
        dim_index       =           find_text(register, 'dimIndex'      )
        if not dim: dim = 1
        if not register_size:
            register_size = derived_from_by_name(registers ,
                                                 register  ,
                                                 'register',
                                                 'size'    )
            if register_size is None:
                register_size = default_size
            else:
                register_size = parse_int(register_size.text)
            if not register_size:  # derivedFrom might have had bad value
                register_size = default_size
        if dim_incr:
            if dim_incr * 8 < register_size:
                sys.stderr.write(  "<dimIncrement> %d bytes but "
                                   "<size> %d bits in peripheral "
                                   "%s register %s -- changing <size> "
                                   "to %d bytes\n"
                                 % (dim_incr     ,
                                    register_size,
                                    periph_in_svd,
                                    reg_svd_name ,
                                    dim_incr * 8  )                     )
                register_size = dim_incr * 8
        else:
            dim_incr = register_size // 8
        if register_size not in (8, 16, 32,64):
            sys.stderr.write(  "Illegal register size %d in peripheral "
                               "%s register %s -- changing to 32\n"
                             % (register_size,
                                periph_in_svd,
                                reg_svd_name  )                          )
            register_size = 32

        if register_name.count('%s') > 1:
            sys.stderr.write(  "Current converter can't handle multiple "
                               "\"%%s\"/\"[%%s]\" (e.g. both \"%%s\" "
                               "and \"[%%s]\" in register "
                               "%s peripheral %s -- removing all"
                             % (reg_svd_name, periph_in_svd)             )
            register_name = remove_name_dim(register_name)
        if dim_index and '[%s]' in register_name:
            sys.stderr.write(  "Illegal \"[%%s]\" in register %s "
                               "with <dimIndex>, peripheral %s -- "
                               "changing to \"%%s\"\n"
                             % (reg_svd_name, periph_in_svd)       )
            # fix: "[%s]" -> "%s"
            register_name = register_name.replace('[', '')
            register_name = register_name.replace(']', '')
        elif dim_index and not '%s' in register_name:
            sys.stderr.write(  "No \"%%s\" in register %s "
                               "name, with <dimIndex>. peripheral %s\n"
                             % (reg_svd_name, periph_in_svd)           )
            dim_index = ""
        elif         '%s'   in register_name \
             and not '[%s]' in register_name \
             and     dim                     \
             and not dim_index:
            sys.stderr.write(  "Register %s in peripheral %s "
                               "has no <dimIndex> but also "
                               "\"%%s\" instead of \"[%%s]\"\n"
                             % (reg_svd_name, periph_in_svd)   )
            register_name = register_name.replace('%s', '')
            while register_name.endswith('_'):
                register_name = register_name[:-1]
        register_name = register_name.replace('[%s]', '')
        if register_name == periph_struct:  # can't nest structs w/ same name
            register_name = "%s_%s" % (periph_struct, register_name)
        register_name = camelcase(register_name)

        if dim_index:
            dims = expand_dim_index(dim_index,
                                      "periph %s  register: %s"
                                    % (periph_in_svd, register_name))
            # ignoring dim if malformed SVD with len(dims) != dim
            for (ndx, dim_name) in enumerate(dims):
                register_infos.append((register                         ,
                                       register.tag == 'cluster'        ,
                                       register_offset + ndx * dim_incr ,
                                       fixname(register_name % dim_name),
                                       register_desc                    ,
                                       register_size                    ,
                                       1                                ,
                                       True                             ))
        else:
            register_infos.append((register                 ,
                                   register.tag == 'cluster',
                                   register_offset          ,
                                   fixname(register_name)   ,
                                   register_desc            ,
                                   register_size            ,
                                   dim                      ,
                                   False                    ))
        del reg_svd_name

    register_infos.sort(key=lambda info: info[2])

    clustr_size    = 0
    decls_rbars    = []
    descs_drvds    = []
    rgstr_sizes    = []
    derived_froms  = {}
    for (reg_ndx, (register       ,
                   is_cluster     ,
                   register_offset,
                   register_name  ,
                   register_desc  ,
                   register_size  ,
                   dim            ,
                   had_dim_index  )) in enumerate(register_infos):

        if 'offset' in opts.debug:
            outfile.write(  "\n    // periph_size=%d,0x%x  "
                            "reg: %s @ %d/0x%x = %d*%d  pre-pad\n"
                          % (periph_size        ,
                             periph_size        ,
                             register_name      ,
                             register_offset    ,
                             register_offset    ,
                             register_size // 8 ,
                             dim                )                 )

        # have to add register/cluster alignment here
        (periph_size, padding_number) = do_padding(outfile        ,
                                                   periph_in_svd  ,
                                                   periph_size    ,
                                                   register_name  ,
                                                   register_size  ,
                                                   register_offset,
                                                   padding_number ,
                                                   indentation    )

        if 'offset' in opts.debug:
            outfile.write(  "\n    // periph_size=%d,0x%x  "
                            "reg: %s @ %d/0x%x = %d*%d  post-pad\n"
                          % (periph_size        ,
                             periph_size        ,
                             register_name      ,
                             register_offset    ,
                             register_offset    ,
                             register_size // 8 ,
                             dim                )                  )

        derived_from = derived_from_stop_tag(registers ,
                                             register  ,
                                             'register',
                                             'fields'  )
        if derived_from == register:
            if is_cluster:
                if had_dim_index:
                    # can't use possible headerStructName because doesn't
                    # have expanded '%s' so all <dimIndex> would have same name
                    cluster_name = register_name
                else:
                    cluster_name = get_struct_name(register)
                cluster_name =      cluster_name + 'Cluster'        \
                               if   cluster_name == cluster_struct  \
                               else cluster_name

                dim_increment = parse_int(find_text(register, 'dimIncrement'))
                (decl_rbar  ,
                 struct_size) = do_cluster(outfile      ,
                                           indentation  ,  # already incremented
                                           periph_in_svd,
                                           periph_struct,
                                           0            ,
                                           0            ,
                                           register     ,
                                           cluster_name ,
                                           dim          ,
                                           False        ,
                                           register     ,
                                           default_size ,
                                           dim_increment)
                indent(outfile                         ,
                       indentation                     ,
                         "};  // struct %s (cluster)\n"
                       % camelcase(cluster_name)       )
            else:
                # C++ can't handle struct of same name as enclosing struct
                if camelcase(register_name) == cluster_struct:
                    register_name += "_reg"
                (decl_rbar, struct_size) = do_register(outfile       ,
                                                       indentation   ,
                                                       cluster_struct,
                                                       register      ,
                                                       register_name ,
                                                       register_size ,
                                                       dim           )
            # TODO: Also need alignment
            decls_rbars.append(decl_rbar             )
            descs_drvds.append((register_desc, False))
            rgstr_sizes.append(struct_size           )
            derived_froms[register] = (decl_rbar, struct_size // dim)
        elif derived_from in derived_froms:
            ((decl, rbar),  size) = derived_froms[derived_from]
            decl_type             = decl.split()[0]
            (decl_rbar  ,
             struct_size) = register_finish(periph_struct           ,
                                            camelcase(register_name),
                                            size                    ,
                                            decl_type               ,
                                            dim                     )
            decls_rbars.append(decl_rbar            )
            descs_drvds.append((register_desc, True))
            rgstr_sizes.append(struct_size          )
        else:
            sys.stderr.write(  "Can't find \"derivedFrom=%s\" "
                               "for register %s in peripheral %s: "
                               "Derived from register at higher "
                               "address not supported (otherwise "
                               "is converter bug).\n"
                             % (register.get('derivedFrom'),
                                register_name              ,
                                periph_in_svd              )        )

        # last one, or next is at higher address
        if    reg_ndx                        == len(register_infos) - 1   \
           or register_infos[reg_ndx + 1][2] >  periph_size:
            periph_size += dump_decls_rbars(outfile    ,
                                            indentation,
                                            is_cluster ,
                                            decls_rbars,
                                            descs_drvds,
                                            rgstr_sizes)
            decls_rbars = []
            descs_drvds = []
            rgstr_sizes = []

            if 'offset' in opts.debug:
                outfile.write(  "    // periph_size=%d,0x%x  after dump\n"
                              % (periph_size  ,
                                 periph_size  )                           )

    if is_peripheral:
        return (periph_size, padding_number)
    else:
        if dim_increment > periph_size:
            (periph_size, padding_number) = do_padding(outfile        ,
                                                       periph_in_svd  ,
                                                       periph_size    ,
                                                       register_name  ,
                                                       0              ,
                                                       dim_increment  ,
                                                       padding_number ,
                                                       indentation    )
        elif dim_increment > 0 and periph_size > dim_increment:
            sys.stderr.write(  "Cluster %s in peripheral %s, <dimIncrement> "
                               "%d bytes but cluster size %d bytes\n"
                             % (register_name,
                                periph_in_svd,
                                dim_increment,
                                periph_size  )                               )
        return register_finish(cluster_struct,
                               cluster_struct,
                               periph_size   ,
                               cluster_struct,  # cluster_type
                               cluster_dim   )



def dump_decls_rbars(outfile    ,
                     indentation,
                     is_cluster ,
                     decls_rbars,
                     descs_drvds,
                     rgstr_sizes):
    if not decls_rbars:
        return 0
    if len(decls_rbars) == 1:
        added_size   = rgstr_sizes[0]
        (decl, rbar) = decls_rbars[0]
        if decl.startswith('uint'):
            outfile.write('\n')
            indent(outfile, indentation, "%s\n" % decl)
        elif is_cluster:
            indent(outfile, indentation, "%s\n" % decl)
        else:
            indent(outfile, indentation, "      %s\n" % decl)
        print_rbar(outfile, indentation, rbar)
    else:
        width = max([len(decl.split()[0]) for (decl, rbar) in decls_rbars]) + 3
        outfile.write('\n')
        indent(outfile, indentation, "union {\n")
        for ((decl, rbar), (desc, drvd), rgstr_size) in zip(decls_rbars,
                                                            descs_drvds,
                                                            rgstr_sizes):
            if desc: linebreak(outfile, indentation + 4, desc)
            if drvd: spaces = 0
            else:    spaces = 4
            (klass, name) = decl.split()
            indent(outfile                                   ,
                   indentation                               ,
                     "%s%s%s\n"
                   % (" " * spaces, klass.ljust(width), name))
        indent(outfile, indentation, "};\n")
        for (decl, rbar) in decls_rbars:
            print_rbar(outfile, indentation + 4, rbar)
    outfile.write('\n')
    return max(rgstr_sizes)




#
# main, etc.
#

def main(xml_lib, svd_path, outfile, version):
    xml_lib = import_xml_lib(xml_lib)
    if not xml_lib:
        sys.exit(1)

    tree = ET.parse(svd_path)
    root = tree.getroot()

    (maj,min,mcr) = (map(int, version.split('.')))
    svd_file = os.path.basename(svd_path)
    #device  = root.find('device')  # has to have
    mcu      = find_text(root, 'name')
    if not mcu: mcu = os.path.splitext(svd_file)[0]
    svd_vers = find_text(root, 'version')
    if not svd_vers: svd_vers = "<no version>"
    svd_desc = find_text(root, 'description')

    outfile.write(HEADER.format(ver='.'.join(map(str, VERSION)),
                                xml_lib=xml_lib                ,
                                svd_file=svd_file              ,
                                mcu=mcu                        ,
                                upper=mcu.upper()              ,
                                lower=mcu.lower()              ,
                                svd_vers=svd_vers              ,
                                svd_desc=svd_desc              ,
                                maj=maj                        ,
                                min=min                        ,
                                mcr=mcr                        ))

    device_default = parse_int(find_text(root, 'size'))
    if not device_default: device_default = 32

    for periph in root.iter('peripheral'):
        if periph.get('derivedFrom'):   # currently treating as 'referenceTo'
            continue                    #   without overrides
        periph_in_svd = find_text(periph, 'name').replace('%', '%%') # for print
        if not periph_in_svd:
            sys.stderr.write("<peripheral> with no <name> -- skipping\n")
            continue
        periph_struct = get_struct_name(periph)  # can't fail after above check
        outfile.write('\n\n\n')

        periph_size    = 0
        padding_number = 0
        (periph_size, padding_number) = do_cluster(outfile                 ,
                                                   0                       ,
                                                   periph_in_svd           ,
                                                   periph_struct           ,
                                                   periph_size             ,
                                                   padding_number          ,
                                                   periph                  ,
                                                   periph_struct           ,
                                                   1                       ,
                                                   True                    ,
                                                   periph.find('registers'),
                                                   device_default          ,
                                                   0                       )
        align_size = (periph_size + 0x3) & ~0x3;
        if align_size > periph_size:
            outfile.write("\n    // pad to modulo 4 bytes")  # no newline
            (periph_size, padding_number) = do_padding(outfile         ,
                                                       periph_in_svd   ,
                                                       periph_size     ,
                                                       '<periph_align>',
                                                       0               ,
                                                       align_size      ,
                                                       padding_number  ,
                                                       4               )
        if 'offset' in opts.debug:
            outfile.write(  "    // periph_size=%d,0x%x  align_size=%d\n"
                          % (periph_size,
                             periph_size,
                             align_size )                                )

        outfile.write("};  // struct %s\n" % periph_struct)
        outfile.write( "{disable}static_assert(sizeof({struct}) == {size}, "
                       "\"sizeof({struct}) != {size}\");\n"
                      .format(disable =      "// "
                                        if   opts.no_sizeof or not periph_size
                                        else ''                               ,
                              struct=periph_struct                            ,
                              size=periph_size                                ))

    outfile.write(PERIPH_DEFINE.format(upper=mcu.upper()))
    periphs = list(root.iter('peripheral'))
    if 'periphs' in opts.sort:
        if 'name' in opts.sort:
            def sorter(periph):
                return find_text(periph, 'name')
        else:
            def sorter(periph):
                return parse_int(find_text(periph, 'baseAddress'))
        periphs.sort(key=sorter)
    for periph in periphs:
        periph_name = find_text(periph, 'name')
        if not periph_name: continue  # already printed warning above

        excludes = list(map(lambda s : s.lower(), opts.excludes))
        h_s_name = find_text(periph, 'headerStructName')
        if                     periph_name   in excludes \
           or  remove_name_dim(periph_name)  in excludes \
           or                     h_s_name   in excludes \
           or camelcase(fixname(  h_s_name)) in excludes:
            continue

        periph_dim = 0
        if '[%s]' in periph_name:
            if periph.find('dimIndex'):
                sys.stderr.write(  "Illegal <dimIndex> in peripheral"
                                   "%s -- ignoring\n"
                                 % periph_name                       )
            periph_dim    = parse_int(find_text(periph, 'dim'         ))
            dim_increment = parse_int(find_text(periph, 'dimIncrement'))
            if not periph_dim or not dim_increment or periph_dim > 1000:
                # 1000 == sanity check
                sys.stderr.write(  "Missing or bad <dim> and/or <dimIncrement>"
                                   "in peripheral %s with \"[%%s]\" in name -- "
                                   "ignoring array specification\n"
                                 % periph_name                                 )
                periph_name = periph_name.replace('[%s]', '')
                periph_dim  = 0
            else:
                periph_name = periph_name.replace('[%s]', '%d')
        if '%s' in periph_name:
            sys.stderr.write(  "Illegal \"%s\" in peripheral %s name "
                               "(should be \"[%%s]\" -- removing and "
                               "ignoring array specification\n"
                             % periph_name                            )
            periph_name = periph_name.replace('%s', '')
        if '%d' in periph_name:
            periph_name = '%d'.join([    snakecase(fixname(part)).lower()
                                     for part
                                     in  periph_name.split('%d')         ])
        else:
            periph_name = fixname(periph_name.lower())
        struct_periph = derived_from_stop_tag(root.find('peripherals'),
                                              periph                  ,
                                              'peripheral'            ,
                                              'registers'             )
        struct_name = get_struct_name(struct_periph        )
        addr        =       find_text(periph, 'baseAddress')
        if not addr: addr = '0x00000000'
        if periph_dim:
            addr = parse_int(addr)
            for instance in range(periph_dim):
                dim_name = periph_name % instance
                outfile.write(  "%s_PERIPH( %-16s, %-16s, 0x%08x);\n"
                              % (mcu.upper()     ,
                                 struct_name     ,
                                 dim_name.lower(),
                                 addr            )                   )
                addr += dim_increment
        else:
            outfile.write(  "%s_PERIPH( %-16s, %-16s, %-10s);\n"
                          % (mcu.upper(),
                             struct_name,
                             periph_name,
                             addr       )                       )
    outfile.write(PERIPH_UNDEF.format(upper=mcu.upper()))


    outfile.write(ARM_NVIC_HEADER)
    for arm_irq in ARM_IRQS:
        outfile.write("    %-24s = %4d,\n" % arm_irq)
    mcu_irqs = []
    alreadys = set()
    for periph in root.iter('peripheral'):
        interrupt = periph.find('interrupt')
        if interrupt is None:
            continue
        name = fixname(remove_name_dim(find_text(interrupt, 'name')))
        if not name: continue    # already printed warning
        desc = find_text(interrupt, 'description')
        valu = find_text(interrupt, 'value'      )
        try:    valu = int(valu)
        except: valu = 0
        if name and valu not in alreadys:
            alreadys.add   ( valu               )
            mcu_irqs.append((valu, (name, desc)))
    outfile.write("    // %s IRQs\n" % mcu)
    if 'irqs' in opts.sort:
        if 'name' in opts.sort:
            def sorter(irq): return irq[1]
        else:
            def sorter(irq): return irq[0]
        mcu_irqs.sort(key=sorter)
    for (valu, (name, desc)) in mcu_irqs:
        if name in ARM_IRQ_NAMES: name = '%s_%s' % (name, mcu)
        if desc:
            outfile.write("    %-24s = %4d,    " % (name, valu))
            linebreak(outfile           ,
                      40                ,
                      desc              ,
                      first_indent=False,
                      extra_indent=2    )
        else:
            outfile.write("    %-24s = %4d,\n" % (name, valu))

    outfile.write(ARM_NVIC_FOOTER)

    outfile.write(FOOTER.format(upper=mcu.upper(), mcu=mcu))




def parse_commandline():
    parser = argparse.ArgumentParser(
                formatter_class=argparse.ArgumentDefaultsHelpFormatter)

    parser.add_argument("--lib",
                        choices=('xml',
                                 'lxml',
                                 'defusedxml',
                                 'BeautifulSoup',
                                 'auto'),
                        default='auto',
                        help="XML parsing library"),

    parser.add_argument('-f', '--file',
                        type=argparse.FileType('w'),
                        default=sys.stdout,
                        help="\"regbits\" output file")

    parser.add_argument('-m', '--max_mskd',
                        type=int          ,
                        default=3         ,
                        help="Maximum mskd_t width before using "
                             "REGBITS_MSKD_RANGE"                )

    parser.add_argument('-u', '--unsigned-width',
                        type=int          ,
                        default=32        ,
                        help="Bit width of unsigned type for "
                             "choosing between REGBITS_MSKD_RANGE "
                             "REGBITS_MSKD_UNSGN"                  )

    parser.add_argument('--no-sizeof',
                        action="store_true",
                        help="Comment out struct sizeof() static_asserts")

    parser.add_argument('-w', '--width',
                        type=int       ,
                        default=79     ,
                        help="Width of .hxx output text")

    parser.add_argument('-n', '--newlines',
                        action="store_true",
                        help="Keep newlines in <descriptions>. Use if SVD "
                             "file has formatted descriptions with newlines "
                             "and whitespace, leave unset if uses whitespace "
                             "to indent XML"
                        )

    parser.add_argument("version",
                        nargs='?',
                        default='0.0.0',
                        help="Output file version triplet (major.minor.micro)")

    parser.add_argument('-a', '--align',
                        type=int       ,
                        nargs=2        ,
                        default=(4,2)  ,
                        help="Size modulo of structs, arrays of structs")

    parser.add_argument('-x', '--excludes',
                        nargs='*',
                        default=[],
                        help="Peripherals to exclude")

    parser.add_argument('-s', '--sort',
                        nargs='*',
                        choices=('none', 'addr', 'name', 'periphs', 'irqs'),
                        default=(('addr', 'irqs', 'periphs')),
                        help="Sort objects in output by address")

    parser.add_argument('--debug',
                        nargs='*',
                        choices=('none', 'periph', 'reg', 'offset'),
                        default=tuple(),
                        help="Debug")

    parser.add_argument("svd",
                        help="SVD input file")

    parser.add_argument('-q', '--quiet',
                        action="store_true",
                        help="Don't print version and copyright notice.")

    return parser.parse_args()




if __name__ == '__main__':
    opts = parse_commandline()
    if not opts.quiet:
        sys.stdout.write("%s\n" % COPYRIGHT)
    hxx_width = opts.width   # global
    main(opts.lib, opts.svd, opts.file, opts.version)
