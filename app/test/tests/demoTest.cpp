#include <stdio.h>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"


extern "C"
{
    /* Header for unit under test. */
    #include "../../src/demo.h"

    /* Headers for mocked functions. */
    #include "stm32f1xx_hal.h"

    TIM_HandleTypeDef htim1;
}

TEST_GROUP( demo_tests )
{
    void teardown()
    {
        mock().clear();
    }
};


TEST( demo_tests, expect_HAL_TIM_Base_Start_IT_with_NULL )
{
    printf( "test htim: %x\r\n", &htim1 );

    mock( "stm32f1xx_hal_tim" )
        .expectOneCall( "HAL_TIM_Base_Start_IT" )
        .withParameter( "htim", &htim1 )
        .andReturnValue( HAL_OK );

    demo();

    mock( "stm32f1xx_hal_tim" )
        .checkExpectations();
}