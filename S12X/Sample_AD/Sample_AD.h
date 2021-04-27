/************************************************************************************

* Sample_AD.h
* 描述: AD寄存器读取

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.10 
* 更新时间：2013-05-25

*************************************************************************************/

/*--------------- I N C L U D E S ------------------------------------*/

#ifndef _SAMPLE_AD_H
#define _SAMPLE_AD_H

/////////////////////////////////////////////////
extern  int16s_t   AD_Value[8]; 

/////////////////////////////////////////////////
extern void AD_Enable(void);
extern void AD_Collect(void);
extern int16u_t  AD_Measure12(int8u_t Channel);
extern int16u_t  AD_Measure10(int8u_t Channel) ;
extern int16u_t  AD_Measure11(int8u_t Channel)  ;
extern int16u_t  ADCValue1(int8u_t channel);
extern int16u_t  ADCValue2(int8u_t channel);

#endif /*PORT_H END */