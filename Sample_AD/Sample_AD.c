/************************************************************************************

* Sample_AD.c
* ����: AD�Ĵ�����ȡ

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.20 
* ����ʱ�䣺2013-05-25

*************************************************************************************/

#include  "Include_def.h"

/***************A/D���������***********************/
////////////////////////////////////////
int16s_t   AD_Value[8]=0;   //�ɼ���ADֵ

//====================================
//�������SAD_Enable
//���ã�AD����ʹ��
//====================================
void AD_Enable(void)
{      
      test =1;
      ATD0CTL5=0x10;            //����ADת��  
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
  //�ݴ�A/Dת���Ľ��
  int16u_t temp;                        
	ATD0CTL5 = channel;
	//ȡA/Dת�����                                  
  while(!ATD0STAT0_SCF);
  temp = ATD0DR3;
	return  temp;
}

int16u_t  ADCValue2(int8u_t channel)
{
  //�ݴ�A/Dת���Ľ��
  int16u_t temp;                        
	ATD0CTL5 = channel;
	//ȡA/Dת�����                                  
  while(!ATD0STAT0_SCF);
  temp = ATD0DR5;
	return  temp;
}



//====================================
//�������SAD_Collect
//���ã��ɼ���������ֵ��AD����
//====================================
void AD_Collect(void)
{   
    
    
    int8u_t   nValue,xValue;
    int32s_t  AD_Value_temp[8];
    int32s_t  AD_temp[20];
    int32s_t  AD_Total=0;
    int32s_t  AD_Average[8];                  
    //test = 1;
    if(ATD0STAT0&0x80)                 //�������ת����������ת������
    {
        AD_Value_temp[0]=ATD0DR0;      //��ȡ��Ӧ����Ĵ���ֵ����Ӧת�����ͨ����־ATD0STAT1
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
        
        for(nValue=0;nValue<20;nValue++)                         //20�ξ�ֵ�˲�
        {
          AD_temp[nValue] = AD_Value_temp[xValue];
          AD_Total += AD_temp[nValue];
        }
        
        AD_Average[xValue] = AD_Total/20;
        AD_Total = 0; 
      
      }
      
      for(nValue=2;nValue<8;nValue++) 
      {
           AD_Value[nValue]=(int16s_t)(AD_Average[nValue]);    //����AD����ֵ
      }
       /* for(nValue=0;nValue<2;nValue++) 
      {
           AD_Value[nValue]=(int16s_t)(AD_Value_temp[nValue]*4);    //����AD����ֵ
      }    */

     //test = 0;

}