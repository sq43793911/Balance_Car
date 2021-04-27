/************************************************************************************

* Direction_Control.c
* ����:�������ߺ�����ȡ���������

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.50 
* ����ʱ�䣺2013-06-29

*************************************************************************************/

#include  "Include_def.h"


int32s_t LineCenter;   //��������������
int32s_t Direction;      //�����������
int32s_t Direction_Old;
int32s_t Direction_New;  
int16s_t DirectionOut_L;   //�����������
int16s_t DirectionOut_R;  //�ҵ���������
int8u_t  stopValue = 0;

//====================================
//�������SLineCapture
//���ã��������ߺ�����ȡ
//====================================   

void   LineCapture(void) 
{
    int8u_t   nValue,xValue,mValue=0,zValue=0;
    
    int16s_t   Data;
    
    
    for(nValue=0;nValue<128;nValue++)
    {
       mValue++ ;
       Data=(Pixel[nValue] - Pixel[nValue+3]) ;   
       if(Data>SetData || Data<-(SetData))             //��һ�μ�⵽�ڰױ仯
       {
         for(xValue=nValue+3;xValue<128;xValue++) 
         {
            zValue++ ;
            Data=(Pixel[xValue]-Pixel[xValue+3]);
            if(Data>SetData || Data<-SetData)               //�ڶ��μ�⵽�ڰױ仯
            {
              LineCenter =( (nValue + xValue)/2 +2);
              
              /*if (zValue>5)                       //�����߼��
              {
                stopValue ++;
                zValue = 0;  
                break;
               
              } */
              break;
            } 
            if(zValue>5)                 // �ڶ��μ�ⲻ��������һ�μ���λ��
            {
               LineCenter = nValue+2;
               
               if(Pixel[nValue]>Pixel[nValue+3]  && nValue <60 )
                LineCenter = 128+nValue;
               if(Pixel[nValue]<Pixel[nValue+3] && nValue >70 )
                LineCenter = 128-nValue;
               zValue = 0;
               break;
            }
            
         }
  
       }
       if(mValue>120)            //���һֱ��ⲻ������ֱ������
       {
          LineCenter = DirectionCenter;
          mValue = 0;
          break;
       }
    }

}



  
  
//====================================
//�������SDirectionControl
//���ã��������
//====================================   
void   DirectionControl(void) 
{
     
      
     int32s_t DirectionErro;
     
     //test = 1;
     LineCapture();
     
     
     Direction_Old = Direction_New; 
     
     DirectionErro = LineCenter - DirectionCenter  ;
     
     Direction = (DirectionErro * Direction_P_int)/100 ;

     Direction_New = Direction;

    // test = 0;

}

//====================================
//�������SDirectionControl
//���ã��������
//====================================   
 void DirectionControlOutput(void)
  {    
       
       float fValue;
       float DirectionControlOut;
        //test = 1;     
       fValue = Direction_New - Direction_Old;    
       DirectionControlOut = fValue * (g_nCarDirCount + 1) /CAR_DIRECTION_PERIOD + Direction_Old;
       
       if( DirectionControlOut<0) 
       {
         DirectionOut_L = (int16s_t)  0;
         DirectionOut_R = (int16s_t) -DirectionControlOut;
        
       }
       
       if(DirectionControlOut>=0) 
       {
       DirectionOut_L =  (int16s_t)  DirectionControlOut;     
       DirectionOut_R = (int16s_t)   0; 
       
       }

       
      // test =0;
  }

