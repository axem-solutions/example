#include <stdint.h>

#include "stm32f1xx_hal.h"

#include "demo.h"


extern TIM_HandleTypeDef htim1;

void demo( void )
{
	printf( "prod htim: %d \n\r", &htim1 );
	HAL_TIM_Base_Start_IT( &htim1 );
}