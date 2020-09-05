#include<msp430f169.h>
#include"type.h"
#include"delay.h"

#ifndef UART_H_
#define UART_H_

uchar keyvalue;

//���ڲ����ʼ��㣬��BRCLK=CPU_Fʱ������Ĺ�ʽ���Լ��㣬����Ҫ�������ü����Ƶϵ��
#define baud           9600                                //���ò����ʵĴ�С
#define baud_setting   (uint)((ulong)CPU_F/((ulong)baud))  //�����ʼ��㹫ʽ
#define baud_h         (uchar)(baud_setting>>8)            //��ȡ��λ
#define baud_l         (uchar)(baud_setting)               //��λ

uchar keyvalue;

void UART_Init();
void Send_Byte(uchar data);

#endif /* UART_H_ */
