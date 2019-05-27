/************************************************************************************

* Delay.c
* ����:��ʱ����

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.10 
* ����ʱ�䣺2013-05-25

*************************************************************************************/

#include  "Include_def.h"

/*--------------- I N C L U D E S ------------------------------------*/

/* CPU delay 200ns at 80M bus clock */

void SamplingDelay(void) \
    { __asm(nop); __asm(nop); __asm(nop); __asm(nop);\
      __asm(nop); __asm(nop); __asm(nop); __asm(nop);\

    }


void Delay_us(unsigned int t) 
{
    while(t--);   
}



void Delay_5us(unsigned int t) 
{
    unsigned int i;
    while(t--) 
    {
       for(i = 0;i<20;i++);      
    }
  
}



void Delay_ms(unsigned int t)
{
    unsigned int i;
    while(t--)
    {
        for(i = 0;i < 6000;i++);
    }
}
