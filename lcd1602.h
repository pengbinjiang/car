#include <msp430f169.h>
#include "type.h"
#include "delay.h"

#ifndef lcd1602_H_
#define lcd1602_H_

//����/12864Һ��/1602Һ�������ݿڣ���Һ������
#define DataDIR         P6DIR                     //���ݿڷ���
#define DataPort        P6OUT                     //P4��Ϊ���ݿ�

//12864/1602Һ�����ƹܽ�
#define RS_CLR          P5OUT &= ~BIT5           //RS�õ�
#define RS_SET          P5OUT |=  BIT5           //RS�ø�

#define RW_CLR          P5OUT &= ~BIT6           //RW�õ�
#define RW_SET          P5OUT |=  BIT6           //RW�ø�

#define EN_CLR          P5OUT &= ~BIT7           //E�õ�
#define EN_SET          P5OUT |=  BIT7           //E�ø�

#define PSB_CLR         P5OUT &= ~BIT0            //PSB�õͣ����ڷ�ʽ
#define PSB_SET         P5OUT |=  BIT0            //PSB�øߣ����ڷ�ʽ

#define RESET_CLR   P5OUT &= ~BIT1            //RST�õ�
#define RESET_SET   P5OUT |= BIT1             //RST�ø�

void WDT_Init();
void Port_init();
void LCD_write_com(unsigned char);
void LCD_write_data(unsigned char);
void LCD_clear(void);
void LCD_write_str(unsigned char,unsigned char,unsigned char *);
void LCD_write_char(unsigned char,unsigned char,unsigned char);
void LCD_init(void);
void LCD_Desk(void);

#endif /* lcd1602_H_ */
