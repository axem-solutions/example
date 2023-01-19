#include <stdio.h>
#include <string.h>

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
    void setup ()
    {
        memset( &htim1, 0u, sizeof( htim1 ) );
    }

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

TEST( interrupt_cb_tests, if_tim_called_with_not_htim1_do_nothing )
{
    HAL_TIM_PeriodElapsedCallback( NULL );
}

TEST( interrupt_cb_tests, if_tim_called_with_htim1_toggle_led )
{
    mock( "stm32f1xx_hal_gpio" )
        .expectOneCall( "HAL_GPIO_TogglePin" )
		.withParameter( "GPIOx", GPIOA )
		.withParameter( "GPIO_Pin", GPIO_PIN_5 );

    HAL_TIM_PeriodElapsedCallback( &htim1 );

    mock( "stm32f1xx_hal_gpio" ).checkExpectations();
}

TEST( interrupt_cb_tests, if_exti_called_with_not_pin13_do_nothing )
{
    HAL_GPIO_EXTI_Callback( 0 );
}

TEST( interrupt_cb_tests, if_exti_called_with_pin13_and_led_blinking_then_stop )
{
    mock( "stm32f1xx_hal_tim" )
        .expectOneCall( "HAL_TIM_Base_Stop_IT" )
        .withParameter( "htim", &htim1 )
        .andReturnValue( HAL_OK );
    mock( "stm32f1xx_hal_gpio" )
        .expectOneCall( "HAL_GPIO_WritePin" )
		.withParameter( "GPIOx", GPIOA )
		.withParameter( "GPIO_Pin", GPIO_PIN_5 )
		.withParameter( "PinState", GPIO_PIN_RESET );

    htim1.State = HAL_TIM_STATE_BUSY;

    HAL_GPIO_EXTI_Callback( GPIO_PIN_13 );

    mock( "stm32f1xx_hal_tim" ).checkExpectations();
    mock( "stm32f1xx_hal_gpio" ).checkExpectations();
}

TEST( interrupt_cb_tests, if_exti_called_with_pin13_and_led_not_blinking_then_start )
{
    TIM_TypeDef g_register_base;

    memset( &g_register_base, 0u, sizeof( g_register_base ) );

    mock( "stm32f1xx_hal_tim" )
        .expectOneCall( "HAL_TIM_Base_Start_IT" )
        .withParameter( "htim", &htim1 )
        .andReturnValue( HAL_OK );
    mock( "stm32f1xx_hal_gpio" )
        .expectOneCall( "HAL_GPIO_WritePin" )
		.withParameter( "GPIOx", GPIOA )
		.withParameter( "GPIO_Pin", GPIO_PIN_5 )
		.withParameter( "PinState", GPIO_PIN_SET );

    htim1.State = HAL_TIM_STATE_READY;
    htim1.Instance = &g_register_base;
    /* The timer already run previously, so its counter value can be not 0.*/
    htim1.Instance->CNT = 0x5A5A;

    HAL_GPIO_EXTI_Callback( GPIO_PIN_13 );

    mock( "stm32f1xx_hal_tim" ).checkExpectations();
    mock( "stm32f1xx_hal_gpio" ).checkExpectations();

    /* The timer must start the counting from 0u. */
    CHECK_EQUAL( 0u, htim1.Instance->CNT );
}

TEST( interrupt_cb_tests, if_exti_called_and_tim_start_fails_expect_led_on )
{
    TIM_TypeDef g_register_base;

    memset( &g_register_base, 0u, sizeof( g_register_base ) );

    mock( "stm32f1xx_hal_tim" )
        .expectOneCall( "HAL_TIM_Base_Start_IT" )
        .withParameter( "htim", &htim1 )
        .andReturnValue( HAL_ERROR );
    mock( "stm32f1xx_hal_gpio" )
        .expectNCalls( 2u, "HAL_GPIO_WritePin" )
		.withParameter( "GPIOx", GPIOA )
		.withParameter( "GPIO_Pin", GPIO_PIN_5 )
		.withParameter( "PinState", GPIO_PIN_SET );

    htim1.State = HAL_TIM_STATE_READY;
    htim1.Instance = &g_register_base;

    HAL_GPIO_EXTI_Callback( GPIO_PIN_13 );

    mock( "stm32f1xx_hal_tim" ).checkExpectations();
    mock( "stm32f1xx_hal_gpio" ).checkExpectations();
}

TEST( interrupt_cb_tests, if_exti_called_and_tim_state_is_invalid_expect_led_on )
{
    mock( "stm32f1xx_hal_gpio" )
        .expectOneCall( "HAL_GPIO_WritePin" )
		.withParameter( "GPIOx", GPIOA )
		.withParameter( "GPIO_Pin", GPIO_PIN_5 )
		.withParameter( "PinState", GPIO_PIN_SET );

    htim1.State = HAL_TIM_STATE_ERROR;

    HAL_GPIO_EXTI_Callback( GPIO_PIN_13 );

    mock( "stm32f1xx_hal_gpio" ).checkExpectations();
}