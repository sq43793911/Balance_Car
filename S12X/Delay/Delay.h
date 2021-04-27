/************************************************************************************

* Delay.h
* 描述:延时函数

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.10 
* 更新时间：2013-05-25

*************************************************************************************/

//#include  "Include_def.h"

#ifndef DELAY_H
#define DELAY_H

/*--------------- I N C L U D E S ------------------------------------*/

extern void SamplingDelay(void);
extern void Delay_us(unsigned int t);
extern void Delay_5us(unsigned int t);
extern void Delay_ms(unsigned int t);


#endif /*PORT_H END */