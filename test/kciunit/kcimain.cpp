

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <kcinteger/primitive.h>

using namespace kcinteger;

TEST_CASE( "Test PrimCmp function", "[PrimCmp]" )
{
    elem a[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    elem b[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    REQUIRE( PrimCmp( 10, a, b ) == 0 );

    a[0] = 5;
    b[0] = 4;
    REQUIRE( PrimCmp( 10, a, b ) > 0 );
    b[0] = 6;
    REQUIRE( PrimCmp( 10, a, b ) < 0 );
    b[0] = 5;
    REQUIRE( PrimCmp( 10, a, b ) == 0 );

    a[9] = 5;
    b[9] = 4;
    REQUIRE( PrimCmp( 10, a, b ) > 0 );
    b[9] = 6;
    REQUIRE( PrimCmp( 10, a, b ) < 0 );
    b[9] = 5;
    REQUIRE( PrimCmp( 10, a, b ) == 0 );
}

TEST_CASE( "Test PrimAdd function", "[PrimAdd]" )
{
    elem x[3] = { 0xffffffff, 0xffffffff, 0xffffffff };
    elem a[3] = { 0xffffffff, 0xffffffff, 0xffffffff };

    elem result = PrimAdd( 3, x, 3, a );
    REQUIRE( result == 1 );
    REQUIRE( x[0] == 0xfffffffe );
    REQUIRE( x[1] == 0xffffffff );
    REQUIRE( x[2] == 0xffffffff );

    x[0] = 0xffffffff;
    x[1] = 0;
    x[2] = 1;
    result = PrimAdd( 3, x, 1, a );
    REQUIRE( result == 0 );
    REQUIRE( x[0] == 0xfffffffe );
    REQUIRE( x[1] == 1 );
    REQUIRE( x[2] == 1 );
}

TEST_CASE( "Test PrimSub function", "[PrimSub]" )
{
    elem x[3] = { 0xffffffff, 0xffffffff, 0xffffffff };
    elem a[3] = { 0xffffffff, 0xffffffff, 0xffffffff };

    PrimSub( 3, x, 3, a );
    REQUIRE( x[0] == 0 );
    REQUIRE( x[1] == 0 );
    REQUIRE( x[2] == 0 );

    x[0] = 0xfffffffe;
    x[1] = 0xffffffff;
    x[2] = 0xffffffff;
    PrimSub( 3, x, 1, a );
    REQUIRE( x[0] == 0xffffffff );
    REQUIRE( x[1] == 0xfffffffe );
    REQUIRE( x[2] == 0xffffffff );
}

TEST_CASE( "Test PrimMulElem function", "[PrimMulElem]" )
{
    elem x[4] = { 0xffffffff, 0xffffffff, 0xffffffff, 0x0 };

    PrimMulElem( 3, x, 0 );
    REQUIRE( x[0] == 0x0 );
    REQUIRE( x[1] == 0x0 );
    REQUIRE( x[2] == 0x0 );
    REQUIRE( x[3] == 0x0 );

    x[0] = 0xffffffff;
    x[1] = 0xffffffff;
    x[2] = 0xffffffff;
    PrimMulElem( 3, x, 1 );
    REQUIRE( x[0] == 0xffffffff );
    REQUIRE( x[1] == 0xffffffff );
    REQUIRE( x[2] == 0xffffffff );
    REQUIRE( x[3] == 0x0 );

    PrimMulElem( 3, x, 2 );
    REQUIRE( x[0] == 0xfffffffe );
    REQUIRE( x[1] == 0xffffffff );
    REQUIRE( x[2] == 0xffffffff );
    REQUIRE( x[3] == 0x1 );

    x[0] = 0xffffffff;
    x[1] = 0xffffffff;
    x[2] = 0xffffffff;
    x[3] = 0x0;
    PrimMulElem( 3, x, 0xffffffff );
    REQUIRE( x[0] == 0x1 );
    REQUIRE( x[1] == 0xffffffff );
    REQUIRE( x[2] == 0xffffffff );
    REQUIRE( x[3] == 0xfffffffe );
}

TEST_CASE( "Test PrimMul function", "[PrimMul]" )
{
    elem x[5] = { 0, 0, 0, 0, 0 };
    elem a[3] = { 0xffffffff, 0xffffffff, 0xffffffff };
    elem b[2] = { 0, 0 };
    PrimMul( x, 3, a, 1, b );
    REQUIRE( x[0] == 0 );
    REQUIRE( x[1] == 0 );
    REQUIRE( x[2] == 0 );
    REQUIRE( x[3] == 0 );
    REQUIRE( x[4] == 0 );

    b[0] = 1;
    PrimMul( x, 3, a, 1, b );
    REQUIRE( x[0] == 0xffffffff );
    REQUIRE( x[1] == 0xffffffff );
    REQUIRE( x[2] == 0xffffffff );
    REQUIRE( x[3] == 0 );
    REQUIRE( x[4] == 0 );

    x[0] = x[1] = x[2] = x[3] = x[4] = 0;
    b[0] = 2;
    PrimMul( x, 3, a, 1, b );
    REQUIRE( x[0] == 0xfffffffe );
    REQUIRE( x[1] == 0xffffffff );
    REQUIRE( x[2] == 0xffffffff );
    REQUIRE( x[3] == 1 );
    REQUIRE( x[4] == 0 );

    x[0] = x[1] = x[2] = x[3] = x[4] = 0;
    b[0] = b[1] = 0xffffffff;
    PrimMul( x, 3, a, 2, b );
    REQUIRE( x[0] == 1 );
    REQUIRE( x[1] == 0 );
    REQUIRE( x[2] == 0xffffffff );
    REQUIRE( x[3] == 0xfffffffe );
    REQUIRE( x[4] == 0xffffffff );
}
