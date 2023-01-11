#include <stdio.h>

#include "CppUTestExt/MockSupport.h"

extern "C"
{
	#include "stm32f1xx_hal.h"
}

HAL_StatusTypeDef HAL_TIM_Base_Start_IT( TIM_HandleTypeDef * htim )
{
	return (HAL_StatusTypeDef)mock( "stm32f1xx_hal_tim" )
		.actualCall( "HAL_TIM_Base_Start_IT" )
		.withParameter( "htim", htim )
		.returnValue().getIntValue();
}

HAL_StatusTypeDef HAL_TIM_Base_Stop_IT(TIM_HandleTypeDef *htim)
{
	return (HAL_StatusTypeDef)mock( "stm32f1xx_hal_tim" )
		.actualCall( "HAL_TIM_Base_Stop_IT" )
		.withParameter( "htim", htim )
		.returnValue().getIntValue();
}