#include <stdint.h>

#include "demo.h"

static void demo_error( void);

static void demo_error( void)
{
    HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET );
}

void demo( void )
{
	HAL_StatusTypeDef hal_status;
	/* Start the timer. */
    hal_status = HAL_TIM_Base_Start_IT( &htim1 );

    if ( hal_status != HAL_OK )
    {
        demo_error();
    }
}

void HAL_TIM_PeriodElapsedCallback( TIM_HandleTypeDef * p_htim )
{
  if ( p_htim == &htim1 )
  {
    HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_StatusTypeDef hal_status;

    hal_status = HAL_OK;

    if ( GPIO_PIN_13 == GPIO_Pin )
    {
      if ( htim1.State == HAL_TIM_STATE_BUSY )
      {
        (void)HAL_TIM_Base_Stop_IT( &htim1 );
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_RESET );
      }
      else if ( htim1.State == HAL_TIM_STATE_READY )
      {
        __HAL_TIM_SET_COUNTER( &htim1, 0u );
        hal_status = HAL_TIM_Base_Start_IT( &htim1 );
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET );
      }
      else
      {
        hal_status = HAL_ERROR;
      }
    }

    if ( hal_status != HAL_OK )
    {
        demo_error();
    }
}
