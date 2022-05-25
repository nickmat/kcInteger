/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Project: iCalc - Integer only Calculator  *  Written by: Nick Matthews  *
 *  Module: Primitive arithmatic functions   *  Date Started: 19 Nov 2007  *
 *    File: icPrim.c        Type: C Source   *  Date Revised: 27 Nov 2007  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

    Copyright (c) 2007, Nick Matthews

	Licence: GNU GPLv3
*/

#include <assert.h>
#include <kcinteger/primitive.h>

using namespace kcinteger;


//  Return zero if a == b, pos if a > b, neg if a < b 
//  Length of a and b arrays are equal.

int kcinteger::PrimCmp( size_t len, const elem* a, const elem* b )
{
	while( len ) {
		--len;
		if( a[len] > b[len] ) {
			return 1;
		}
		if( a[len] < b[len] ) {
			return -1;
		}
	}
	return 0;
}


// x += a;  where xlen >= alen, returns a carry (1) if result overflows

elem kcinteger::PrimAdd( size_t xlen, elem* x, size_t alen, const elem* a )
{
	assert( alen <= xlen );

	size_t i = 0;
	lelem k = 0;
	for( ; i < alen; i++ ) {
		k += a[i];
		k += x[i];
		x[i] = (elem) k;
		k >>= ELEM_BITS;
	}
	for( ; i < xlen; i++ ) {
		if( k == 0 ) break;
		k += x[i];
		x[i] = (elem) k;
		k >>= ELEM_BITS;
	}
	return (elem) k;
}

 // x -= a; for x > a (result must be positive)

void kcinteger::PrimSub( size_t xlen, elem* x, size_t alen, const elem* a )
{
	assert( xlen == alen ? PrimCmp( xlen, x, a ) >= 0 : xlen > alen );

	size_t j = 0;
	slelem k = 0;
	for( ; j < alen; j++ ) {
		k += (slelem) x[j] - a[j];
		x[j] = (elem) k;
		k >>= ELEM_BITS;
	}
	for( ; j < xlen; j++ ) {
		if( k == 0 ) break;
		k += x[j];
		x[j] = (elem) k;
		k >>= ELEM_BITS;
	}
}

// x *= v;  xlen is the occupied size of element array x.
//          the array has an addition (cleared) element to allow
//          for the expanded result.
// NOTE: Is this required?

void kcinteger::PrimMulElem( size_t xlen, elem* x, elem v )
{
	lelem t = 0;
	for( size_t j = 0; j < xlen; j++ )
	{
		t += (lelem) x[j] * v;
		x[j] = (elem) t;
		t >>= ELEM_BITS;
	}
	x[xlen] = (elem) t;
}

//  x = a * b;  where length of x is alen + blen and is cleared

void kcinteger::PrimMul(
	elem* x, size_t alen, const elem* a, size_t blen, const elem* b )
{
	for( size_t j = 0; j < blen; j++ )
	{
		if( b[j] == 0 )
		{
			x[j + alen] = 0;
			continue;
		}
		elem k = 0;
		for( size_t i = 0; i < alen; i++ )
		{
			lelem t = (lelem) a[i] * b[j] + x[i + j] + k;
			x[i + j] = (elem) t;
			k = (elem) (t >> ELEM_BITS);
		}
		x[j + alen] = k;
	}
}

//  x =/ v  and  return = x % v  (v != 0)

//  x = the dividend array changed to resulting quotient.
//  xlen = len of x array
//  v = the divisor element, v > 0
//  returns the resulting remainder, (an element)

elem kcinteger::PrimDivElem( size_t xlen, elem* x, elem v )
{
	assert( v != 0 );

	lelem r = 0;
    while( xlen )
    {
		--xlen;
		r = r * ELEM_BASE + x[xlen];
        x[xlen] = (elem) ( r / v );
		r %= v;
	}
	return (elem) r;
}

