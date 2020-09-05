#include <msp430f169.h>
#include "lcd1602.h"
#include "SRF05.h"
#include "UART.h"
#include "type.h"
#include "delay.h"
#include "clock.h"
#include "ele.h"

/********************************************************************
                      ������
********************************************************************/
main()
{
    WDT_Init();                        //���Ź�����
    Clock_Init();                      //ϵͳʱ������
    Port_init();                       //ϵͳ��ʼ��������IO������
    LCD_init();                         //Һ��������ʼ������
    LCD_clear();                        //����
    LCD_Desk();
    ele_init();
    timer_B_init();
    SRF05_IOinit();
    init_timerA();
    
    TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;         //��Ϊ�����ز���
    UART_Init();
    _EINT();
    keyvalue = 0;
    j = 0;
    while(1)
    {
        if(keyvalue == 5) j = 0,stop();
        if(keyvalue == 6) j = 1;
        if(j == 0)
        {
            switch(keyvalue)
            {
                case 0: stop();break;
                case 1: forward();break;
                case 2: left();break;
                case 3: right();break;
                case 4: retreat();break;
                default: break;
            }
        }

        P1OUT |= BIT4;              //�ߵ�ƽ����10us�������������
        delay_ms(10);
        P1OUT &=~BIT4;              //�������60ms�Ĳ�������
        delay_ms(70);
        LCD_DisplayDistance(S);      //��̬��ʾ���룬��λm

        if(j == 1)
        {
            P1OUT |= BIT4;              //�ߵ�ƽ����10us�������������
            delay_ms(10);
            P1OUT &=~BIT4;              //�������60ms�Ĳ�������
            delay_ms(70);

            LCD_DisplayDistance(S);      //��̬��ʾ���룬��λm

        if(S>=300) forward();
        if(S<200)
        {
            stop();
            delay_ms(10);
            do{
                retreat();

                P1OUT |= BIT4;              //�ߵ�ƽ����10us�������������
                delay_ms(10);
                P1OUT &=~BIT4;              //�������60ms�Ĳ�������
                delay_ms(70);
                LCD_DisplayDistance(S);      //��̬��ʾ���룬��λm
            }while(S<300);

            stop();
            delay_ms(10);

            left();
            delay_ms(200);
        }
        }
    }
    
}
