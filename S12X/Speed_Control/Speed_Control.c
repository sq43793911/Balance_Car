/************************************************************************************

* Speed_Control.c
* ����:�ٶȸ�������������

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V2.00 
* ����ʱ�䣺2013-05-25

*************************************************************************************/
                              

/*--------------- I N C L U D E S ------------------------------------*/

#include  "Include_def.h"

/*******************************�ٶȱ���***********************************/
///////////////////////////////////////////////////////
int8s_t  direction_R=1;        //�����תΪ1����תΪ-1
int8s_t  direction_L=1;
int16s_t DCDuty_L=0;           //���Ƶ��
int16s_t DCDuty_R=0;           //���Ƶ��

///////////////////////////////////////////////////////
int16s_t ObjectSpeed=0;	       //Ŀ���ٶ�
int16s_t NowSpeed_L_temp=0;
int16s_t NowSpeed_R_temp=0;
int16u_t ms_1000=0;
int16u_t second=0; 

 float  start=0; 
///////////////////////////////////////////////////////
//==========================================
//�������SMotor_Decision
//���ã��ٶȾ���
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
//�������MMotor_Control
//���ã������������PID������ٶ�ֵ
//========================================== 
void Motor_Control_R(void)
 {
    //test = 1 ;
     
    if(DCDuty_R>=0) 
    {
      if(direction_R==1)
      {       
        PWMDTY67= 0;       //��ת
        PWMDTY45 =(DCDuty_R/2);
        direction_R=1;
      }
      if(direction_R==-1)
      {
        PWMDTY67  = 0;	
        PWMDTY45   = 0; 
        
        Delay_us(80); 
        
        PWMDTY67 = 0;	 // ��ת
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
        
        PWMDTY67  = -(DCDuty_R);	       //��ת
        PWMDTY45   = 0;
        direction_R=-1;  
      }
      if(direction_R==-1)
      {
        PWMDTY67  = -(DCDuty_R);	       //��ת
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
        
        PWMDTY23 = 0;	 // ��ת
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
        
        PWMDTY23 = -(DCDuty_L);	         //��ת
        PWMDTY01  = 0;
        direction_L=-1;  
      }
      if(direction_L==-1)
      {
        PWMDTY23 =-(DCDuty_L);	         //��ת
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
      
    DCDuty_R = 0;                    //���ֱ�Ӹ�ֵ
    DCDuty_L = 0;                    //���ֱ�Ӹ�ֵ 
    }
    
   /* if (stopValue > 1)            //������ֹͣ
    {
    DCDuty_R = 0;                    //���ֱ�Ӹ�ֵ
    DCDuty_L = 0;                    //���ֱ�Ӹ�ֵ  
    
    stopValue = 0;
    }  */
    DCDuty_R = 0;                    //���ֱ�Ӹ�ֵ
    DCDuty_L = 0;                    //���ֱ�Ӹ�ֵ  
    
    if( DCDuty_R> DC_Limit)  DCDuty_R= DC_Limit; 
    if( DCDuty_L> DC_Limit)  DCDuty_L= DC_Limit;
    if( DCDuty_R<-DC_Limit)  DCDuty_R=-DC_Limit; 
    if( DCDuty_L<-DC_Limit)  DCDuty_L=-DC_Limit;
    
    //test = 0;
     
    Motor_Control_R();
    Motor_Control_L();
    
    
 }
 /***************************/
 /*       �ٶȲɼ�   5msһ��*/
 ////////////////////////////
 void Speed_Collect(void) 
 {
      
       int8u_t  spd_temp1,spd_temp2;
       int8u_t  time_out;                          //����������ȴ���ʱ
        //test = 1;
       spd_temp1 =PORTA;                           //��߼���
       spd_temp2 =PORTB;                           //�ұ߼���
                               
       PTT_PTT4=1; 
       PTT_PTT6=1;                                //�� PTT_PTT6,7 �� 1��������������
    
       if(direction_L==1)                             
       {
           NowSpeed_L_temp += spd_temp1;
       } 
       else                                         //����ַ�ת
       {
           NowSpeed_L_temp -= spd_temp1;
       }
       if(direction_R==1)                              
       {
           NowSpeed_R_temp += spd_temp2;
       } 
       else                                         //�Ҳ��ַ�ת
       {
           NowSpeed_R_temp -= spd_temp2;
       } 
       
       ////////////////////////////////
       /////////////////////////////////////////////////////
       //��ʱʱ�����
          ms_1000++;
           if(ms_1000>=200)   //��ʱ1s
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
       
       spd_temp1 =PORTA;                            //�ٴζ�ȡPA��PB�ڣ�ȷ���Ѿ�������
       spd_temp2 =PORTB; 
       while(spd_temp1 && spd_temp2 && time_out<200)             //ȷ������
       {
            spd_temp1 = PORTA;
            spd_temp2 = PORTB;
            time_out++;
       }         
       time_out=0;   
       
       PTT_PTT4=0;
       PTT_PTT6=0;                                  //�� PTT_PTT6,7 �� 0, ��ʼ����      
       ////////////////////////////////////////////////////
       //test =0;
 }
