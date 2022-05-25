/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Project: iCalc - Integer only Calculator  *  Written by: Nick Matthews  *
 *  Module: Primitive arithmatic functions   *  Date Started: 19 Nov 2007  *
 *    File: icPrim.h        Type: C Header   *  Date Revised: 27 Nov 2007  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    Copyright (c) 2007, Nick Matthews

    Licence: GNU GPLv3
*/

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <cstdint>

namespace kcinteger {

    using elem = uint32_t;
    using lelem = uint64_t;
    using slelem = int64_t;

    constexpr int ELEM_BITS = sizeof( elem ) * 8; // 32
    constexpr lelem ELEM_BASE = 0x0000000100000000ULL;
    constexpr elem LEAD_BIT = 0x80000000U;
    constexpr elem ELEM_BORROW = 0xffffffffU;

            // return zero if a == b, pos if a > b, neg if a < b
    extern int PrimCmp( size_t len, const elem* a, const elem* b );

    // x += a;  where alen <= xlen, returns a carry if result len < blen
    extern elem PrimAdd( size_t xlen, elem* x, size_t alen, const elem* a );

    // x -= a;  where alen <= xlen, returns a borrow (-1) if xlen > alen
    extern void PrimSub( size_t xlen, elem* x, size_t alen, const elem* a );

    // x *= v;  xlen is the occupied size of element array x.
    //          the array has an addition (cleared) element to allow
    //          for the expanded result.
    extern void PrimMulElem( size_t xlen, elem* x, elem v );

    // x = a * b;  where length of x is alen + blen and has been cleared
    extern void PrimMul(
        elem* x, size_t alen, const elem* a, size_t blen, const elem* b );

    // x =/ v  and  return = x % v   (v != 0 )
    extern elem PrimDivElem( size_t xlen, elem* x, elem v );

}

#endif // PRIMITIVE_H 
