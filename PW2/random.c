#include <stdlib.h>
#include "random.h"

float random01 () {
	return (float)(rand()%10001)/10000;
}

float random0n (int n) {
	return random01()*n;
}

int tossOfOneDice () {
	return rand()%6+1;
}

int tossOfTwoDice () {
	return (tossOfOneDice() + tossOfOneDice());
}