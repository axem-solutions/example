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
#include "CppUTestExt/MockSupport.h"

extern "C"
{
    #include "../../src/demo.h"
}

TEST_GROUP( demo_tests )
{
    void setup()
    {
    }
    void destroy()
    {
        // mock().clear();
    }
};

void sum( unsigned char number )
{
    // mock().actualCall( "sum" );
}

TEST( demo_tests, expect_sum_call )
{
    uint32_t cica;

    cica = 10u;
    // mock().expectOneCall( "sum" );
    // demo();
    // mock().checkExpectations();
}