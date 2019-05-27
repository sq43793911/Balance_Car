
/************************************************************************************

* Com_def.h
* 描述:数据类型声明，参数配置

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.90 
* 更新时间：2013-05-25

*************************************************************************************/
#ifndef _Com_def_H           //if no define
#define _Com_def_H           //define  即如果没有定义的话，则定义。。。。(防止其他函数多次调用此头文件时而重复定义)

#include <hidef.h>            // common defines and macros 
#include <MC9S12XS128.h>      // derivative information 

/***************数据类型定义****************/
typedef  char           int8s_t;
typedef  int              int16s_t;
typedef  long           int32s_t;
typedef  unsigned char  int8u_t;
typedef  unsigned int     int16u_t;                        
typedef  unsigned long  int32u_t;

/*******************宏定义*******************/
///////////////////////////////
#define Filter_Method       0         // 滤波方式选择， 0：卡尔曼滤波 其他：互补滤波

///////////////////////////////
#define CAR_PERIOD          5         // 中断服务时间片轮转周期

/***********电机赋值限速************/
#define DC_Limit            500

/***********采样通道参数配置**********/
#define CV_ACCE_Z			      3          //AD通道 - 加速度传感器
#define CV_GYRO				      5          //AD通道 - 陀螺仪
#define CV_ACCE_VAL         (AD_Value[CV_ACCE_Z])
#define CV_GYRO_VAL         (AD_Value[CV_GYRO])
                                                                                          
/***********车体参数配置**********/
#define CV_ACCE_Z_ZERO  	  280      //加速度传感器静态偏置值                                                                          
#define CV_GYRO_ZERO        370        //陀螺仪静态偏置值

/***********直立闭环参数配置**********/
#if Filter_Method == 0                 //卡尔曼滤波 
  #define CAR_AA_P				 4.78    		              // (error) * P   4.78
  #define CAR_AA_D			     0.07                        // (GyroVal) * D 0.07
#else                                  //互补滤波
  #define CV_ACCE_RATIO      5.95      //加速度归一化系数
  #define CV_ACCE_RATIO_INT  (int32s_t)(CV_ACCE_RATIO*100)
  #define CAR_GYRO_RATIO     1.46      //归一化系数，试验获得  
  #define CAR_GYRO_RATIO_INT (int32s_t)(CAR_GYRO_RATIO*100)
  #define CAR_ACCE_RATIO     0.30      //角度反馈系数 0.45
  #define CAR_ACCE_RATIO_INT (int32s_t)(CAR_ACCE_RATIO*1000)                                 
  #define CAR_AA_P				  1.97			 // (error) * P     1.77
  #define CAR_AA_D			     1.56			 // (GyroVal ) * D  1.13         
#endif
    
#define CAR_AA_P_INT		    (int32s_t)(CAR_AA_P*100)
#define CAR_AA_D_INT		    (int32s_t)(CAR_AA_D*100)

#define MOTOR_SPEED_SET_MAX	 380      //角度控制速度限速
#define MOTOR_SPEED_SET_MIN	-380      //角度控制速度限速
                               
                                       
/***********电机参数配置**********/
#define MOTOR_OUT_MAX			 (int16s_t)( 500)    //角度+速度限幅
#define MOTOR_OUT_MIN			 (int16s_t)(-500)    //角度+速度限幅
#define MOTOR_OUT_DEAD_VAL_L     (int16s_t)(  45)   //克服电机静态死区  35
#define MOTOR_OUT_DEAD_VAL_R     (int16s_t)(  45)   //克服电机静态死区  40
/***********速度闭环参数配置**********/
#define CAR_MOTION_PERIOD		 20			 	// 车速控制周期
#define MOTOR_SPEED_P	                0.07            //比例   0.07
#define MOTOR_SPEED_P_INT		(int32s_t)(MOTOR_SPEED_P * 100)
#define MOTOR_SPEED_I		             0.19             //积分 0.19
#define MOTOR_SPEED_I_INT		(int32s_t)(MOTOR_SPEED_I * 100)

/***********线性CCD参数配置**********/
/* TSL1401_CLK -- PORTT1 */
#define TSL1401_CLK_DDR     DDRT_DDRT1
#define TSL1401_CLK              PTT_PTT1

/* TSL1401_SI -- PORTT2 */
#define TSL1401_SI_DDR      DDRT_DDRT2
#define TSL1401_SI              PTT_PTT2


/***********方向控制参数配置**********/
#define CAR_DIRECTION_PERIOD  2    //方向控制周期
#define  SetData    20                         //黑白阀值
#define  DirectionCenter  64               //初始中心线位置
#define  Direction_P         1.15                                    
#define  Direction_P_int    (int32s_t)(Direction_P*100)                //方向控制比例  


//测试

#define test_DDR    DDRT_DDRT7
#define test            PTT_PTT7

   

#endif //结束定义，配合#ifndef使用