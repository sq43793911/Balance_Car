/************************************************************************************

* Balance_Control.h
* 描述:角度角速度滤波，及车模直立控制

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.10 
* 更新时间：2013-05-25

*************************************************************************************/

/*--------------- I N C L U D E S ------------------------------------*/

#ifndef  _BALANCE_CONTROL_H
#define  _BALANCE_CONTROL_H

/////////////////////////////////////////
extern  int16s_t  g_nCarGyroVal;         //角加速度
extern  int16s_t  g_nCarAngle;           //车体角度
extern  int16s_t  g_nLeftMotorOut;
extern  int16s_t  g_nRightMotorOut;

/////////////////////////////////////////
extern  void  CarVoltageGet(void);
extern  void  CarAngleControl(void);

#endif /* _System_Init_H */
