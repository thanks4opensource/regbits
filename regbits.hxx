// regbits: C++ templates for type-safe bit manipulation
// Copyright (C) 2019 Mark R. Rubin
//
// This file is part of regbits.
//
// The regbits program is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation, either version 3 of the
// License, or (at your option) any later version.
//
// The regbits program is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License (LICENSE.txt) along with the regbits program.  If not, see
// <https://www.gnu.org/licenses/gpl.html>


#ifndef regbits_hxx
#define regbits_hxx

namespace regbits {

template<typename WORD, typename CLSS> class Pos {
  public:
    // friends
    template <typename BITS_WORD, typename BITS_CLSS> friend class Bits;
    template <typename BITS_WORD, typename BITS_CLSS> friend class Mskd;


    // constructors
    //
    explicit
    constexpr
    Pos(
    const WORD  pos)
    :   _pos(pos)
    {}

#ifdef REGPOS_COPY_CTOR  // implementing this impacts object passing performance
    constexpr
    Pos(
    const Pos<WORD, CLSS>   &other)
    :   _pos(other._pos)
    {}
#endif


    // for passing constexpr instance by value without requiring storage
    Pos<WORD, CLSS> operator+()
    const
    {
        return *this;  // don't need: return Pos(_pos);
    }


    // assignments
    //
    Pos<WORD, CLSS> operator=(
    const Pos<WORD, CLSS>   &other)
    {
        _pos = other._pos;
        return *this;
    }

    Pos<WORD, CLSS> operator=(
    const WORD  word)
    {
        _pos = word;
        return *this;
    }


    // accessor
    constexpr WORD pos() const { return _pos; }


    // comparisons
    //
    constexpr
    bool operator==(
    const Pos<WORD, CLSS>    other)
    const
    {
        return other._pos == _pos;
    }

    constexpr
    bool operator!=(
    const Pos<WORD, CLSS>    other)
    const
    {
        return  other._pos != _pos;
    }


  private:
    // do not implement this, even as private
    // operator WORD() {}


  protected:
    WORD    _pos;

};  // template<typename WORD, typename CLSS> class Pos



// forward ref
template<typename MSKD_WORD, typename MSKD_CLSS> class Mskd;

template<typename WORD, typename CLSS> class Bits {
  public:
    // friends
    template <typename MSKD_WORD, typename MSKD_CLSS> friend class Mskd;
    template <typename REG_WORD, typename REG_CLSS> friend class Reg;


    // constructors
    //
    constexpr
    Bits(
    const WORD  bits)
    :   _bits(bits)
    {}

    constexpr
    Bits(
    const     WORD          bits,
    const Pos<WORD, CLSS>   pos )
    :   _bits(bits << pos._pos)
    {}

#ifdef REGBITS_COPY_CTOR  // implementing this impacts object passing performance
    constexpr
    Bits(
    const Bits<WORD, CLSS>  &other)
    :   _bits(other._bits)
    {}
#endif

    // for passing constexpr instance by value without requiring storage
    Bits<WORD, CLSS> operator+()
    const
    {
        return *this;  // don't need: return Bits(_bits)
    }


    // assignments
    //
    Bits<WORD, CLSS> operator=(
    const Bits<WORD, CLSS>  &other)
    {
        _bits = other._bits;
        return *this;
    }

    Bits<WORD, CLSS> operator=(
    const WORD  bits)
    {
        _bits = bits;
        return *this;
    }


    // accessor
    constexpr WORD bits() const { return _bits; }


    // converter (must be explicit)
    //
    explicit
    constexpr
    operator Mskd<WORD, CLSS>()
    {
        return Mskd<WORD, CLSS>(_bits, _bits);
    }


    // bitwise operators
    //
    constexpr
    Bits<WORD, CLSS> operator|(
    const Bits<WORD, CLSS>   other)
    const
    {
        return Bits<WORD, CLSS>(_bits | other._bits);
    }

    constexpr
    Bits<WORD, CLSS> operator|(
    const Mskd<WORD, CLSS>   &mskd)
    const
    {
        return Bits<WORD, CLSS>(_bits | mskd._bits);
    }

    Bits<WORD, CLSS> operator|=(
    const Bits<WORD, CLSS>   other)
    {
        _bits |= other._bits;
        return *this;
    }

    constexpr
    Bits<WORD, CLSS> operator|=(
    const Mskd<WORD, CLSS>   &mskd)
    {
        _bits |= mskd._bits;
        return *this;
    }


    // comparisons
    //
    constexpr
    bool operator==(
    const Bits<WORD, CLSS>   other)
    const
    {
        return other._bits == _bits;
    }

    constexpr
    bool operator!=(
    const Bits<WORD, CLSS>   other)
    const
    {
        return  other._bits != _bits;
    }


  private:
    // do not implement this, even as private
    // operator WORD() {}


  protected:
    WORD    _bits;

};  // template<typename WORD, typename CLSS> class Bits




// #warning could derive from Bits
template<typename WORD, typename CLSS> class Mskd {
  public:
    // friends
    template <typename BIT_WORD, typename BIT_CLSS> friend class Bits;
    template <typename REG_WORD, typename REG_CLSS> friend class Reg;


    // constructors
    //
    constexpr
    Mskd(
    const     WORD          mask,
    const     WORD          bits,
    const Pos<WORD,CLSS>    pos )
    :   _mask(mask << pos._pos),
        _bits(bits << pos._pos)
    {}

    constexpr
    Mskd(
    const WORD  mask,
    const WORD  bits)
    :   _mask(mask),
        _bits(bits)
    {}

#ifdef REGBITS_COPY_CTOR  // implementing this impacts object passing performance
    constexpr
    Mskd(
    const Mskd<WORD, CLSS> &other)
    :   _mask(other._mask),
        _bits(other._bits)
    {}
#endif

    // for passing constexpr instance by value without requiring storage
    Mskd<WORD, CLSS> operator+()
    const
    {
        return Mskd(_mask, _bits);   // can't have: return *this
    }


    // resettter
    Mskd<WORD, CLSS> &operator()(
    const WORD  mask,
    const WORD  bits)
    {
        _mask = mask;
        _bits = bits;
        return *this;
    }


    // assignments
    //
    Mskd<WORD, CLSS> &operator=(
    const Mskd<WORD, CLSS> &other)
    {
        _mask = other._mask;
        _bits = other._bits;
        return *this;
    }

    Mskd<WORD, CLSS> &operator=(
    const Bits<WORD, CLSS>  &bits)
    {
        _mask = bits._bits;
        _bits = bits._bits;
        return *this;
    }


    // accessors
    constexpr WORD mask() const { return _mask; }
    constexpr WORD bits() const { return _bits; }


    // converter (must be explicit)
    explicit
    constexpr
    operator Bits<WORD, CLSS>()
    {
        return Bits<WORD, CLSS>(_bits);
    }


    // bitwise operators
    //
    constexpr
    Mskd<WORD, CLSS> operator|(
    const Mskd<WORD, CLSS>  &other)
    const
    {
        return Mskd<WORD, CLSS>(_mask | other._mask, _bits | other._bits);
    }

    constexpr
    Mskd<WORD, CLSS> operator|(
    const Bits<WORD, CLSS>   bits)
    const
    {
        return Mskd<WORD, CLSS>(_mask | bits._bits, _bits | bits._bits);
    }

    Mskd<WORD, CLSS> operator|=(
    const Mskd<WORD, CLSS>  &other)
    {
        _mask |= other._mask;
        _bits |= other._bits;
        return *this;
    }

    Mskd<WORD, CLSS> operator|=(
    const Bits<WORD, CLSS>   bits)
    {
        _mask |= bits._bits;
        _bits |= bits._bits;
        return *this;
    }



    // comparisons
    //
    constexpr
    bool operator==(
    const Mskd<WORD, CLSS>  &other)
    const
    {
        return other._mask == _mask && other._bits == _bits;
    }

    constexpr
    bool operator!=(
    const Mskd<WORD, CLSS>  &other)
    const
    {
        return  other._mask != _mask || other._bits != _bits;
    }

    constexpr
    bool operator<(
    const Mskd<WORD, CLSS>  &other)
    const
    {
        return _bits < other._bits;
    }

    constexpr
    bool operator<=(
    const Mskd<WORD, CLSS>  &other)
    const
    {
        return _bits <= other._bits;
    }

    constexpr
    bool operator>(
    const Mskd<WORD, CLSS>  &other)
    const
    {
        return _bits > other._bits;
    }

    constexpr
    bool operator>=(
    const Mskd<WORD, CLSS>  &other)
    const
    {
        return _bits >= other._bits;
    }


  private:
    // do not implement this, even as private
    // operator WORD() {}


  protected:
    WORD    _mask,
            _bits;

};  // template<typename WORD, typename CLSS> class Mskd



template<typename WORD,  typename CLSS> class Reg {
  public:
    // constructor
    constexpr Reg<WORD, CLSS>() {};


    // accessor
    WORD word() { return _word; }


    // extractors
    //
    Bits<WORD, CLSS> &operator>>=(
    Bits<WORD, CLSS>    &bits)
    const
    {
        bits._bits = _word;
        return bits;
    }

    Bits<WORD, CLSS> &get(
    Bits<WORD, CLSS>    &dest)
    const
    {
        dest._bits = _word;
        return dest;
    }

    Mskd<WORD, CLSS> &operator>>=(
    Mskd<WORD, CLSS>    &mskd)
    const
    {
    //  mskd._mask = _word; // leave alone
        mskd._bits = _word & mskd._mask;
        return mskd;
    }

    Mskd<WORD, CLSS> &get(
    Mskd<WORD, CLSS>    &dest)
    const
    {
    //  dest._mask = _word;  // leave alone
        dest._bits = _word & dest._mask;
        return dest;
    }

    // assignments
    //
    void operator=(
    const WORD  word)
    volatile
    {
        _word = word;
    }

    void zero(
    const WORD  word)
    volatile
    {
        _word =static_cast<WORD>(0);
    }

    void operator=(
    const Bits<WORD, CLSS>  bits)
    volatile
    {
        _word = bits._bits;
    }

    void wrt(
    const Bits<WORD, CLSS>  bits)
    volatile
    {
        _word = bits._bits;
    }

    void operator=(
    const Mskd<WORD, CLSS>  &mskd)
    volatile
    {
        _word = mskd._bits;
    }

    void wrt(
    const Mskd<WORD, CLSS>  &mskd)
    volatile
    {
        _word = mskd._bits;
    }


    // bitwise operators
    //
    void operator|=(
    const Bits<WORD, CLSS>  bits)
    volatile
    {
        _word |= bits._bits;
    }

    void set(
    const Bits<WORD, CLSS>  bits)
    volatile
    {
        _word |= bits._bits;
    }

    void operator|=(
    const Mskd<WORD, CLSS>  &mskd)
    volatile
    {
        _word |= mskd._bits;
    }

    void set(
    const Mskd<WORD, CLSS>  &mskd)
    volatile
    {
        _word |= mskd._bits;
    }


    void operator-=(
    const Bits<WORD, CLSS>  bits)
    volatile
    {
        _word &= ~bits._bits;
    }

    void clr(
    const Bits<WORD, CLSS>  bits)
    volatile
    {
        _word &= ~bits._bits;
    }

    void operator-=(
    const Mskd<WORD, CLSS>  &mskd)
    volatile
    {
        _word &= ~mskd._bits;
    }

    void clr(
    const Mskd<WORD, CLSS>  &mskd)
    volatile
    {
        _word &= ~mskd._bits;
    }


    void operator^=(
    const Bits<WORD, CLSS>  bits)
    volatile
    {
        _word ^= bits._bits;
    }

    void flp(
    const Bits<WORD, CLSS>  bits)
    volatile
    {
        _word ^= bits._bits;
    }

    void operator^=(
    const Mskd<WORD, CLSS>  &mskd)
    volatile
    {
        _word ^= mskd._bits;
    }

    void flp(
    const Mskd<WORD, CLSS>  &mskd)
    volatile
    {
        _word ^= mskd._bits;
    }

    void operator<<=(
    const Mskd<WORD, CLSS>  &mskd)
    volatile
    {
        _word = (_word & ~mskd._mask) | mskd._bits;
    }

    void ins(
    const Mskd<WORD, CLSS>  &mskd)
    volatile
    {
        _word = (_word & ~mskd._mask) | mskd._bits;
    }


    // comparisons
    //
    constexpr
    bool zero()
    const
    {
        return _word == static_cast<WORD>(0);
    }

    constexpr
    bool operator==(
    const WORD      word)
    {
        return word == _word;
    }

    constexpr
    bool operator!=(
    const WORD      word)
    {
        return word != _word;
    }


    constexpr
    bool operator==(
    const Bits<WORD, CLSS>  bits)
    const
    {
        return _word & bits._bits;
    }

    bool operator!=(
    const Bits<WORD, CLSS>  bits)
    const
    {
        return !(_word & bits._bits);
    }

    bool operator==(
    const Mskd<WORD, CLSS>  &mskd)
    const
    {
        return (_word & mskd._mask) == mskd._bits;
    }

    bool operator!=(
    const Mskd<WORD, CLSS>  &mskd)
    const
    {
        return (_word & mskd._mask) != mskd._bits;
    }



  protected:
    volatile WORD   _word;


  private:
    // do not implement this, even as private
    // operator WORD() {}

};  // template<typename BITS, typename MSKD> class Reg

}  // namespace regbits



