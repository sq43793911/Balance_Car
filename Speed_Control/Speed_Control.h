/************************************************************************************

* Speed_Control.h
* ����:�ٶȸ�������������

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.20 
* ����ʱ�䣺2013-05-25

*************************************************************************************/

/*--------------- I N C L U D E S ------------------------------------*/

#ifndef  _Speed_Control_H
#define  _Speed_Control_H

/////////////////////////////////////////
extern  int16s_t  NowSpeed_L;
extern  int16s_t  NowSpeed_R;

extern  int16s_t  ObjectSpeed;	    //Ŀ���ٶ�
extern  int16s_t NowSpeed_L_temp;
extern  int16s_t NowSpeed_R_temp;
/////////////////////////////////////////
extern void Spd_Decision(void);
extern void Motor_Control(void);
extern void Speed_Collect(void);

#endif /* _System_Init_H */               
