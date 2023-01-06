#include <stdint.h>

#include "stm32f1xx_hal.h"

#include "demo.h"
#include "sum.h"


void demo( void )
{
	uint32_t cica = 10u;

	sum( cica );
}