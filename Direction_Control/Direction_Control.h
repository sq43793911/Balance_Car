/************************************************************************************

* Direction_Control.h
* ����:�������ߺ�����ȡ���������

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.00 
* ����ʱ�䣺2013-06-29

*************************************************************************************/

#ifndef Direction_Control_H        //if no define
#define Direction_Control_H        //define  �����û�ж���Ļ������塣������(��ֹ����������ε��ô�ͷ�ļ�ʱ���ظ�����)

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