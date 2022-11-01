#include "sum.h"

unsigned int sum( unsigned char number )
{
	unsigned int sum;

	sum = 0u;

	while ( number != 0u )
	{
		sum += number;
		number--;
	}

	return sum;
}