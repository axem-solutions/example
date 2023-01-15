#include <stdint.h>

#include "demo.h"

void demo( void )
{
	HAL_StatusTypeDef hal_status;
	/* Start the timer. */
    hal_status = HAL_TIM_Base_Start_IT( &htim1 );

    if ( hal_status != HAL_OK )
    {
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET );
    }
}

void HAL_TIM_PeriodElapsedCallback( TIM_HandleTypeDef * p_htim )
{
  if ( p_htim == &htim1 )
  {
    HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );
  }
}