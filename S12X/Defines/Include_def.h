
/************************************************************************************

* Include_def.h
* ����:�������ļ���ͷ�ļ������β��������徯��

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.10 
* ����ʱ�䣺2013-05-25

*************************************************************************************/
#ifndef Include_def_H        //if no define
#define Include_def_H        //define  �����û�ж���Ļ������塣������(��ֹ����������ε��ô�ͷ�ļ�ʱ���ظ�����)

/* ͷ�ļ����� */
#include <hidef.h>            /* common defines and macros */
#include <MC9S12XS128.h>      /* derivative information */

#include <math.h>

#include "Com_def.h"         //�����궨��
#include "System_Init.h"      //��ʼ��ģ�麯��          
#include "Delay.h"            //��ʱģ��
#include "Kalman_Filter.h"    //�������˲�����
#include "Speed_PID.h"        //�ٶ�PID�Ͳ���PID
#include "Sample_AD.h"        //AD���������ݴ�����
#include "Balance_Control.h"  //�ǶȽ��ٶȲ�������ƽ�����
#include "Speed_Control.h"    //�������
#include  "CCD.h"                   //����CCD�Զ��ع⼰ͼ��ɼ�
#include  "Direction_Control.h" //�������ߺ�����ȡ���������
#include  "SCI0.h"                    //����

/* ���α������Ĳ���warning */
#pragma MESSAGE DISABLE C5905   /* warning-���ݱ�1�� */
#pragma MESSAGE DISABLE C12056  /* warning-�������Ż� */

#endif //�������壬���#ifndefʹ��