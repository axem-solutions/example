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


TEST( demo_tests, expect_start_of_timer )
{
    mock( "stm32f1xx_hal_tim" )
        .expectOneCall( "HAL_TIM_Base_Start_IT" )
        .withParameter( "htim", &htim1 )
        .andReturnValue( HAL_OK );

    demo();

    mock( "stm32f1xx_hal_tim" ).checkExpectations();
}

TEST( demo_tests, if_error_expect_led_on )
{
    mock( "stm32f1xx_hal_tim" )
        .expectOneCall( "HAL_TIM_Base_Start_IT" )
        .withParameter( "htim", &htim1 )
        .andReturnValue( HAL_ERROR );

    mock( "stm32f1xx_hal_gpio" )
        .expectOneCall( "HAL_GPIO_WritePin" )
		.withParameter( "GPIOx", GPIOA )
		.withParameter( "GPIO_Pin", GPIO_PIN_5 )
		.withParameter( "PinState", GPIO_PIN_SET );

    demo();

    mock( "stm32f1xx_hal_tim" ).checkExpectations();
    mock( "stm32f1xx_hal_gpio" ).checkExpectations();
}

TEST_GROUP( interrupt_cb_tests )
{
    void teardown()
    {
        mock().clear();
    }
};

TEST( interrupt_cb_tests, if_not_called_with_htim1_do_nothing )
{
    HAL_TIM_PeriodElapsedCallback( NULL );
}

TEST( interrupt_cb_tests, if_called_with_htim1_toggle_led )
{
    mock( "stm32f1xx_hal_gpio" )
        .expectOneCall( "HAL_GPIO_TogglePin" )
		.withParameter( "GPIOx", GPIOA )
		.withParameter( "GPIO_Pin", GPIO_PIN_5 );

    HAL_TIM_PeriodElapsedCallback( &htim1 );

    mock( "stm32f1xx_hal_gpio" ).checkExpectations();
}