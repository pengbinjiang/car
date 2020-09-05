#include <msp430f169.h>
#include "type.h"
#include "delay.h"

#ifndef SRF05_H_
#define SRF05_H_

//**************声明外部函数和变量********************

extern void delayms(unsigned int count);

#define  RISE  1
#define  FALL  0

unsigned int TA_Overflow_Cnt;         //TA溢出次数存放变量
unsigned long int Period;             //脉宽存放结果变量
unsigned long int S;
unsigned int distance;
unsigned int RiseCapVal;              //上升沿时刻捕获值存放变量
uchar    temp,A1,A2,A3,A4;            //定义的变量,显示数据处理

void init_timerA();
void SRF05_IOinit();
void Data_do(uint);
void  LCD_DisplayDistance(long int);

#endif /* SRF05_H_ */
