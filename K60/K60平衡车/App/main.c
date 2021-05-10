/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,Ұ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�Ұ���ѧ��̳ http://www.chuxue123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����Ұ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��Ұ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      Ұ��K60 ƽ̨������
 * @author     Ұ��Ƽ�
 * @version    v5.0
 * @date       2013-12-19
 */

#include "common.h"
#include "include.h"

extern uint16 g_nCarCount=0;                  //�ж�ʱ��Ƭ����
extern int16 g_nCarMtionCount=0;             //�ٶȿ���ʱ��Ƭ������
extern int16 g_nCarDirCount=0;             //�������ʱ��Ƭ����

extern int16 g_nCarMtionPeriod =0;
extern int16 g_nCarDirPeriod = 0;


extern float Gyro_Now,g_fCarAngle;

extern float OutData[4];                              //SCIʾ��������
extern float Gyro_Now,angle_offset_vertical;          //������ת����Ľ��ٶȣ�ת����ļ��ٶȽǶ�
extern float g_fCarAngle,g_fGyroscopeAngleIntegral;   //�ںϺ�ĽǶ�
extern volatile int     MMA7361 ,ENC03,real_angle;    //���ٶȼ�AD ,������AD��ģ������ĽǶ�


extern void PIT0_IRQHandler(void);
extern   void OutPut_Data(void);                              //SCI�ɲ���

void main()
{
    DisableInterrupts;//��ֹ���ж�

    // ��control.h��������غ�
    adc_init (ZOUT);          //MMA7361 Z��
    adc_init (Gyro1);        // ENC03���ٶ�
    adc_init (Ang);          //�Ƕ�

    uart_init (UART4, 9600);
    //��ʼ�� PWM ���
    //FTM �Ĺܽ� ����  fire_port_cfg.h
    //�궨��FTM0_PRECISON   ��Ϊ  1000u
    //PWM��ֵ��ת��
    FTM_PWM_init(FTM0, FTM_CH3,10000,1000);
    FTM_PWM_init(FTM0, FTM_CH4,10000,1000);
    FTM_PWM_init(FTM0, FTM_CH5,10000,1000);
    FTM_PWM_init(FTM0, FTM_CH6,10000,1000);


    //����ʹ�ܶ�
    gpio_init(PTD15,GPO,0);
    gpio_init(PTA19,GPO,0);
    gpio_init(PTA5 ,GPO,0);
    gpio_init(PTA24,GPO,0);

    /*
    //3 �� ��ת
    //5 �� ��ת
    //4 �� ��ת
    //6 �� ��ת
     */
    led_init(LED0);                                         //��ʼ��LED0��PIT0�ж��õ�LED0

    pit_init_ms(PIT0, 1);                                //��ʼ��PIT0����ʱʱ��Ϊ�� 5ms
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϸ�λ����Ϊ PIT0_IRQHandler
    enable_irq (PIT0_IRQn);                                 //ʹ��PIT0�ж�
    EnableInterrupts;//�ж�����
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


/**********************�жϷ������*******************/
void PIT0_IRQHandler(void)
{
    led_turn(LED0);                             //��˸ LED0
    g_nCarCount++;
      
     ////////////////////////////////////////////////////
   //ʱ��Ƭ��ת
   if(g_nCarCount>=CAR_PERIOD)          //��0��1ms
   {
       g_nCarCount=0;
  
       ////////////////////////////////////////////////////
       //�ٶȲ���
        
       
       /////////////////////////////////////////////////////
       
    
   }
   else if(g_nCarCount==1)              //��1��1ms
   {
       ////////////////////////////////////////////////
       #if Angle_Calculate_Select_Soft  
     
           AD_Calculate_Soft();                   //AD���ݲɼ�,�������
       
       #elif Angle_Calculate_Select_Hard
         
           AD_Calculate_Hard();                 //Ӳ������
           
       #endif
       ////////////////////////////////////////////////   

   }
   else if(g_nCarCount==2)              //��2��1ms
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
        Speed_Calculate(g_fCarAngle,Gyro_Now);      //�ٶȼ���
      }
      
      #elif Angle_Calculate_Select_Hard
      #endif
   }
   else if(g_nCarCount==3)              //��3��1ms
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
           
           
           //Speed_PI();                     //�ٶ�PI���ƣ�����100ms
           
        }
                                      
        //Speed_PI_OUT();                   //PWM������ƣ�����5ms
       ////////////////////////////////////////////////////////////////////
     

   }
   else if(g_nCarCount==4)                 //��4��1ms
   {
   

       g_nCarDirCount++;
       //Spd_Decision();     //�ٶȾ���
       ///////////////////////////////////////
       
      if(g_nCarDirCount >= CAR_DIRECTION_PERIOD ) 
       {
          
          //DirectionControl();           //�������
          g_nCarDirCount = 0;
          g_nCarDirPeriod = 0;
        
       } 
       
       //DirectionControlOutput();  
       
   
   }
   /////////////////////////////////////////////////////

    PIT_Flag_Clear(PIT0);                       //���жϱ�־λ
}

