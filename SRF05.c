#include "SRF05.h"
//#include "lcd1602.c"

/********************************************************************
//DM430-L����Сϵͳ�����SRF05������ģ�鶯̬��ʾ���Ծ��룬TA1�������,CCI1A����
//����ͨ��1602��ʾ
//Trig�Ž�P14��Echo�Ž�P12��CCI1A��ΪP12
//������ģ��VCC��5V��GND�Ӱ��ӵ�GND
//ֱ�ӽ�1602����1602�ӿڣ�ע�ⰲװ�����ǳ���
//ע��ѡ��Һ���ĵ�Դ��λ��TFT�ӿڸ�������ѡ5V��3.3V������Һ����ѹ����ѡ��Ĭ������Ϊ5V
//���Ի�����EW430 V5.30
//���ߣ�www.avrgcc.com
//ʱ�䣺2015.09.25
********************************************************************/

unsigned char disbuff[4]="0.00";
unsigned char Edge=1;                 //��ǰ������

/********************************************************************
    ��ʼ����ʱ��A����
********************************************************************/
void init_timerA()
{
  TACTL   |= TASSEL_2+MC_2+TAIE+TACLR+ ID_3;//SMCLK,�����������ж�����������������
  TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;//����ģʽ�������ز���CCI1A���룬ͬ�������ж�����
}

/********************************************************************
    SRF05ģ����ƿڳ�ʼ������
********************************************************************/
void SRF05_IOinit()
{
  P1DIR |= BIT4;                  //P1.4���
  P1DIR &=~ BIT2;                 //P1.2����
  P1SEL =  BIT2;                  //P1.2�ڶ����ܣ���������

  P1OUT &=~BIT4;                  //����P14���ƶ�
  delay_ms(1000);
}

//*************************************************************************
//      ����ֵ��������
//*************************************************************************
void Data_do(uint temp_d)
{
  uint temp_1,temp_2;
  A1=temp_d/1000;                       //�ֳ�ǧ���٣�ʮ���͸�λ
  temp_1=temp_d%1000;
  A2=temp_1/100;
  temp_2=temp_1%100;
  A3=temp_2/10;
  A4=temp_2%10;
}

/********************************************************************
                      ����ֵ��ʾ����
********************************************************************/
void  LCD_DisplayDistance(long int distance)
{
  Data_do(distance);        //��ʾλ����ȡ
  LCD_write_char(0x0a,1,0x30+A1);
  LCD_write_char(0x0b,1,'.');
  LCD_write_char(0x0c,1,0x30+A2);
  LCD_write_char(0x0d,1,0X30+A3);
  LCD_write_char(0x0e,1,0X30+A4);
  LCD_write_char(0x0f,1,'m');
}


/********************************************************************
                      ��ʱ��A�������
********************************************************************/
//��ʱ��A�������
#pragma vector=TIMERA1_VECTOR
__interrupt void Timer_A(void)
{

  switch(TAIV)
  {
    case 2 :if(Edge==RISE)
              {
                RiseCapVal = TACCR1;
                TACCTL1 |= CAP+CM_2+CCIS_0+SCS+CCIE;//��Ϊ�½��ز���
                //TACCTL1 |= CAP+CM_1+CCIS_0+SCS+CCIE;//��Ϊ�����ز���
                Edge = FALL;//�½��ز����־
              }
             else
              {

                _DINT();

                Period = TACCR1-RiseCapVal;
                S=(Period*17)/100;
                TACCR1 = 0;
                TACCTL1|= CAP+CM_1+CCIS_0+SCS+CCIE;//��Ϊ�����ز���
                Edge = RISE;//�����ز����־
                _EINT();
              }
             break;
    case 4 : break;
    case 10: TA_Overflow_Cnt++;
             break;
  }
}