/************************************************************************************

* Speed_PID.h
* 描述:速度PI控制，及速度分级输出

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.10 
* 更新时间：2013-05-25

*************************************************************************************/

/*--------------- I N C L U D E S ------------------------------------*/

#ifndef _SPEED_PID_H
#define _SPEED_PID_H

/////////////////////////////////////////////////
extern  int16s_t  NowSpeed_L;         //左测速
extern  int16s_t  NowSpeed_R;         //右测速
//extern  int16s_t  NowSpeed_L_temp;
//extern  int16s_t  NowSpeed_R_temp;
extern  int16s_t  NowSpeed_L_history1;
extern  int16s_t  NowSpeed_R_history1;
extern  int16s_t g_nCarMtionPeriod;

extern  int16s_t  PI_Out;

/////////////////////////////////////////////////
extern  int16s_t g_nCarMtionCount;    //速度控制时间片计数

/////////////////////////////////////////////////
extern void Speed_PI(void);
extern void Speed_PI_OUT(void);

#endif /*PORT_H END */