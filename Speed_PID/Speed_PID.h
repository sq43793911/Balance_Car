/************************************************************************************

* Speed_PID.h
* ����:�ٶ�PI���ƣ����ٶȷּ����

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.10 
* ����ʱ�䣺2013-05-25

*************************************************************************************/

/*--------------- I N C L U D E S ------------------------------------*/

#ifndef _SPEED_PID_H
#define _SPEED_PID_H

/////////////////////////////////////////////////
extern  int16s_t  NowSpeed_L;         //�����
extern  int16s_t  NowSpeed_R;         //�Ҳ���
//extern  int16s_t  NowSpeed_L_temp;
//extern  int16s_t  NowSpeed_R_temp;
extern  int16s_t  NowSpeed_L_history1;
extern  int16s_t  NowSpeed_R_history1;
extern  int16s_t g_nCarMtionPeriod;

extern  int16s_t  PI_Out;

/////////////////////////////////////////////////
extern  int16s_t g_nCarMtionCount;    //�ٶȿ���ʱ��Ƭ����

/////////////////////////////////////////////////
extern void Speed_PI(void);
extern void Speed_PI_OUT(void);

#endif /*PORT_H END */