
/************************************************************************************

* Com_def.h
* ����:����������������������

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.90 
* ����ʱ�䣺2013-05-25

*************************************************************************************/
#ifndef _Com_def_H           //if no define
#define _Com_def_H           //define  �����û�ж���Ļ������塣������(��ֹ����������ε��ô�ͷ�ļ�ʱ���ظ�����)

#include <hidef.h>            // common defines and macros 
#include <MC9S12XS128.h>      // derivative information 

/***************�������Ͷ���****************/
typedef  char           int8s_t;
typedef  int              int16s_t;
typedef  long           int32s_t;
typedef  unsigned char  int8u_t;
typedef  unsigned int     int16u_t;                        
typedef  unsigned long  int32u_t;

/*******************�궨��*******************/
///////////////////////////////
#define Filter_Method       0         // �˲���ʽѡ�� 0���������˲� �����������˲�

///////////////////////////////
#define CAR_PERIOD          5         // �жϷ���ʱ��Ƭ��ת����

/***********�����ֵ����************/
#define DC_Limit            500

/***********����ͨ����������**********/
#define CV_ACCE_Z			      3          //ADͨ�� - ���ٶȴ�����
#define CV_GYRO				      5          //ADͨ�� - ������
#define CV_ACCE_VAL         (AD_Value[CV_ACCE_Z])
#define CV_GYRO_VAL         (AD_Value[CV_GYRO])
                                                                                          
/***********�����������**********/
#define CV_ACCE_Z_ZERO  	  280      //���ٶȴ�������̬ƫ��ֵ                                                                          
#define CV_GYRO_ZERO        370        //�����Ǿ�̬ƫ��ֵ

/***********ֱ���ջ���������**********/
#if Filter_Method == 0                 //�������˲� 
  #define CAR_AA_P				 4.78    		              // (error) * P   4.78
  #define CAR_AA_D			     0.07                        // (GyroVal) * D 0.07
#else                                  //�����˲�
  #define CV_ACCE_RATIO      5.95      //���ٶȹ�һ��ϵ��
  #define CV_ACCE_RATIO_INT  (int32s_t)(CV_ACCE_RATIO*100)
  #define CAR_GYRO_RATIO     1.46      //��һ��ϵ����������  
  #define CAR_GYRO_RATIO_INT (int32s_t)(CAR_GYRO_RATIO*100)
  #define CAR_ACCE_RATIO     0.30      //�Ƕȷ���ϵ�� 0.45
  #define CAR_ACCE_RATIO_INT (int32s_t)(CAR_ACCE_RATIO*1000)                                 
  #define CAR_AA_P				  1.97			 // (error) * P     1.77
  #define CAR_AA_D			     1.56			 // (GyroVal ) * D  1.13         
#endif
    
#define CAR_AA_P_INT		    (int32s_t)(CAR_AA_P*100)
#define CAR_AA_D_INT		    (int32s_t)(CAR_AA_D*100)

#define MOTOR_SPEED_SET_MAX	 380      //�Ƕȿ����ٶ�����
#define MOTOR_SPEED_SET_MIN	-380      //�Ƕȿ����ٶ�����
                               
                                       
/***********�����������**********/
#define MOTOR_OUT_MAX			 (int16s_t)( 500)    //�Ƕ�+�ٶ��޷�
#define MOTOR_OUT_MIN			 (int16s_t)(-500)    //�Ƕ�+�ٶ��޷�
#define MOTOR_OUT_DEAD_VAL_L     (int16s_t)(  45)   //�˷������̬����  35
#define MOTOR_OUT_DEAD_VAL_R     (int16s_t)(  45)   //�˷������̬����  40
/***********�ٶȱջ���������**********/
#define CAR_MOTION_PERIOD		 20			 	// ���ٿ�������
#define MOTOR_SPEED_P	                0.07            //����   0.07
#define MOTOR_SPEED_P_INT		(int32s_t)(MOTOR_SPEED_P * 100)
#define MOTOR_SPEED_I		             0.19             //���� 0.19
#define MOTOR_SPEED_I_INT		(int32s_t)(MOTOR_SPEED_I * 100)

/***********����CCD��������**********/
/* TSL1401_CLK -- PORTT1 */
#define TSL1401_CLK_DDR     DDRT_DDRT1
#define TSL1401_CLK              PTT_PTT1

/* TSL1401_SI -- PORTT2 */
#define TSL1401_SI_DDR      DDRT_DDRT2
#define TSL1401_SI              PTT_PTT2


/***********������Ʋ�������**********/
#define CAR_DIRECTION_PERIOD  2    //�����������
#define  SetData    20                         //�ڰ׷�ֵ
#define  DirectionCenter  64               //��ʼ������λ��
#define  Direction_P         1.15                                    
#define  Direction_P_int    (int32s_t)(Direction_P*100)                //������Ʊ���  


//����

#define test_DDR    DDRT_DDRT7
#define test            PTT_PTT7

   

#endif //�������壬���#ifndefʹ��