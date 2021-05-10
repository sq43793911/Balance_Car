#ifndef _BALANCE_CONTROL_H_
#define _BALANCE_CONTROL_H_

#define XOUT    ADC1_DM0
#define YOUT    ADC0_SE16
#define ZOUT    ADC0_SE17

#define Gyro1   ADC1_SE16
#define Gyro2   ADC1_DP0
#define Ang     ADC0_SE18

/***********************直立控制参数********************/
#define MMA7361_vertical             1850    // 1860// 1760  //1850// 2600
#define GYRO_VAL                     1360   //陀螺仪中值        //加大向后，减少向前
#define Gyro_ratio                   0.28    //0.8
#define GRAVITY_ADJUST_TIME_CONSTANT 2
#define DT                           0.005
#define MMA7361_ratio                0.12//1150    
#define P_ANGLE             2
#define D_ANGLE             0.05
#define Balance_Point       -65

 //反复调整以上5个参数，以及机械结构
 
#define MOTOR_DEAD_VAL_L  20    //  死区电压
#define MOTOR_DEAD_VAL_R  20





/***********************函数声明********************/
 extern   void Rd_Ad_Value(void);                              //AD采集
 extern   void AD_Calculate_Soft(void);                              //AD采集和计算
 extern   void AD_Calculate_Hard(void);
 extern   void Speed_Calculate(float angle,float angle_dot);   //速度计算
 static   unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT);
 extern   void OutPut_Data(void);                              //SCI采参数

#endif