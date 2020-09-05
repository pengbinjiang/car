#include <msp430f169.h>
#include "lcd1602.h"
#include "SRF05.h"
#include "UART.h"
#include "type.h"
#include "delay.h"
#include "clock.h"
#include "ele.h"

/********************************************************************
                      主函数
********************************************************************/
main()
{
    WDT_Init();                        //看门狗设置
    Clock_Init();                      //系统时钟设置
    Port_init();                       //系统初始化，设置IO口属性
    LCD_init();                         //液晶参数初始化设置
    LCD_clear();                        //清屏
    LCD_Desk();
    ele_init();
    timer_B_init();
    SRF05_IOinit();
    init_timerA();
    
    TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;         //改为上升沿捕获
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

        P1OUT |= BIT4;              //高电平至少10us启动超声波测距
        delay_ms(10);
        P1OUT &=~BIT4;              //建议大于60ms的测量周期
        delay_ms(70);
        LCD_DisplayDistance(S);      //动态显示距离，单位m

        if(j == 1)
        {
            P1OUT |= BIT4;              //高电平至少10us启动超声波测距
            delay_ms(10);
            P1OUT &=~BIT4;              //建议大于60ms的测量周期
            delay_ms(70);

            LCD_DisplayDistance(S);      //动态显示距离，单位m

        if(S>=300) forward();
        if(S<200)
        {
            stop();
            delay_ms(10);
            do{
                retreat();

                P1OUT |= BIT4;              //高电平至少10us启动超声波测距
                delay_ms(10);
                P1OUT &=~BIT4;              //建议大于60ms的测量周期
                delay_ms(70);
                LCD_DisplayDistance(S);      //动态显示距离，单位m
            }while(S<300);

            stop();
            delay_ms(10);

            left();
            delay_ms(200);
        }
        }
    }
    
}
