/************************************************************************************

* CCD.c
* ����:����CCD�Զ��ع⼰ͼ��ɼ�

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.20 
* ����ʱ�䣺2013-06-29

*************************************************************************************/


#include  "Include_def.h"

//����CCD�ɼ���������
int8u_t    Pixel[128];

/* 128�����ص��ƽ��ADֵ */
int8u_t    PixelAverageValue;
/* 128�����ص��ƽ����ѹֵ��10�� */
int8u_t        PixelAverageVoltage;

/* �趨Ŀ��ƽ����ѹֵ��ʵ�ʵ�ѹ��10�� */
 int16s_t     TargetPixelAverageVoltage = 20;
/* �趨Ŀ��ƽ����ѹֵ��ʵ��ֵ��ƫ�ʵ�ʵ�ѹ��10�� */
 int16s_t      PixelAverageVoltageError = 0;
/* �趨Ŀ��ƽ����ѹֵ�����ƫ�ʵ�ʵ�ѹ��10�� */
 int16s_t      TargetPixelAverageVoltageAllowError = 2;

/* �ع�ʱ�䣬��λms */
int8u_t      IntegrationTime = 10;

int8u_t     TimerFlag20ms = 0;

 int8u_t  TimerCnt20ms = 0;                  //static unsigned char

unsigned char send_data_cnt = 0;



//====================================
//�������SImageCapture
//���ã�����CCDͼ��ɼ�
//====================================   
void ImageCapture(int8u_t * ImageData)                                      //unsigned char * ImageData
 {

    int8u_t    i;
    int16u_t  temp_int;

    TSL1401_SI = 1;         /* SI  = 1 */
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    TSL1401_SI = 0;         /* SI  = 0 */
    SamplingDelay();

    //Delay 20us for sample the first pixel

      // Delay_us(20);
    

    //Sampling Pixel 1
    
    temp_int = (AD_Measure12(0)*8);
    *ImageData++ = (byte)(temp_int>>4);
    TSL1401_CLK = 0;      /* CLK = 0 */

    // Pixel[0] = (byte)AD_Value[1];
    // TSL1401_CLK =0;
  
  
    for(i=0; i<127; i++) {
        SamplingDelay();
        //SamplingDelay();
        TSL1401_CLK = 1;    //CLK = 1 
        SamplingDelay();
        //SamplingDelay();
        //Sampling Pixel 2~128
        temp_int = (AD_Measure12(0)*8);
        *ImageData++ = (byte)(temp_int>>4);
        TSL1401_CLK = 0;    //CLK = 0
    }        
  /*            
  for(i=1; i<128; i++)
  {
        SamplingDelay();
        SamplingDelay();
    TSL1401_CLK = 1;
        SamplingDelay();
        SamplingDelay();
    Pixel[i] = (byte)AD_Value[1];
    TSL1401_CLK  = 0;
  }    */
    //SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    //SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 0;        /* CLK = 0 */
}




 //====================================
//�������SStartIntegration
//���ã�����CCD�ع�
//====================================   
void StartIntegration(void) {

    int8u_t i;

    TSL1401_SI = 1;         /* SI  = 1 */
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    SamplingDelay();
    TSL1401_SI = 0;         /* SI  = 0 */
    SamplingDelay();
    TSL1401_CLK = 0;        /* CLK = 0 */

    for(i=0; i<127; i++) {
        //SamplingDelay();
        SamplingDelay();
        TSL1401_CLK = 1;    /* CLK = 1 */
        //SamplingDelay();
        SamplingDelay();
        TSL1401_CLK = 0;    /* CLK = 0 */
    }
    //SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 1;        /* CLK = 1 */
    //SamplingDelay();
    SamplingDelay();
    TSL1401_CLK = 0;        /* CLK = 0 */
}


//====================================
//�������SStartIntegration
//���ã�����CCD�ع���ƣ�1msһ��
//====================================  
void IntegrationControl(void) 
{

    
     int8u_t  integration_piont;
     
  
           TimerCnt20ms++;

            /* �����ع�ʱ�����20ms�����ڵ��ع�� */
            integration_piont =20 - IntegrationTime;
            if(integration_piont >= 2)
            {      /* �ع��С��2(�ع�ʱ�����18ms)�򲻽������ع� */
              if(integration_piont == TimerCnt20ms)
              StartIntegration();           /* �ع⿪ʼ */
              }
     
     
    if(TimerCnt20ms >= 20) 
    {
        TimerCnt20ms = 0;
        TimerFlag20ms = 1;
        }
    
}



//====================================
//�������SPixelAverage
//���ã�����CCD���ݾ�ֵ
//====================================  
unsigned char PixelAverage(unsigned char len, unsigned char *data) {
  int8u_t    i;
  int16u_t sum = 0;
  for(i = 0; i<len; i++) {
    sum = sum + *data++;
  }
  return ((int8u_t)(sum/len));
}
    
//====================================
//�������SCalculateIntegrationTime
//���ã�����CCD�ع�ʱ�����
//====================================  
    void CalculateIntegrationTime(void) 
    {

    /* ����128�����ص��ƽ��ADֵ */
    PixelAverageValue = PixelAverage(128,Pixel);
    /* ����128�����ص��ƽ����ѹֵ,ʵ��ֵ��10�� */
    PixelAverageVoltage = (unsigned char)((int)PixelAverageValue * 25 / 128);

    PixelAverageVoltageError = TargetPixelAverageVoltage - PixelAverageVoltage;
    if(PixelAverageVoltageError < -TargetPixelAverageVoltageAllowError)
        IntegrationTime--;
    if(PixelAverageVoltageError > TargetPixelAverageVoltageAllowError)
        IntegrationTime++;
    if(IntegrationTime <= 1)
        IntegrationTime = 1;
    if(IntegrationTime >= 20)
        IntegrationTime = 20;
}


//====================================
//�������SSendImageData
//���ã����ڷ�������
//====================================  

void SendHex(unsigned char hex) {
  unsigned char temp;
  temp = hex >> 4;
  if(temp < 10) {
    SCI0_SendChar1(temp + '0');
  } else {
    SCI0_SendChar1(temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if(temp < 10) {
    SCI0_SendChar1(temp + '0');
  } else {
    SCI0_SendChar1(temp - 10 + 'A');
  }
}

//====================================
//�������SSendImageData
//���ã����ڷ�������
//====================================  

void SendImageData(unsigned char * ImageData) {

    unsigned char i;
    unsigned char crc = 0;

    /* Send Data */
    SCI0_SendChar1('*');
    SCI0_SendChar1('L');
    SCI0_SendChar1('D');

    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);

    for(i=0; i<128; i++) {
      SendHex(*ImageData++);
    }

    SendHex(crc);
    SCI0_SendChar1('#');
}




 //====================================
//�������SPixelAverage
//���ã�����CCD���ݾ�ֵ
//====================================  
  void CCDTotalControl(void) 
  {
    

         //test =1; 
         IntegrationControl();
                                                    //CCD�ع�
        ////////////////////////////////////////
        /* 20ms Task */
        
        
        if(TimerFlag20ms == 1) {
            TimerFlag20ms = 0;


            /* Sampling CCD data */
            ImageCapture(Pixel);

            /* Calculate Integration Time */
            CalculateIntegrationTime();
            /* Send data to CCDView every 100ms */
           /* if(++send_data_cnt >= 5) {
                send_data_cnt = 0;
                SendImageData(Pixel);
            }  */

    }
    
    //test =0;
  }