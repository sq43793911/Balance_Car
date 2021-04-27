/************************************************************************************

* Direction_Control.c
* 描述:赛道单边黑线提取及方向控制

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.50 
* 更新时间：2013-06-29

*************************************************************************************/

#include  "Include_def.h"


int32s_t LineCenter;   //赛道黑线中心线
int32s_t Direction;      //方向输出参数
int32s_t Direction_Old;
int32s_t Direction_New;  
int16s_t DirectionOut_L;   //左电机方向参数
int16s_t DirectionOut_R;  //右电机方向参数
int8u_t  stopValue = 0;

//====================================
//函数名LineCapture
//作用：赛道单边黑线提取
//====================================   

void   LineCapture(void) 
{
    int8u_t   nValue,xValue,mValue=0,zValue=0;
    
    int16s_t   Data;
    
    
    for(nValue=0;nValue<128;nValue++)
    {
       mValue++ ;
       Data=(Pixel[nValue] - Pixel[nValue+3]) ;   
       if(Data>SetData || Data<-(SetData))             //第一次检测到黑白变化
       {
         for(xValue=nValue+3;xValue<128;xValue++) 
         {
            zValue++ ;
            Data=(Pixel[xValue]-Pixel[xValue+3]);
            if(Data>SetData || Data<-SetData)               //第二次检测到黑白变化
            {
              LineCenter =( (nValue + xValue)/2 +2);
              
              /*if (zValue>5)                       //起跑线检测
              {
                stopValue ++;
                zValue = 0;  
                break;
               
              } */
              break;
            } 
            if(zValue>5)                 // 第二次检测不到，按第一次检测的位置
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
       if(mValue>120)            //如果一直检测不到，则按直道处理
       {
          LineCenter = DirectionCenter;
          mValue = 0;
          break;
       }
    }

}



  
  
//====================================
//函数名DirectionControl
//作用：方向控制
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
//函数名DirectionControl
//作用：方向控制
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

