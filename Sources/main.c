/************************************************************************************

* main.c
* 描述:主函数尚为空，可以插入调试程序，中断服务程序负责整个检测与控制

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.50 
* 更新时间：2013-05-25

*************************************************************************************/

/************************定义头文件以调用其他函数**************************/

#include  "Include_def.h"


/**************实时时钟中断***********************/

int16u_t ms_2500=0;

///////////////////////////////////////////////////
int16u_t g_nCarCount=0;                  //中断时间片计数
int16s_t g_nCarMtionCount=0;             //速度控制时间片计数、
int16s_t g_nCarDirCount=0;             //速度控制时间片计数

int16s_t g_nCarMtionPeriod =0;
int16s_t g_nCarDirPeriod = 0;


////////////////////////////////////////////////////
/*************************************主函数************************************/
void main(void) 
{
  
   // int16u_t i;
    //int16u_t dealy1=0,delay2=0;
        
    DisableInterrupts;                     //程序一开始需要关闭所有中断，防止单片机初始化过程中被某个中断打断
    
    /*for(dealy1=0;dealy1<=20000;dealy1++)
    {
        for(delay2=0;delay2<60;delay2++);
    }                       
             */
    System_Init();                         //调用系统初始化函数
     
    /*
    for(i=0;i<1000;i++) 
    {
         AD_Collect();                      //顺序不能颠倒
         AD_Enable();                       //顺序不能颠倒      
    }     */
    
    EnableInterrupts;                      //允许中断
       
    for(;;) 
    {         
                  
    }   
}

/*******************************************中断函数*************************************************/
/*==============================RTI中断(定时1ms，可用于测速和定时)===============================*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt 7 RTI_int()
{ 
    
   //Speed_PI_OUT();                   //PWM输出控制，周期5ms
   // DirectionControlOutput();
 
   CRGFLG_RTIF=1;                              //Clear Flag   
   g_nCarCount++;
   
    //g_nCarMtionPeriod++;
    //Speed_PI_OUT(); 
    
    //g_nCarDirPeriod ++;
    //DirectionControlOutput();
   
   ////////////////////////////////////////////////////
   //时间片轮转
   if(g_nCarCount>=CAR_PERIOD)          //第0个1ms
   {
       g_nCarCount=0;
       test = 1;
       ////////////////////////////////////////////////
       
       //test = 1;
       AD_Enable();                     //AD使能
       
       //test =0;
       ////////////////////////////////////////////////////
       //速度采样
        
       Speed_Collect();
       //test = 1;
       /////////////////////////////////////////////////////
       
       
       CCDTotalControl();             //CCD图像采集 20ms一次
       test = 0;     
   }
   else if(g_nCarCount==1)              //第1个1ms
   {
       ////////////////////////////////////////////////
       test =1 ;
        AD_Collect();                   //AD数据采集
       ////////////////////////////////////////////////   
       //test = 0   ;
        CarVoltageGet();                //AD数值转换及卡尔曼滤波
       ////////////////////////////////////////////////
       //test = 1  ;
         CCDTotalControl();             //CCD图像采集 20ms一次
         test = 0;
   }
   else if(g_nCarCount==2)              //第2个1ms
   {
       test = 1 ;
        CarAngleControl(); 
        //////////////////////////////////////////////////////
        //test = 1;
        CCDTotalControl();             //CCD图像采集 20ms一次
        
        test = 0;
   }
   else if(g_nCarCount==3)              //第3个1ms
   {
        test = 1;
        g_nCarMtionCount++;
        if(g_nCarMtionCount>=CAR_MOTION_PERIOD) 
        {
            g_nCarMtionCount = 0;
            g_nCarMtionPeriod =0;
           ////////////////////////////////////////////////
            NowSpeed_L = NowSpeed_L_temp;
            NowSpeed_R = NowSpeed_R_temp;
            NowSpeed_L_temp = 0;
            NowSpeed_R_temp = 0;
             
            NowSpeed_L_history1 = NowSpeed_L ;
            NowSpeed_R_history1 = NowSpeed_R ;       
           //////////////////////////////////////////////// 
           
           //test =0 ;
           Speed_PI();                     //速度PI控制，周期100ms
           
        }
        //test = 1 ;                                
        Speed_PI_OUT();                   //PWM输出控制，周期5ms
       ////////////////////////////////////////////////////////////////////
       //test = 0 ;
        CCDTotalControl();             //CCD图像采集 20ms一次
        test = 0;
   }
   else if(g_nCarCount==4)                 //第4个1ms
   {
   
       test = 1 ;
       g_nCarDirCount++;
       Spd_Decision(); 
       ///////////////////////////////////////
       
       //test = 0 ;
       CCDTotalControl();             //CCD1ms曝光和图像采集
      if(g_nCarDirCount >= CAR_DIRECTION_PERIOD ) 
       {
          //test =1 ;
          DirectionControl();           //方向控制
          g_nCarDirCount = 0;
          g_nCarDirPeriod = 0;
          //test =0 ;
       } 
       
       //test = 1;
       DirectionControlOutput();  
       
       test = 0;  
   }
   /////////////////////////////////////////////////////
      

}

#pragma CODE_SEG DEFAULT

