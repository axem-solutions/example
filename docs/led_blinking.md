# LED blinking - example application

Let's create our very simple embedded application.

!!! note 

    Instead of writing it yourself, you can check out the 
    [example repo](https://github.com/axem-solutions/example) from GitHub, which is a working 
    solution.

## The specification

We have 3 requirements:

1. After power up, the LD2 user LED shall blink with a 1Hz frequency, 50% duty cycle.
2. If the LED is blinking and the user presses the B1 user button, the LED shall stop blinking.
3. If the LED is not blinking and the user presses the B1 user button, the LED shall start blinking.

## The implementation

Create the directory structure for the application.

    app
    ├── src
    └── test

Add the application source and header to the src directory:

``` c title="demo.c"
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
```

``` c title="demo.h"
#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef htim1;

void demo( void );
```

Don't forget to call the demo() function from the main() in main.c. You also need to include the 
demo.h at the private includes section  - `#include "../../app/src/demo.h"`.

``` c title="main() in main.c" hl_lines="32"
/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  demo();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
```

## The test cases

We also create some tests to try out our containerized test environment.

First we need a Makefile that describes how to build the test cases. Save it in the `app/test` 
directory.

``` make title="Makefile"
#Set this to @ to keep the makefile quiet
SILENCE = @

#---- Outputs ----#
COMPONENT_NAME = demo
	
TEST_TARGET = \
	$(COMPONENT_NAME)_tests

#--- Inputs ----#
CPP_PLATFORM = Gcc

CPPUTEST_WARNINGFLAGS += -Wall 
CPPUTEST_WARNINGFLAGS += -Wswitch-default 
CPPUTEST_WARNINGFLAGS += -Wswitch-enum  

CPPUTEST_CFLAGS += -Wextra 

CPPUTEST_ADDITIONAL_CFLAGS = \
	-DSTM32F103xB

CPPUTEST_CXXFLAGS += \
	-DSTM32F103xB

INCLUDE_DIRS = \
	$(CPPUTEST_HOME)/include/ \
	../../Drivers/STM32F1xx_HAL_Driver/Inc \
	../../Core/Inc \
	../../Drivers/CMSIS/Device/ST/STM32F1xx/Include \
	../../Drivers/CMSIS/Include

SRC_DIRS = \
	../../app/src

TEST_SRC_DIRS = \
	tests

MOCKS_SRC_DIRS = \
	mocks

CPPUTEST_USE_EXTENSIONS = Y

ifeq "$(CPPUTEST_HOME)" ""
    $(error The CPPUTEST_HOME env variable is not set.)
endif

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
```

Now we add the test cases. These are specific to the CppUTest framework and are built as C++.

``` c title="demoTest.cpp"
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
```

Finally we need to add an entry point for the test runner.

``` c title="AllTests.cpp"
#include "CppUTest/CommandLineTestRunner.h"

int main(int argc, char** argv)
{
    return CommandLineTestRunner::RunAllTests(argc, argv);
}
```