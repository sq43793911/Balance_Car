/************************************************************************************

* Balance_Control.h
* ����:�ǶȽ��ٶ��˲�������ģֱ������

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.10 
* ����ʱ�䣺2013-05-25

*************************************************************************************/

/*--------------- I N C L U D E S ------------------------------------*/

#ifndef  _BALANCE_CONTROL_H
#define  _BALANCE_CONTROL_H

/////////////////////////////////////////
extern  int16s_t  g_nCarGyroVal;         //�Ǽ��ٶ�
extern  int16s_t  g_nCarAngle;           //����Ƕ�
extern  int16s_t  g_nLeftMotorOut;
extern  int16s_t  g_nRightMotorOut;

/////////////////////////////////////////
extern  void  CarVoltageGet(void);
extern  void  CarAngleControl(void);

#endif /* _System_Init_H */
