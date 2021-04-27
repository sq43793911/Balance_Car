/************************************************************************************

* System_Init.h
* 描述:寄存器配置，包括锁相环、I/O、PWM模块、实时时钟、AD

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.10 
* 更新时间：2013-05-25

*************************************************************************************/

#ifndef System_Init_H        //if no define
#define System_Init_H        //define  即如果没有定义的话，则定义。。。。(防止其他函数多次调用此头文件时而重复定义)

//#include  "Include_def.h"
/*--------------- I N C L U D E S ------------------------------------*/   
extern void FBE_Init(void);                        //初始化总线时钟 
extern void SCI0_Init(void);   
extern void PORT_Init(void);                       //初始化普通I/O端口，光电传感器的输入等
extern void CCD_IO_Init(void);                   //初始化CCD时钟控制
extern void Init_Pixel_Array(void) ;             //初始化像素值
//extern void Servo_Init(void);                      //初始化PWM01，控制舵机
extern void Forward_Init(void);                    //初始化PWM1,3和PWM5,7，控制电机
extern void ATD_Init(void);                        //初始化AD模块    
extern void RTI_Init(void);                        //初始化RTI定时中断，定时1ms    
//extern void TIM_Init(void);                        //初始化TIM输入捕捉，计数测速用                     
extern void System_Init(void);

///////////////////////////////////////////////




#endif //结束定义，配合#ifndef使用