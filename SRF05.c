#include "SRF05.h"
//#include "lcd1602.c"

/********************************************************************
//DM430-L型最小系统板控制SRF05超声波模块动态显示测试距离，TA1捕获测量,CCI1A输入
//距离通过1602显示
//Trig脚接P14，Echo脚接P12，CCI1A即为P12
//超声波模块VCC接5V，GND接板子的GND
//直接将1602插入1602接口，注意安装方向，是朝外
//注意选择液晶的电源，位于TFT接口附近，可选5V或3.3V，根据液晶电压进行选择，默认设置为5V
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2015.09.25
********************************************************************/

unsigned char disbuff[4]="0.00";
unsigned char Edge=1;                 //当前触发沿

/********************************************************************
    初始化定时器A函数
********************************************************************/
void init_timerA()
{
  TACTL   |= TASSEL_2+MC_2+TAIE+TACLR+ ID_3;//SMCLK,连续计数，中断允许，计数器清零
  TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;//捕获模式，上升沿捕获，CCI1A输入，同步捕获，中断允许
}

/********************************************************************
    SRF05模块控制口初始化函数
********************************************************************/
void SRF05_IOinit()
{
  P1DIR |= BIT4;                  //P1.4输出
  P1DIR &=~ BIT2;                 //P1.2输入
  P1SEL =  BIT2;                  //P1.2第二功能，捕获输入

  P1OUT &=~BIT4;                  //清零P14控制端
  delay_ms(1000);
}

//*************************************************************************
//      距离值处理函数
//*************************************************************************
void Data_do(uint temp_d)
{
  uint temp_1,temp_2;
  A1=temp_d/1000;                       //分出千，百，十，和个位
  temp_1=temp_d%1000;
  A2=temp_1/100;
  temp_2=temp_1%100;
  A3=temp_2/10;
  A4=temp_2%10;
}

/********************************************************************
                      距离值显示函数
********************************************************************/
void  LCD_DisplayDistance(long int distance)
{
  Data_do(distance);        //显示位数提取
  LCD_write_char(0x0a,1,0x30+A1);
  LCD_write_char(0x0b,1,'.');
  LCD_write_char(0x0c,1,0x30+A2);
  LCD_write_char(0x0d,1,0X30+A3);
  LCD_write_char(0x0e,1,0X30+A4);
  LCD_write_char(0x0f,1,'m');
}


/********************************************************************
                      定时器A服务程序
********************************************************************/
//定时器A服务程序
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{

  switch(TAIV)
  {
    case 2 :if(Edge==RISE)
              {
                RiseCapVal = TACCR1;
                TACCTL1 |= CAP+CM_2+CCIS_0+SCS+CCIE;//改为下降沿捕获
                //TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;//改为上升沿捕获
                Edge = FALL;//下降沿捕获标志
              }
             else
              {

                _DINT();

                Period = TACCR1-RiseCapVal;
                S=(Period*17)/100;
                TACCR1 = 0;
                TACCTL1|= CAP+CM_1+CCIS_0+SCS+CCIE;//改为上升沿捕获
                Edge = RISE;//上升沿捕获标志
                _EINT();
              }
             break;
    case 4 : break;
    case 10: TA_Overflow_Cnt++;
             break;
  }
}
