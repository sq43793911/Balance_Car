/************************************************************************************

* System_Init.h
* ����:�Ĵ������ã��������໷��I/O��PWMģ�顢ʵʱʱ�ӡ�AD

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.10 
* ����ʱ�䣺2013-05-25

*************************************************************************************/

#ifndef System_Init_H        //if no define
#define System_Init_H        //define  �����û�ж���Ļ������塣������(��ֹ����������ε��ô�ͷ�ļ�ʱ���ظ�����)

//#include  "Include_def.h"
/*--------------- I N C L U D E S ------------------------------------*/   
extern void FBE_Init(void);                        //��ʼ������ʱ�� 
extern void SCI0_Init(void);   
extern void PORT_Init(void);                       //��ʼ����ͨI/O�˿ڣ���紫�����������
extern void CCD_IO_Init(void);                   //��ʼ��CCDʱ�ӿ���
extern void Init_Pixel_Array(void) ;             //��ʼ������ֵ
//extern void Servo_Init(void);                      //��ʼ��PWM01�����ƶ��
extern void Forward_Init(void);                    //��ʼ��PWM1,3��PWM5,7�����Ƶ��
extern void ATD_Init(void);                        //��ʼ��ADģ��    
extern void RTI_Init(void);                        //��ʼ��RTI��ʱ�жϣ���ʱ1ms    
//extern void TIM_Init(void);                        //��ʼ��TIM���벶׽������������                     
extern void System_Init(void);

///////////////////////////////////////////////




#endif //�������壬���#ifndefʹ��