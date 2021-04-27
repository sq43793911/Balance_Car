/************************************************************************************

* Kalman_Filter.c
* 描述:卡尔曼滤波器

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    匿名
* 注释：    孙谦       (第七届电磁)


* 程序版本：V1.50 
* 更新时间：2013-05-25

*************************************************************************************/

/*--------------- I N C L U D E S ------------------------------------*/

#include  "Include_def.h"


/*********Kalman滤波，8MHz的处理时间约1.8ms***********/

////////////////////////////////////////////
float Angle, Angle_dot; 		//外部需要引用的变量
////////////////////////////////////////////
float Q_angle=0.001, Q_gyro=0.003, R_angle=0.67, dt=0.005;   	//dt的取值为kalman滤波器采样时间;
//float Q_angle=0.01, Q_gyro=0.03, R_angle=0.01, dt=0.010;   	//Q_angle=0.001, Q_gyro=0.003, R_angle=0.67, dt=0.005;dt的取值为kalman滤波器采样时间;		
float P[2][2] =
            {
					{ 1, 0 },
					{ 0, 1 }
			   };
	
char  C_0 = 1;
float E;  
float q_bias;
float Angle_err;
float PCt_0, PCt_1;
float K_0, K_1;
float t_0, t_1;
float Pdot[4] ={0,0,0,0};

//-------------------------------------------------------

void Kalman_Filter(float angle_m,float gyro_m)			//gyro_m:gyro_measure
{
	Angle+=(gyro_m-q_bias) * dt;    //先验估计
	
	Pdot[0]=Q_angle - P[0][1] - P[1][0];// Pk-' 先验估计误差协方差的微分
	Pdot[1]=- P[1][1];
	Pdot[2]=- P[1][1];
	Pdot[3]=Q_gyro;
	
	P[0][0] += Pdot[0] * dt;        // Pk- 先验估计误差协方差微分的积分 = 先验估计误差协方差
	P[0][1] += Pdot[1] * dt;
	P[1][0] += Pdot[2] * dt;
	P[1][1] += Pdot[3] * dt;
		
	Angle_err = angle_m - Angle;    //zk-先验估计
		
	PCt_0 = C_0 * P[0][0];
	PCt_1 = C_0 * P[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;                //Kk
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * P[0][1];

	P[0][0] -= K_0 * t_0;           //后验估计误差协方差
	P[0][1] -= K_0 * t_1;
	P[1][0] -= K_1 * t_0;
	P[1][1] -= K_1 * t_1;
		
	Angle	+= K_0 * Angle_err;       //后验估计	
	q_bias+= K_1 * Angle_err;       //后验估计
	Angle_dot = gyro_m-q_bias;      //输出值（后验估计）的微分 = 角速度
}
