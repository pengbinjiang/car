#include <msp430f169.h>
#include "type.h"
#include "delay.h"

#ifndef SRF05_H_
#define SRF05_H_

//**************�����ⲿ�����ͱ���********************

extern void delayms(unsigned int count);

#define  RISE  1
#define  FALL  0

unsigned int TA_Overflow_Cnt;         //TA���������ű���
unsigned long int Period;             //������Ž������
unsigned long int S;
unsigned int distance;
unsigned int RiseCapVal;              //������ʱ�̲���ֵ��ű���
uchar    temp,A1,A2,A3,A4;            //����ı���,��ʾ���ݴ���

void init_timerA();
void SRF05_IOinit();
void Data_do(uint);
void  LCD_DisplayDistance(long int);

#endif /* SRF05_H_ */