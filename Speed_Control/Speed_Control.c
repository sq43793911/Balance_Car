/************************************************************************************

* Speed_Control.c
* 描述:速度给定，及电机输出

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V2.00 
* 更新时间：2013-05-25

*************************************************************************************/
                              

/*--------------- I N C L U D E S ------------------------------------*/

#include  "Include_def.h"

/*******************************速度变量***********************************/
///////////////////////////////////////////////////////
int8s_t  direction_R=1;        //电机正转为1，反转为-1
int8s_t  direction_L=1;
int16s_t DCDuty_L=0;           //控制电机
int16s_t DCDuty_R=0;           //控制电机

///////////////////////////////////////////////////////
int16s_t ObjectSpeed=0;	       //目标速度
int16s_t NowSpeed_L_temp=0;
int16s_t NowSpeed_R_temp=0;
int16u_t ms_1000=0;
int16u_t second=0; 

 float  start=0; 
///////////////////////////////////////////////////////
//==========================================
//函数名Motor_Decision
//作用：速度决策
//==========================================
void Spd_Decision(void)
{      
   
    
    //start++;
    
   // if(start ==1)
    // {
    
        ObjectSpeed =0;
        
    //}
    // if(start>520)
    //  {
      
       //ObjectSpeed =220;
      // start = 521;
      
    // }
   
}    
 
//==========================================
//函数名Motor_Control
//作用：赋给电机经过PID运算的速度值
//========================================== 
void Motor_Control_R(void)
 {
    //test = 1 ;
     
    if(DCDuty_R>=0) 
    {
      if(direction_R==1)
      {       
        PWMDTY67= 0;       //正转
        PWMDTY45 =(DCDuty_R/2);
        direction_R=1;
      }
      if(direction_R==-1)
      {
        PWMDTY67  = 0;	
        PWMDTY45   = 0; 
        
        Delay_us(80); 
        
        PWMDTY67 = 0;	 // 反转
        PWMDTY45  = (DCDuty_R/2);
        direction_R=1;
      } 
    }
    if(DCDuty_R<0)
    {
      if(direction_R==1)
      {
        PWMDTY67 = 0;	
        PWMDTY45 = 0; 
        
        Delay_us(80); 
        
        PWMDTY67  = -(DCDuty_R);	       //正转
        PWMDTY45   = 0;
        direction_R=-1;  
      }
      if(direction_R==-1)
      {
        PWMDTY67  = -(DCDuty_R);	       //正转
        PWMDTY45  = 0;
        direction_R=-1;
      }
    }
   // test = 0;
 }
 ////////////////////////////////////////////////////
 void Motor_Control_L(void)
 {
    //test = 1; 
    if(DCDuty_L>=0) 
    {
      if(direction_L==1)
      {
        PWMDTY23 =  0;
        PWMDTY01  = (DCDuty_L/2);
        direction_L=1;
      }
      if(direction_L==-1)
      {
        PWMDTY23  = 0;	
        PWMDTY01  = 0; 
        
        Delay_us(80);
        
        PWMDTY23 = 0;	 // 反转
        PWMDTY01  =(DCDuty_L/2);
        direction_L=1;
      } 
    }
    if(DCDuty_L<0)
    {
      if(direction_L==1)
      {
        PWMDTY23 = 0;	
        PWMDTY01  = 0;
        
        Delay_us(80);
        
        PWMDTY23 = -(DCDuty_L);	         //反转
        PWMDTY01  = 0;
        direction_L=-1;  
      }
      if(direction_L==-1)
      {
        PWMDTY23 =-(DCDuty_L);	         //反转
        PWMDTY01  = 0;
        direction_L=-1;
      }
    }
   // test = 0;
 }
//////////////////////////////////////////////////////
void Motor_Control(void) 
{ 
 
      
      
	  int16s_t nLeftVal, nRightVal;
	  
	  //test = 1;
	  
 	  nLeftVal = g_nLeftMotorOut;
	  nRightVal = g_nRightMotorOut;
	
	  if(nLeftVal > 0) 		
	     nLeftVal += MOTOR_OUT_DEAD_VAL_L;
   	else if(nLeftVal < 0) 
 	     nLeftVal -= MOTOR_OUT_DEAD_VAL_L;
 	
   	if(nRightVal > 0) 		
 	     nRightVal += MOTOR_OUT_DEAD_VAL_R;
 	  else if(nRightVal < 0) 
 	     nRightVal -= MOTOR_OUT_DEAD_VAL_R;

    DCDuty_L = nLeftVal;
    DCDuty_R = nRightVal;
     
    if(Angle>20 || Angle<-20) 
    {
      
    DCDuty_R = 0;                    //电机直接赋值
    DCDuty_L = 0;                    //电机直接赋值 
    }
    
   /* if (stopValue > 1)            //起跑线停止
    {
    DCDuty_R = 0;                    //电机直接赋值
    DCDuty_L = 0;                    //电机直接赋值  
    
    stopValue = 0;
    }  */
    DCDuty_R = 0;                    //电机直接赋值
    DCDuty_L = 0;                    //电机直接赋值  
    
    if( DCDuty_R> DC_Limit)  DCDuty_R= DC_Limit; 
    if( DCDuty_L> DC_Limit)  DCDuty_L= DC_Limit;
    if( DCDuty_R<-DC_Limit)  DCDuty_R=-DC_Limit; 
    if( DCDuty_L<-DC_Limit)  DCDuty_L=-DC_Limit;
    
    //test = 0;
     
    Motor_Control_R();
    Motor_Control_L();
    
    
 }
 /***************************/
 /*       速度采集   5ms一次*/
 ////////////////////////////
 void Speed_Collect(void) 
 {
      
       int8u_t  spd_temp1,spd_temp2;
       int8u_t  time_out;                          //计数器清零等待超时
        //test = 1;
       spd_temp1 =PORTA;                           //左边计数
       spd_temp2 =PORTB;                           //右边计数
                               
       PTT_PTT4=1; 
       PTT_PTT6=1;                                //将 PTT_PTT6,7 置 1，给计数器清零
    
       if(direction_L==1)                             
       {
           NowSpeed_L_temp += spd_temp1;
       } 
       else                                         //左侧轮反转
       {
           NowSpeed_L_temp -= spd_temp1;
       }
       if(direction_R==1)                              
       {
           NowSpeed_R_temp += spd_temp2;
       } 
       else                                         //右侧轮反转
       {
           NowSpeed_R_temp -= spd_temp2;
       } 
       
       ////////////////////////////////
       /////////////////////////////////////////////////////
       //定时时间服务
          ms_1000++;
           if(ms_1000>=200)   //定时1s
           {
               ms_1000=0;
              
               second++;
               if(second==9000)
               {
                  second=0; 
               }            
           }    
       /////////////////////////////////////////////////////
       ///////////////////////////////
       
       spd_temp1 =PORTA;                            //再次读取PA、PB口，确保已经被清零
       spd_temp2 =PORTB; 
       while(spd_temp1 && spd_temp2 && time_out<200)             //确保清零
       {
            spd_temp1 = PORTA;
            spd_temp2 = PORTB;
            time_out++;
       }         
       time_out=0;   
       
       PTT_PTT4=0;
       PTT_PTT6=0;                                  //将 PTT_PTT6,7 清 0, 开始计数      
       ////////////////////////////////////////////////////
       //test =0;
 }
