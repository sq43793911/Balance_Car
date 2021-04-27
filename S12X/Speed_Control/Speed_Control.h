/************************************************************************************

* Speed_Control.h
* 描述:速度给定，及电机输出

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.20 
* 更新时间：2013-05-25

*************************************************************************************/

/*--------------- I N C L U D E S ------------------------------------*/

#ifndef  _Speed_Control_H
#define  _Speed_Control_H

/////////////////////////////////////////
extern  int16s_t  NowSpeed_L;
extern  int16s_t  NowSpeed_R;

extern  int16s_t  ObjectSpeed;	    //目标速度
extern  int16s_t NowSpeed_L_temp;
extern  int16s_t NowSpeed_R_temp;
/////////////////////////////////////////
extern void Spd_Decision(void);
extern void Motor_Control(void);
extern void Speed_Collect(void);

#endif /* _System_Init_H */               
