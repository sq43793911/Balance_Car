/************************************************************************************

* Speed_PID.c
* 描述:速度PI控制，及速度分级输出

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.40 
* 更新时间：2013-05-25

*************************************************************************************/

#include  "Include_def.h"

/*****************----PID函数-----******************/

/********测 速*********/
int16s_t NowSpeed_L;
int16s_t NowSpeed_R;
int16s_t NowSpeed_L_history1=0;
int16s_t NowSpeed_R_history1=0;

/*****速度位置式PI*****/
int16s_t PI_SpeedNew;
int16s_t PI_SpeedOld;
int32s_t PI_SpeedKeep;

int32s_t PI_SpeedErr;

int16s_t PI_Out;
int16s_t PI_Out_history1;

//====================================
//函数名Speed_PI
//作用：速度位置式PI控制，100ms调用一次
//====================================   
void Speed_PI(void) 
{
   
    
	int32s_t  nP, nI;
	int32s_t  nSpeed;
	int32s_t  nValue1, nValue2;
	//test = 1;
	nSpeed = (NowSpeed_R + NowSpeed_L) / 2;
	
	PI_SpeedErr = ObjectSpeed - nSpeed;
	nValue1 = ObjectSpeed - nSpeed;
	nValue2 = ObjectSpeed - nSpeed;
		
    //if(nValue1 > 2000)  nValue1 = 2000;
    //if(nValue1 < -2000) nValue1  = -2000;
    //if(nValue2 > 1600) nValue2 =1600;
    //if(nValue2 < -1600) nValue2  = -1600;
  
  //if(nValue1 > 160)  nValue1 = 160;
  //if(nValue1 < -160) nValue1  = -160;
  //if(nValue2 > 135)  nValue2 = 135;
 //if(nValue2 < -135) nValue2  = -135;
	
	nP = nValue1 * MOTOR_SPEED_P_INT;
	nI =  nValue2 * MOTOR_SPEED_I_INT; 

		
   PI_SpeedKeep += nI;
	PI_SpeedOld = PI_SpeedNew;
	
   PI_SpeedNew = (int16s_t)((nP + (PI_SpeedKeep/5)) / 100L);

  //if(PI_SpeedKeep > 200000)   PI_SpeedKeep = 200000;
  //if(PI_SpeedKeep < -200000)  PI_SpeedKeep = -200000;
  //if(PI_SpeedKeep > 26000)   PI_SpeedKeep = 26000;
  //if(PI_SpeedKeep < -26000)  PI_SpeedKeep = -26000;

   //test = 0;
}

//====================================
//函数名Speed_PI_OUT
//作用：计算速度PI控制的输出，5ms调用一次
//====================================  
void Speed_PI_OUT(void) 
{
    
    
  int32s_t  nValue;
   //test = 1;
   nValue = PI_SpeedNew - PI_SpeedOld;
	nValue = nValue * (g_nCarMtionCount + 1) / (CAR_MOTION_PERIOD-1) + PI_SpeedOld;
	PI_Out = (int16s_t)nValue; 
	
//	test = 0; 
}
