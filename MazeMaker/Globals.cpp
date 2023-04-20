#include "globals.h"
#include <string>
#include <time.h>

Globals::Globals(void)
{
	srand(time(NULL));
}

int Globals::randomgen(int min, int max)
{
    return rand()%max + min;
}