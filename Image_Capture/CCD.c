/************************************************************************************

* CCD.c
* 描述:线性CCD自动曝光及图像采集

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.20 
* 更新时间：2013-06-29

*************************************************************************************/


#include  "Include_def.h"

//保存CCD采集到的数据
int8u_t    Pixel[128];

/* 128个像素点的平均AD值 */
int8u_t    PixelAverageValue;
/* 128个像素点的平均电压值的10倍 */
int8u_t        PixelAverageVoltage;

/* 设定目标平均电压值，实际电压的10倍 */
 int16s_t     TargetPixelAverageVoltage = 20;
/* 设定目标平均电压值与实际值的偏差，实际电压的10倍 */
 int16s_t      PixelAverageVoltageError = 0;
/* 设定目标平均电压值允许的偏差，实际电压的10倍 */
 int16s_t      TargetPixelAverageVoltageAllowError = 2;

/* 曝光时间，单位ms */
int8u_t      IntegrationTime = 10;

int8u_t     TimerFlag20ms = 0;

 int8u_t  TimerCnt20ms = 0;                  //static unsigned char

unsigned char send_data_cnt = 0;



//====================================
//函数名ImageCapture
//作用：线性CCD图像采集
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
//函数名StartIntegration
//作用：线性CCD曝光
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
//函数名StartIntegration
//作用：线性CCD曝光控制，1ms一次
//====================================  
void IntegrationControl(void) 
{

    
     int8u_t  integration_piont;
     
  
           TimerCnt20ms++;

            /* 根据曝光时间计算20ms周期内的曝光点 */
            integration_piont =20 - IntegrationTime;
            if(integration_piont >= 2)
            {      /* 曝光点小于2(曝光时间大于18ms)则不进行再曝光 */
              if(integration_piont == TimerCnt20ms)
              StartIntegration();           /* 曝光开始 */
              }
     
     
    if(TimerCnt20ms >= 20) 
    {
        TimerCnt20ms = 0;
        TimerFlag20ms = 1;
        }
    
}



//====================================
//函数名PixelAverage
//作用：线性CCD数据均值
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
//函数名CalculateIntegrationTime
//作用：线性CCD曝光时间控制
//====================================  
    void CalculateIntegrationTime(void) 
    {

    /* 计算128个像素点的平均AD值 */
    PixelAverageValue = PixelAverage(128,Pixel);
    /* 计算128个像素点的平均电压值,实际值的10倍 */
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
//函数名SendImageData
//作用：串口发送数据
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
//函数名SendImageData
//作用：串口发送数据
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
//函数名PixelAverage
//作用：线性CCD数据均值
//====================================  
  void CCDTotalControl(void) 
  {
    

         //test =1; 
         IntegrationControl();
                                                    //CCD曝光
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