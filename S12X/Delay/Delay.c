/************************************************************************************

* Delay.c
* 描述:延时函数

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.10 
* 更新时间：2013-05-25

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
