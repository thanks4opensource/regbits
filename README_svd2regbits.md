README for svd2regbits.py
=========================

**svd2regbits.py** is a tool to convert CMSIS System View Description (SVD) files into [regbits](README.md) C++ header files.


Copyright <a name="copyright"></a					   >
---------

regbits: C++ templates for type-safe bit manipulation
Copyright (C) 2019,2020 Mark R. Rubin

This file is part of regbits.

The regbits program is free software: you can redistribute it
and/or modify it under the terms of the GNU General Public License
as published by the Free Software Foundation, either version 3 of
the License, or (at your option) any later version.

The regbits program is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty
of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
(LICENSE.txt) along with the regbits program. If not, see
<https://www.gnu.org/licenses/gpl.html>.


Contents  <a name="contents"></a>
--------
* [Copyright](#copyright)
* [SVD and svd2regbits.py](#svd_and_svd2regbits.py)
    * [Disclosure](#disclosure)
    * [Design and documentation](#design_and_documentation)
    * [svd2regbits.py](#svd2regbits_py)
    * [`<dim>`/`[%s]` arrays vs `<dimIndex>`/`%s` lists vs `<derivedFrom>`](#dim_vs_dim_index)
    * [svd2regbits.py `<derivedFrom>` limitations](#svd2regbits.py_`<derivedFrom>`_limitations)
    * [Missing `<headerStructName>` tags](#Missing_`<headerStructName>`_tags)
    * [Unconvertible SVD constructs](#unconvertible_svd_constructs)
    * [Size and alignment errors](#size_and_alignment_errors)
    * [SVDs file "quality"](#svds_file_quality)
* [Credits](#credits)



SVD and svd2regbits.py <a name="svd_and_svd2regbits.py"></a>
----------------------

<a name="disclosure"></a>
#### Disclosure
This document includes highly opinionated comments and occasional criticisms regarding the design of the SVD standard and its implementation in  many existing SVD file implementations. All statements are strictly the author's opinion and do not in any way reflect the views of the individuals and organizations listed [below](#credits).



<a name="design_and_documentation"></a>
### Design and documentation

The design of the SVD file format, and its related documentation, is in general highly commendable. The design is exceptionally complete and general, covering a wide range of disparate use cases. Likewise,the documentation is among the best [<sup>1</sup>](#footnote_1) that exists in the realm of embedded software.

That said, neither are perfect. The documentation is unclear and/or ambiguous several places. That, and more importantly, the complexity of the format almost guarantees that many creators of SVD files will make serious mistakes [<sup>2</sup>](#footnote_2). Such files are frequently semantically incorrect or at minimum "clumsy" and non-optimal, and often even syntactically malformed on some level.


### svd2regbits.py <a name="svd2regbits_py"></a>

The current [svd2regbits.py](svd2regbits.py) program should be considered an early beta release. It is missing several important capabilities, and likewise doesn't handle (or handles poorly) several SVD features. The intent is that many of these failings will be addressed in future releases, although not all (see [below](#unconvertible_svd_constructs)).

The general intent, both currently and for the future, is to "fix" incorrect and/or untranslatable SVD file features when strictly necessary, but to "drop" all others (malformed, or other elements that svd2regbits.py cannot handle,  will not appear in the regbits .hxx file output). Warning messages will be printed in both cases. Specifically, constructs which the author (rightly or wrongly) considers in violation of the documented SVD file format will be removed. Several examples of these are described in the following sections.

In terms of testing, the current svd2regbits.py successfully converts all SVD examples in the [posborne/cmsis-dvd/data](https://github.com/posborne/cmsis-svd/tree/master/data) repository (see [Credits](#credits), below) as of this writing, and all compile with the exception of two which contain "svd2regbits-will-not-attempt-to-fix" typos [<sup>3</sup>](#footnote_3). Whether or not the resulting regbits .hxx files contain correct addresses, offsets, register layouts, and/or bitfield descriptions is another question entirely.



<a name="dim_vs_dim_index"></a>
### `<dim>`/`[%s]` arrays vs `<dimIndex>`/`%s` lists vs `<derivedFrom>`

This is the most frequent misuse/misinterpretation of the complex SVD format. The documentation clearly states (for `<cluster>`, `<register>`, and `<field`>  elements):

*name:* ... *You can use the placeholder %s, which is replaced by the dimIndex substring. Use the placeholder [%s] only at the end of the identifier to generate arrays in the header file. The placeholder [%s] cannot be used together with dimIndex.*

and:

*dimIndex: Specify the substrings that replaces the %s placeholder within name and displayName. By default, the index is a decimal value starting with 0 for the first register. dimIndex should not be used together with the placeholder [%s], but rather with %s.*

Despite this clarity, many existent SVD files contain elements with `<name>` tags containing `%s` but no corresponding `<dimIndex>`, and vice-versa (`[%s]` with `<dimIndex>`). Also `%s` with `<dim>` in addition to `<dimIndex>` (which is the correct size? `<dim>` or the number of the `<dimIndex>` values?) and other such horrors.

In addition, there is almost universal "misuse" of `%s` with e.g. `<dimIndex>0,1,2,3</dimIndex>` which conceptually should be replaced (in this example) with `[%s]` and `<dim>4</dim>`. Admittedly this is both a question of style (whether individually-named elements vs a singly-named array is desired), and also somewhat regbits specific where e.g. `ARRAY[2]` is safely range-checked at compile time without any impact on executable code size or speed compared to `NAME_2`.

Also note that `<peripheral>` elements are clearly documented as only allowing `[%s]`, not `%s` [<sup>4</sup>](#footnote_4).

Partly due to current limitations [<sup>5</sup>](#footnote_5) of regbits, the problems are handled as follows:

* `<peripheral>`:  Illegal `%s` and/or missing `<dim>` or `<dimIncrement>` ignored/removed, otherwise handled correctly.
* `<cluster>` and `<register>`: Ignored if more than one `%s` and/or `[%s]` [<sup>6</sup>](#footnote_6). If `[%s]` and `<dimIndex>`, `[%s]` changed to `%s` and `<dimIndex>` used. Ignored if `%s` without `dimIndex`. Otherwise handled correctly by expanding `%s`/`<dimIndex>` as separately-named elements, or `[%s]`/`<dim>` as array.
* `<field>`: Always expanded as separate `%s`/`<dimIndex>` names (including implicit rewrite of `[%s]`/`<dim>` to `%s`/`<dimIndex>` if the former) due to current regbits limitation [<sup>5</sup>](#footnote_5).



<a name="svd2regbits.py_`<derivedFrom>`_limitations"></a>
### svd2regbits.py `<derivedFrom>` limitations

The current svd2regbits.py converter intentionally misinterprets `<derivedFrom>` tags in `<peripheral>`, `<cluster>`, and `<register>` elements, effectively treating them as "clonedFrom" or "copyOf", i.e. without modification or overriding. (It also completely ignores `<derivedFrom>` in `<field>` and `<enumeratedValue>` elements.)

The `<derivedFrom>` tag adds useful the capabilities to the design of SVD format, but is very difficult to implement fully in an SVD-to-C/C++ converter. This is especially true if the converter attempts to create single struct/object definitions for multiple SVD elements which are identical instead of blindly expanding a possibly deep `<derivedFrom>` tree without analysis of what, if anything, is being added/overridden.

Future releases of svd2regbits.py should have improvements regarding the issue.

In addition, svd2regbits.py cannot handle "retrograde" `<derivedFrom>` addresses. C++ (and C) peripheral structs must have their registers/clusters in address order because they must know the type of each sub-object as it is instantiated (forward declaration does not work in this situation). For example, if an SVD file has:

        <peripheral>
          <name>SOME_PERIPHERAL</name>
          <register>
            <name>FIRST_OF_THIS_TYPE</name>
            <addressOffset>0x20</addressOffset>
            ...
          </register>
          ...
          <register derivedFrom FIRST_OF_THIS_TYPE>
            <name>SECOND_OF_THIS_TYPE</name>
            <addressOffset>0x10</addressOffset>
            ...
          </register>
        </peripheral>

the converted regbits .hxx file will fail to compile:

        struct SomePeripheral {
            first_of_this_type_t   secondOfThisType;
            // ...
            struct FirstOfThisType {
                // ...
            };
            using first_of_this_type_t = Reg<uint32_t, FirstOfThisType>;
                  first_of_this_type_t   first_of_this_type;
        };

Again, this could be corrected by a "virtual" reordering of the SVD file at conversion time, but the difficulty of doing so will likely remain out of the scope of this converter for the conceivable future, regardless that the problem is specific to svd2regbits.py and does not affect SVD-to-CMSIS converters. (I contend that such SVD files are conceptually misleading and should be 
changed anyway -- if the ordering is not in fact a typo in the first place.)

Note that the above is a separate issue from the order in the SVD file (although it would also be nice if SVD writers respected address order, thus allowing linear "stream" parsing of the files).



<a name="Missing_`<headerStructName>`_tags"></a>
### Missing `<headerStructName>` tags

A problem with many existing SVD files (not the SVD standard itself) is the lack of `<headerStructName>` tags, particularly in `<derivedFrom>` peripherals where they would be most useful. The SVD documentation clearly states:

*headerStructName: Specify the base name of C structures. The headerfile generator uses the name of a peripheral as the base name for the C structure type. If <headerStructName> element is specfied, then this string is used instead of the peripheral name; useful when multiple peripherals get derived and a generic type name should be used.*

Failure to include meaningful `<headerStructName>` tags results in C/C++ pointers in converted files with confusingly inaccurate types, such the following in a regbits/C++/.hxx file:

        static volatile GenTim2* gen_tim_4 = reinterpret_cast<volatile GenTim2*>(TIM4_BASE);

or the equivalent in a CMSIS .h header file: 

        #define TIM4 ((TIM2_TypeDef *)TIM4_BASE)

Note that, ironically, the `<groupName>` tag *is* often included but cannot be used as a substitute for `<headerStructName>` as it is frequently more "generic" (e.g. all timers being given `<groupName>TIMER</groupname>` tags despite the various timers belonging to conceptually and C/C++ struct/class different sub-types).



<a name="unconvertible_svd_constructs"></a>
### Unconvertible SVD constructs

The SVD file format allows the description of elements that while syntactically and semantically correct cannot be converted into C/C++ structs without extensive reinterpretation. For example, consider the following pathological case:

        <register>
          <name>A[%s]</name>
          <addressOffset>0x20</addressOffset>
          <size>32</size>
          <dim>4</dim>
          <dimIncrement>8</dimIncrement>
          ...
        </register>
        <register>
          <name>B[%s]</name>
          <addressOffset>0x24</addressOffset>
          <size>32</size>
          <dim>4</dim>
          <dimIncrement>8</dimIncrement>
          ...
        </register>

Of course these interleaved registers should be more properly written as a `<cluster>` containing "A" and "B" and `<dim>4</dim>`, but while the above is perfectly legal SVD, it cannot be converted without an A.I.-level analysis and implicit rewrite.


<a name="size_and_alignment_errors"></a>
### Size and alignment errors

Many existent SVD files contain obvious alignment and/or size errors, such as 16, 32, 64 bit registers with `<addressOffset>` values that are not 2, 4, 8 bit aligned. I understand that some ARM (and other) CPUs can handle misaligned data, but other evidence in the files imply that the misalignments are in fact typos or misunderstandings.


<a name="svds_file_quality"></a>
### SVDs file "quality"

As noted in the SVD documentation, the "quality" of an SVD file is a separate issue from its correctness. An SVD file can be syntactically and semantically correct but if it is missing `<field>` and/or `<enumeratedValue>` elements it will likely be of little use, both in and of itself and after conversion to a usable format such as CMSIS header or regbits .hxx file [<sup>7</sup>](#footnote_7). "Garbage in, garbage out" as the saying from the dawn of computing goes.



Credits <a name="credits"></a>
-------
Many thanks to:

* [gzigzigzeo](https://github.com/gzigzigzeo) for informing me about the existence of SVD files ([Generate RegBits definitions from SVD #1](https://github.com/thanks4opensource/regbits_stm/issues/1))
* [posborne](https://github.com/posborne) for his excellent work creating and maintaining his [CMSIS-SVD Repository and Parsers](https://github.com/posborne/cmsis-svd/)
* [Arm Limited](https://www.arm.com/) and/or [armKeil](https://www.keil.com/) [<sup>8</sup>](#footnote_8) for creating and making publicly available [<sup>9</sup>](#footnote_9) SVD and its documentation ([System View Description](https://arm-software.github.io/CMSIS_5/SVD/html/index.html), [System View Description](https://www.keil.com/pack/doc/CMSIS/SVD/html/index.html)).



Footnotes
---------
1. <a name="footnote_1"></a> Given the quality level of most embedded documentation, this is unfortunately a very low hurdle to clear.
2. <a name="footnote_2"></a> And they do. Lots of them.
3. <a name="footnote_3"></a> Not to name any names, but a company whose initials begin with "S" and "T" and end with "M" shouldn't include multiple `<interrupt>` elements with the same `<name>` but different `<value>` values. To be fair, these obvious typos affect only two of the 87 STM SVD examples tested.
4. <a name="footnote_4"></a> I have not seen any examples that violate this rule, nor in fact any arrays of `<peripheral>` at all. Once again the possibility that the SVD standard is more complex than necessary, in this case with `<peripheral>` arrays being a subset of the `<derivedFrom>` semantics.
5. <a name="footnote_5"></a> Which will be addressed in an upcoming release.
6. <a name="footnote_6"></a> What does having both `%s` and `[%s]` in a `<cluster>` or `<register>` name mean? Multiple `<dimIndex>`-replaced names each being a `<dim>` array, or an array of `<dimIndex>` names in an implicit `<cluster>`?
7. <a name="footnote_7"></a> I find it ironic that STM, which does a fair job of `#define`-ing field values in its CMSIS headers (although only for single bit fields, completely giving up on multiple regardless of whether wide and semantically an integer vs. narrow with a small number of enumerated encoded values) (and likewise has no `<enumeratedValue>` tags in its SVD files), while NXP which at least in the CMSIS headers for the older, low-end LPC series chips I've seen has no field descriptions at all nevertheless supplies `<field>` tags with `<description>` and `<enumeratedValue>` elements in its SVDs. (Their CMSIS headers aren't generated from the SVDs?)
8. <a name="footnote_8"></a> The creation, history, and ownership of SVD is unclear to me.
9. <a name="footnote_9"></a> Likewise its licensing terms, other than the Apache license in the published [CMSIS-SVD Schema File](https://arm-software.github.io/CMSIS_5/SVD/html/schema_1_2_gr.html), [CMSIS-SVD Schema File](https://www.keil.com/pack/doc/CMSIS/SVD/html/schema_1_2_gr.html)
