/************************************************************************************

* main.c
* ����:��������Ϊ�գ����Բ�����Գ����жϷ��������������������

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.50 
* ����ʱ�䣺2013-05-25

*************************************************************************************/

/************************����ͷ�ļ��Ե�����������**************************/

#include  "Include_def.h"


/**************ʵʱʱ���ж�***********************/

int16u_t ms_2500=0;

///////////////////////////////////////////////////
int16u_t g_nCarCount=0;                  //�ж�ʱ��Ƭ����
int16s_t g_nCarMtionCount=0;             //�ٶȿ���ʱ��Ƭ������
int16s_t g_nCarDirCount=0;             //�ٶȿ���ʱ��Ƭ����

int16s_t g_nCarMtionPeriod =0;
int16s_t g_nCarDirPeriod = 0;


////////////////////////////////////////////////////
/*************************************������************************************/
void main(void) 
{
  
   // int16u_t i;
    //int16u_t dealy1=0,delay2=0;
        
    DisableInterrupts;                     //����һ��ʼ��Ҫ�ر������жϣ���ֹ��Ƭ����ʼ�������б�ĳ���жϴ��
    
    /*for(dealy1=0;dealy1<=20000;dealy1++)
    {
        for(delay2=0;delay2<60;delay2++);
    }                       
             */
    System_Init();                         //����ϵͳ��ʼ������
     
    /*
    for(i=0;i<1000;i++) 
    {
         AD_Collect();                      //˳���ܵߵ�
         AD_Enable();                       //˳���ܵߵ�      
    }     */
    
    EnableInterrupts;                      //�����ж�
       
    for(;;) 
    {         
                  
    }   
}

/*******************************************�жϺ���*************************************************/
/*==============================RTI�ж�(��ʱ1ms�������ڲ��ٺͶ�ʱ)===============================*/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt 7 RTI_int()
{ 
    
   //Speed_PI_OUT();                   //PWM������ƣ�����5ms
   // DirectionControlOutput();
 
   CRGFLG_RTIF=1;                              //Clear Flag   
   g_nCarCount++;
   
    //g_nCarMtionPeriod++;
    //Speed_PI_OUT(); 
    
    //g_nCarDirPeriod ++;
    //DirectionControlOutput();
   
   ////////////////////////////////////////////////////
   //ʱ��Ƭ��ת
   if(g_nCarCount>=CAR_PERIOD)          //��0��1ms
   {
       g_nCarCount=0;
       test = 1;
       ////////////////////////////////////////////////
       
       //test = 1;
       AD_Enable();                     //ADʹ��
       
       //test =0;
       ////////////////////////////////////////////////////
       //�ٶȲ���
        
       Speed_Collect();
       //test = 1;
       /////////////////////////////////////////////////////
       
       
       CCDTotalControl();             //CCDͼ��ɼ� 20msһ��
       test = 0;     
   }
   else if(g_nCarCount==1)              //��1��1ms
   {
       ////////////////////////////////////////////////
       test =1 ;
        AD_Collect();                   //AD���ݲɼ�
       ////////////////////////////////////////////////   
       //test = 0   ;
        CarVoltageGet();                //AD��ֵת�����������˲�
       ////////////////////////////////////////////////
       //test = 1  ;
         CCDTotalControl();             //CCDͼ��ɼ� 20msһ��
         test = 0;
   }
   else if(g_nCarCount==2)              //��2��1ms
   {
       test = 1 ;
        CarAngleControl(); 
        //////////////////////////////////////////////////////
        //test = 1;
        CCDTotalControl();             //CCDͼ��ɼ� 20msһ��
        
        test = 0;
   }
   else if(g_nCarCount==3)              //��3��1ms
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
           Speed_PI();                     //�ٶ�PI���ƣ�����100ms
           
        }
        //test = 1 ;                                
        Speed_PI_OUT();                   //PWM������ƣ�����5ms
       ////////////////////////////////////////////////////////////////////
       //test = 0 ;
        CCDTotalControl();             //CCDͼ��ɼ� 20msһ��
        test = 0;
   }
   else if(g_nCarCount==4)                 //��4��1ms
   {
   
       test = 1 ;
       g_nCarDirCount++;
       Spd_Decision(); 
       ///////////////////////////////////////
       
       //test = 0 ;
       CCDTotalControl();             //CCD1ms�ع��ͼ��ɼ�
      if(g_nCarDirCount >= CAR_DIRECTION_PERIOD ) 
       {
          //test =1 ;
          DirectionControl();           //�������
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

