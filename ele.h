#include <msp430f169.h>
#include "type.h"

#ifndef ELE_H_
#define ELE_H_

uchar bb,j;

void ele_init();
void timer_B_init();
void forward();
void left();
void right();
void retreat();
void stop();

#endif /* ELE_H_ */
