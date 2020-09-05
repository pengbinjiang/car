#include "ele.h"
#include "lcd1602.h"

#pragma vector = TIMERB0_VECTOR
__interrupt void Timer_B(void)
{
    bb++;
    if(bb == 800)
    {
        bb = 0;
    }
}

void ele_init()
{
    P4DIR |= 0x3c;
    P4SEL |= 0x3c;
}

void timer_B_init()
{
    TBCCR0 = 10000;
    TBCTL = CNTL_0 + TASSEL_2 + MC_1;
}

void forward()
{
    LCD_write_str(0x00,1,"forw");
    TBCCR0 = 10000;
    TBCCTL0 = CCIE;
    TBCCTL2 = OUTMOD_7;
    TBCCR2 = 0;
    TBCCTL3 = OUTMOD_7;
    TBCCR3 = 5000;
    TBCCTL4 = OUTMOD_7;
    TBCCR4 = 5000;
    TBCCTL5 = OUTMOD_7;
    TBCCR5 = 0;
}

void left()
{
    LCD_write_str(0x00,1,"left");
    TBCCR0 = 10000;
    TBCCTL0 = CCIE;
    TBCCTL2 = OUTMOD_7;
    TBCCR2 = 0;
    TBCCTL3 = OUTMOD_7;
    TBCCR3 = 0;
    TBCCTL4 = OUTMOD_7;
    TBCCR4 = 5000;
    TBCCTL5 = OUTMOD_7;
    TBCCR5 = 0;
}

void right()
{
    LCD_write_str(0x00,1,"righ");
    TBCCR0 = 10000;
    TBCCTL0 = CCIE;
    TBCCTL2 = OUTMOD_7;
    TBCCR2 = 0;
    TBCCTL3 = OUTMOD_7;
    TBCCR3 = 5000;
    TBCCTL4 = OUTMOD_7;
    TBCCR4 = 0;
    TBCCTL5 = OUTMOD_7;
    TBCCR5 = 0;
}

void retreat()
{
    LCD_write_str(0x00,1,"retr");
    TBCCR0 = 10000;
    TBCCTL0 = CCIE;
    TBCCTL2 = OUTMOD_7;
    TBCCR2 = 5000;
    TBCCTL3 = OUTMOD_7;
    TBCCR3 = 0;
    TBCCTL4 = OUTMOD_7;
    TBCCR4 = 0;
    TBCCTL5 = OUTMOD_7;
    TBCCR5 = 5000;
}

void stop()
{
    LCD_write_str(0x00,1,"stop");
    TBCCR0 = 10000;
    TBCCTL0 = CCIE;
    TBCCTL2 = OUTMOD_7;
    TBCCR2 = 0;
    TBCCTL3 = OUTMOD_7;
    TBCCR3 = 0;
    TBCCTL4 = OUTMOD_7;
    TBCCR4 = 0;
    TBCCTL5 = OUTMOD_7;
    TBCCR5 = 0;
}
