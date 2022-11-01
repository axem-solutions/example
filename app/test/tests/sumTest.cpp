//- ------------------------------------------------------------------
//-    Copyright (c) James W. Grenning -- All Rights Reserved         
//-    For use by owners of Test-Driven Development for Embedded C,   
//-    and attendees of Renaissance Software Consulting, Co. training 
//-    classes.                                                       
//-                                                                   
//-    Available at http://pragprog.com/titles/jgade/                 
//-        ISBN 1-934356-62-X, ISBN13 978-1-934356-62-3               
//-                                                                   
//-    Authorized users may use this source code in your own          
//-    projects, however the source code may not be used to           
//-    create training material, courses, books, articles, and        
//-    the like. We make no guarantees that this source code is       
//-    fit for any purpose.                                           
//-                                                                   
//-    www.renaissancesoftware.net james@renaissancesoftware.net      
//- ------------------------------------------------------------------


#include "string.h"
#include "CppUTest/TestHarness.h"

extern "C"
{
    #include "../../src/sum.h"
}

TEST_GROUP(sum_tests)
{
    void setup()
    {
    }
    void destroy()
    {
    }
};

TEST(sum_tests, SumOf0is0)
{
    BYTES_EQUAL( 0u, sum( 0u ) );
}

TEST(sum_tests, SumOf1is1)
{
    BYTES_EQUAL( 1u, sum( 1u ) );
}

TEST(sum_tests, SumOf2is3)
{
    BYTES_EQUAL( 3u, sum( 2u ) );
}

TEST(sum_tests, SumOf3is6)
{
    BYTES_EQUAL( 6u, sum( 3u ) );
}

TEST(sum_tests, SumOf4is10)
{
    BYTES_EQUAL( 10u, sum( 4u ) );
}

TEST(sum_tests, SumOf255is32640)
{
    BYTES_EQUAL( 32640u, sum( 255u ) );
}