/************************************************************************************

* Sample_AD.c
* 描述: AD寄存器读取

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.20 
* 更新时间：2013-05-25

*************************************************************************************/

#include  "Include_def.h"

/***************A/D相关量定义***********************/
////////////////////////////////////////
int16s_t   AD_Value[8]=0;   //采集的AD值

//====================================
//函数名AD_Enable
//作用：AD采样使能
//====================================
void AD_Enable(void)
{      
      test =1;
      ATD0CTL5=0x10;            //开启AD转换  
      test =0;   
} 



int16u_t  AD_Measure12(int8u_t Channel) {
    ATD0CTL5_Cx = Channel;
    while(ATD0STAT0_SCF == 0);
    return ATD0DR0;
}

int16u_t  AD_Measure10(int8u_t Channel) {
    ATD0CTL5_Cx = Channel;
    while(ATD0STAT0_SCF == 0);
    return ATD0DR3;
}

int16u_t  AD_Measure11(int8u_t Channel) {
    ATD0CTL5_Cx = Channel;
    while(ATD0STAT0_SCF == 0);
    return ATD0DR5;
}


int16u_t  ADCValue1(int8u_t channel)
{
  //暂存A/D转换的结果
  int16u_t temp;                        
	ATD0CTL5 = channel;
	//取A/D转换结果                                  
  while(!ATD0STAT0_SCF);
  temp = ATD0DR3;
	return  temp;
}

int16u_t  ADCValue2(int8u_t channel)
{
  //暂存A/D转换的结果
  int16u_t temp;                        
	ATD0CTL5 = channel;
	//取A/D转换结果                                  
  while(!ATD0STAT0_SCF);
  temp = ATD0DR5;
	return  temp;
}



//====================================
//函数名AD_Collect
//作用：采集传感器数值，AD采样
//====================================
void AD_Collect(void)
{   
    
    
    int8u_t   nValue,xValue;
    int32s_t  AD_Value_temp[8];
    int32s_t  AD_temp[20];
    int32s_t  AD_Total=0;
    int32s_t  AD_Average[8];                  
    //test = 1;
    if(ATD0STAT0&0x80)                 //如果队列转换结束队列转换结束
    {
        AD_Value_temp[0]=ATD0DR0;      //读取相应结果寄存器值清相应转换完成通道标志ATD0STAT1
        AD_Value_temp[1]=ATD0DR1;
        AD_Value_temp[2]=ATD0DR2;
        AD_Value_temp[3]=ATD0DR3;			   
        AD_Value_temp[4]=ATD0DR4;
        AD_Value_temp[5]=ATD0DR5;
        AD_Value_temp[6]=ATD0DR6;
        AD_Value_temp[7]=ATD0DR7;                   	
     

    }
      
      for(xValue=2;xValue<8;xValue++)
      {         
        
        for(nValue=0;nValue<20;nValue++)                         //20次均值滤波
        {
          AD_temp[nValue] = AD_Value_temp[xValue];
          AD_Total += AD_temp[nValue];
        }
        
        AD_Average[xValue] = AD_Total/20;
        AD_Total = 0; 
      
      }
      
      for(nValue=2;nValue<8;nValue++) 
      {
           AD_Value[nValue]=(int16s_t)(AD_Average[nValue]);    //保存AD采样值
      }
       /* for(nValue=0;nValue<2;nValue++) 
      {
           AD_Value[nValue]=(int16s_t)(AD_Value_temp[nValue]*4);    //保存AD采样值
      }    */

     //test = 0;

}