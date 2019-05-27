/************************************************************************************

* Direction_Control.h
* 描述:赛道单边黑线提取及方向控制

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.00 
* 更新时间：2013-06-29

*************************************************************************************/

#ifndef Direction_Control_H        //if no define
#define Direction_Control_H        //define  即如果没有定义的话，则定义。。。。(防止其他函数多次调用此头文件时而重复定义)

///////////////////////////////////////////////////////////////////////

extern void  DirectionControl(void) ;
extern void  DirectionControlOutput(void); 

////////////////////////////////////////////////////////
extern int8u_t  stopValue;
extern int16s_t DirectionOut_L;
extern int16s_t DirectionOut_R;
extern int16s_t g_nCarDirCount;
extern int16s_t g_nCarDirPeriod;


 #endif 