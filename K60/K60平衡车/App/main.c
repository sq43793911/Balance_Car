/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,野火科技
 *     All rights reserved.
 *     技术讨论：野火初学论坛 http://www.chuxue123.com
 *
 *     除注明出处外，以下所有内容版权均属野火科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留野火科技的版权声明。
 *
 * @file       main.c
 * @brief      野火K60 平台主程序
 * @author     野火科技
 * @version    v5.0
 * @date       2013-12-19
 */

#include "common.h"
#include "include.h"

extern uint16 g_nCarCount=0;                  //中断时间片计数
extern int16 g_nCarMtionCount=0;             //速度控制时间片计数、
extern int16 g_nCarDirCount=0;             //方向控制时间片计数

extern int16 g_nCarMtionPeriod =0;
extern int16 g_nCarDirPeriod = 0;


extern float Gyro_Now,g_fCarAngle;

extern float OutData[4];                              //SCI示波器参数
extern float Gyro_Now,angle_offset_vertical;          //陀螺仪转化后的角速度，转化后的加速度角度
extern float g_fCarAngle,g_fGyroscopeAngleIntegral;   //融合后的角度
extern volatile int     MMA7361 ,ENC03,real_angle;    //加速度计AD ,陀螺仪AD，模块输出的角度


extern void PIT0_IRQHandler(void);
extern   void OutPut_Data(void);                              //SCI采参数

void main()
{
    DisableInterrupts;//禁止总中断

    // 在control.h定义了相关宏
    adc_init (ZOUT);          //MMA7361 Z轴
    adc_init (Gyro1);        // ENC03角速度
    adc_init (Ang);          //角度

    uart_init (UART4, 9600);
    //初始化 PWM 输出
    //FTM 的管脚 可在  fire_port_cfg.h
    //宏定义FTM0_PRECISON   改为  1000u
    //PWM数值反转。
    FTM_PWM_init(FTM0, FTM_CH3,10000,1000);
    FTM_PWM_init(FTM0, FTM_CH4,10000,1000);
    FTM_PWM_init(FTM0, FTM_CH5,10000,1000);
    FTM_PWM_init(FTM0, FTM_CH6,10000,1000);


    //开启使能端
    gpio_init(PTD15,GPO,0);
    gpio_init(PTA19,GPO,0);
    gpio_init(PTA5 ,GPO,0);
    gpio_init(PTA24,GPO,0);

    /*
    //3 左 反转
    //5 左 正转
    //4 右 正转
    //6 右 反转
     */
    led_init(LED0);                                         //初始化LED0，PIT0中断用到LED0

    pit_init_ms(PIT0, 1);                                //初始化PIT0，定时时间为： 5ms
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //设置PIT0的中断复位函数为 PIT0_IRQHandler
    enable_irq (PIT0_IRQn);                                 //使能PIT0中断
    EnableInterrupts;//中断允许
    //DELAY_MS(3000);
    while(1)
   {
        #if 1
        OutData[0] = ENC03;
        OutData[1] = MMA7361;//Gyro_Now;//
        OutData[2] = angle_offset_vertical ;
        OutData[3] = g_fCarAngle;
        OutPut_Data();
        #endif
        //FTM_PWM_Duty(FTM0,FTM_CH3,900);
   }
}


/**********************中断服务程序*******************/
void PIT0_IRQHandler(void)
{
    led_turn(LED0);                             //闪烁 LED0
    g_nCarCount++;
      
     ////////////////////////////////////////////////////
   //时间片轮转
   if(g_nCarCount>=CAR_PERIOD)          //第0个1ms
   {
       g_nCarCount=0;
  
       ////////////////////////////////////////////////////
       //速度采样
        
       
       /////////////////////////////////////////////////////
       
    
   }
   else if(g_nCarCount==1)              //第1个1ms
   {
       ////////////////////////////////////////////////
       #if Angle_Calculate_Select_Soft  
     
           AD_Calculate_Soft();                   //AD数据采集,软件计算
       
       #elif Angle_Calculate_Select_Hard
         
           AD_Calculate_Hard();                 //硬件计算
           
       #endif
       ////////////////////////////////////////////////   

   }
   else if(g_nCarCount==2)              //第2个1ms
   {
      #if Angle_Calculate_Select_Soft   
      if (g_fCarAngle <= -80 || g_fCarAngle >= -50)
      {
        FTM_PWM_Duty(FTM0,FTM_CH3,1000);
        FTM_PWM_Duty(FTM0,FTM_CH4,1000);
        FTM_PWM_Duty(FTM0,FTM_CH5,1000);
        FTM_PWM_Duty(FTM0,FTM_CH6,1000);
      }
      else 
      {
        Speed_Calculate(g_fCarAngle,Gyro_Now);      //速度计算
      }
      
      #elif Angle_Calculate_Select_Hard
      #endif
   }
   else if(g_nCarCount==3)              //第3个1ms
   {
        
        g_nCarMtionCount++;
        if(g_nCarMtionCount >= CAR_MOTION_PERIOD) 
        {
            g_nCarMtionCount = 0;
            g_nCarMtionPeriod =0;
           ////////////////////////////////////////////////
            //NowSpeed_L = NowSpeed_L_temp;
            //NowSpeed_R = NowSpeed_R_temp;
            //NowSpeed_L_temp = 0;
            //NowSpeed_R_temp = 0;
             
            //NowSpeed_L_history1 = NowSpeed_L ;
            //NowSpeed_R_history1 = NowSpeed_R ;       
           //////////////////////////////////////////////// 
           
           
           //Speed_PI();                     //速度PI控制，周期100ms
           
        }
                                      
        //Speed_PI_OUT();                   //PWM输出控制，周期5ms
       ////////////////////////////////////////////////////////////////////
     

   }
   else if(g_nCarCount==4)                 //第4个1ms
   {
   

       g_nCarDirCount++;
       //Spd_Decision();     //速度决策
       ///////////////////////////////////////
       
      if(g_nCarDirCount >= CAR_DIRECTION_PERIOD ) 
       {
          
          //DirectionControl();           //方向控制
          g_nCarDirCount = 0;
          g_nCarDirPeriod = 0;
        
       } 
       
       //DirectionControlOutput();  
       
   
   }
   /////////////////////////////////////////////////////

    PIT_Flag_Clear(PIT0);                       //清中断标志位
}