// macro for generating functions returning Bits (constexpr and non-)
// assumes pos_t and bits_ have been typedef'd/using'd
//
#define REGBITS_BITS_RANGE(CLASS, CONSTEXPR_FUNC, RUNTIME_FUNC, VALID_FUNC, WORD) \
template<unsigned BIT_NUM> static constexpr bits_t CONSTEXPR_FUNC() { \
    static_assert(BIT_NUM < sizeof(WORD) * 8, \
                  CLASS "::" #CONSTEXPR_FUNC "<BIT_NUM> out of range"); \
    return bits_t(1, pos_t(BIT_NUM)); \
} \
static const bits_t RUNTIME_FUNC( \
const unsigned  bit_num) \
{ \
    return bits_t(1, pos_t(bit_num)); \
} \
static bool VALID_FUNC( \
const unsigned  bit_num) \
{ \
    return bit_num < sizeof(WORD) * 4; \
}


// macro for generating functions returning Mskd (constexpr and non-)
// assumes mskd_t has been typedef'd/using'd
//
#define REGBITS_MSKD_RANGE(CLASS, CONSTEXPR_FUNC, RUNTIME_FUNC, VALID_FUNC, MASK, POS, LIMIT) \
template<unsigned BITS> static constexpr mskd_t CONSTEXPR_FUNC() { \
    static_assert(BITS <= LIMIT, \
                  CLASS "::" #CONSTEXPR_FUNC "<BITS> out of range"); \
    return mskd_t(MASK, BITS, POS); \
} \
static const mskd_t RUNTIME_FUNC( \
const unsigned  bits) \
{ \
    return mskd_t(MASK << POS.pos(), bits << POS.pos()); \
} \
static bool VALID_FUNC( \
const unsigned  bits) \
{ \
    return bits <= LIMIT; \
}


// macro for generating functions returning array member (constexpr and non-)
#define REGBITS_ARRAY_RANGE(CLASS, CONSTEXPR_FUNC, RUNTIME_FUNC, VALID_FUNC, DATATYPE, ARRAY, LIMIT) \
template<unsigned INDEX> DATATYPE& CONSTEXPR_FUNC() { \
    static_assert(INDEX <= LIMIT, \
                  CLASS "::" #CONSTEXPR_FUNC "<INDEX> out of range"); \
    return ARRAY[INDEX]; \
} \
DATATYPE& RUNTIME_FUNC( \
const unsigned index) \
{ \
    return ARRAY[index]; \
} \
static bool VALID_FUNC( \
const unsigned  index) \
{ \
    return index <= LIMIT; \
}

#endif  // ifndef regbits_hxx
