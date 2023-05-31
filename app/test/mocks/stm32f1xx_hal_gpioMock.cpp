#include <stdio.h>

#include "CppUTestExt/MockSupport.h"

extern "C"
{
    #include "stm32f1xx_hal.h"
}

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
    mock( "stm32f1xx_hal_gpio" )
        .actualCall( "HAL_GPIO_WritePin" )
        .withParameter( "GPIOx", GPIOx )
        .withParameter( "GPIO_Pin", GPIO_Pin )
        .withParameter( "PinState", PinState );
}

void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    mock( "stm32f1xx_hal_gpio" )
        .actualCall( "HAL_GPIO_TogglePin" )
        .withParameter( "GPIOx", GPIOx )
        .withParameter( "GPIO_Pin", GPIO_Pin );
}