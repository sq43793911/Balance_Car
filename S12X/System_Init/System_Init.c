/************************************************************************************

* System_Init.c
* 描述:寄存器配置，包括锁相环、I/O、PWM模块、实时时钟、AD

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.10 
* 更新时间：2013-05-25

*************************************************************************************/

/*--------------- I N C L U D E S ------------------------------------*/

#include  "Include_def.h"

/*********************************************************************
函数名:       PORT_Init                          
作用:         初始化普通I/O端口
输入管脚:     PTIT               
输出管脚:     PTT                                                
备注:         光电传感器输入等用途                                            
*********************************************************************/
void PORT_Init(void)
{

   //PTT_PTT2 为输出 蜂鸣器   
   //DDRT_DDRT2=1;    //  PTT_PTT2 为输出
   //PTT_PTT2=0; 
   
   //PTT_PTT6 测速计数器清零
   DDRT_DDRT4=1;  
   DDRT_DDRT6=1;//PTT 6,7位为输出方式
   PTT_PTT4=1;
   PTT_PTT6=1;  //Clear1;
   
   //PORTA PORTB GPIO口 读测速计数器的值  
   DDRA=0X00;    //A口为输入方式    
   DDRB=0X00;    //B口为输入方式   
   PUCR_PUPAE=0; //A口上拉
   PUCR_PUPBE=0; //B口上拉 
   
   //PS0、PS1识别电机正反转
   //DDRS&=0xFC;   //PS0、PS1设为输入
   
   //陀螺仪零点校正指示灯
   //DDRH_DDRH0=1; //将PH0设为输出
                     
}

/*********************************************************************
函数名:       CCD_IO_Init                         
作用:         初始化普通I/O端口
输入管脚:     PTIT               
输出管脚:     PTT                                                
备注:         CCD                                            
*********************************************************************/
void CCD_IO_Init(void) {
    TSL1401_CLK_DDR = 1;
    TSL1401_SI_DDR  = 1;
    TSL1401_CLK = 0;
    TSL1401_SI  = 0;
    
    
    ////////测试用
    
    test_DDR  = 1 ;
    test = 0;
}

 /*********************************************************************
函数名:       Init_Pixel_Array                         
作用:         初始化普通I/O端口
输入管脚:     PTIT               
输出管脚:     PTT                                                
备注:         CCD                                            
*********************************************************************/
void Init_Pixel_Array(void) 
{
     int8u_t i;
     int8u_t *pixel_pt;
    /* Init Pixel Array */
    pixel_pt = Pixel;
    for(i=0; i<128+10; i++) {
        *pixel_pt++ = 0;
    }
}

/*********************************************************************
函数名:       FBE_Init                          
作用:         设置总线时钟
输入管脚:     None               
输出管脚:     None                                                   
备注:         晶振频率(OSC):16MHz，总线频率(BUS):80MHz，单位时钟:0.0125us                                              
*********************************************************************/

void FBE_Init(void)            //函数作用:设置总线时钟
{
    
    CLKSEL=0X00;			         //disengage PLL to system
    PLLCTL_PLLON=1;			       //turn on PLL
    SYNR =0xc0 | 0x09;         // Fvco=2*osc*(1+SYNRDIV)/(1+REFDIV)
                               //Fpll=Fvco/(2*POSTDIV) Fbus=Fpll/2
    REFDV=0x80 | 0x01; 
    POSTDIV=0x00;              //pllclock=2*osc*(1+SYNRDIV)/(1+REFDIV)=160MHz;
    _asm(nop);                 //BUS CLOCK=80M
    _asm(nop);
    while(!(CRGFLG_LOCK==1));	 //when pll is steady ,then use it;
    CLKSEL_PLLSEL =1;		       //engage PLL to system; 
    PLLCTL_PCE=1;  
    
}

/*********************************************************************
函数名:       SCI0_Init                          
作用:         设置串口
输入管脚:     None               
输出管脚:     None                                                   
备注:         晶振频率(OSC):16MHz，总线频率(BUS):80MHz，单位时钟:0.0125us，波特率:115200                                              
*********************************************************************/
void SCI0_Init(void)
{
/*  Init_SCI init code */
  SCI0CR1 = 0x00;
  SCI0SR2 = 0x80;                      /* Switch to the alternative register set */
  SCI0ASR1 = 0x83;                     /* Clear alternative status flags */
  SCI0ACR1 = 0x00;
  SCI0ACR2 = 0x00;
  SCI0SR2 = 0x00;                      /* Switch to the normal register set */
  (void) SCI0SR1;                      /* Reset interrupt request flags */
  SCI0CR2 = 0x00;                      /* Disable error interrupts */
  SCI0BD = 0x2C;                       /* Set prescaler bits */
  
  SCI0CR2 |= (SCI0CR2_TE_MASK | SCI0CR2_RE_MASK); /* Enable transmitter, Enable receiver */
}


/*********************************************************************
函数名:       PWMA_Init，PWMB_Init                          
作用:         初始化PWM脉宽调制波
输入管脚:     None               
输出管脚:     PWM1(PP1),PWM3(PP3),PWM5(PP5)     
                                              
备注:         电机控制。电机PWM周期一般为0.1ms(10kHz).

              
              本单片机共有8路8位的专用PWM端口，为了提高控制精度，将其合并为4路16位PWM.                               
*********************************************************************/

//========================================================================================
//函数名：Forward_Init
//作用：初始化PWM01,PWM23和PWM45，PWM67分别用来控制左右电机正反转。PWM占空比越高，电机转速越快
//      注意PWM23和PWM45不能同时输出！
//========================================================================================

 void Forward_Init(void)         //函数作用：初始化PWMB，输出PWM波，输出端口为PWM1,PWM3和PWM5,PWM7接电机驱动
 {
   PWMCTL_CON01 = 1;
   PWMCTL_CON23 = 1;          
   PWMCTL_CON45 = 1;      
   PWMCTL_CON67 = 1;        //PWMCTL      PWM控制寄存器 使用两个8位端口PWM0、PWM1；PWM2、PWM3；PWM4、PWM5；PWM6、PWM7组合输出16位PWM波 
  

   PWME_PWME1 = 0;
   PWME_PWME3 = 0;			      
   PWME_PWME5 = 0;   
   PWME_PWME7 = 0;          //PWME        PWM使能寄存器   先停止PWM1、PWM3、PWM5、PWM7.
  
   PWMPRCLK_PCKA = 4;         //PWMPRCLK    PWM时钟预分频寄存器       clockA  16分频，clockA = busclk/16 = 5MHz;
   PWMPRCLK_PCKB = 4;         //PWMPRCLK    PWM时钟预分频寄存器       clockB  16分频，clockB = busclk/16 = 5MHz; 								 
   PWMSCLA=1;                 // Clock SA = Clock A / (2 * PWMSCLA)  = 2.5 M
	 PWMSCLB=1;                 // Clock SB = Clock B / (2 * PWMSCLA)  = 2.5 M
	                              
   PWMCLK_PCLK3 = 0;        //PWMCLK      PWM时钟选择寄存器                PWM3使用clockB为时钟，单位时钟为0.2us         
   PWMCLK_PCLK7 = 0;        //PWMCLK      PWM时钟选择寄存器                PWM7使用clockA为时钟，单位时钟为0.2us     
   PWMCLK_PCLK1 = 1;        //通道1选择 Clock SB
	 PWMCLK_PCLK5 = 1;        //通道5选择 Clock SB     
   
   PWMPOL |= 0b10101010;    // 通道1357输出极性 首先为高 占空比计数器计数完毕变为低  
  
   PWMCNT01 =  0;
   PWMCNT23 =  0;              
   PWMCNT45 =  0;
   PWMCNT67 =  0;              //PWMCNTx     PWM计数寄存器     PWM01、PWM23、PWM45、PWM67计数器清零(递增型计数器)
  
   PWMDTY01 = 20;
   PWMDTY23 = 20;           
   PWMDTY45 = 20;
   PWMDTY67 = 20;              //PWMDTYx     PWM比较寄存器(PWM高电平)    计数器比较匹配后输出相应的电平:PWM高电平时间：0个单位时钟，占空比0/2000 = 0%    
   
   PWMCAE   = 0x00;   //脉冲模式为左对齐模式
   
   PWMPER01 = 250;          
   PWMPER23 = 500;
   PWMPER45 = 250;            
   PWMPER67 = 500;     //PWMPERx     PWM预置数寄存器(PWM周期)    PWM周期, 500个单位时钟，约为100us(10kHz)         
  
   PWME_PWME1 = 1;          //PWME        PWM使能寄存器                    使能PWM1，PWM1为输出端口
   PWME_PWME3 = 1;          //PWME        PWM使能寄存器                    使能PWM3，PWM3为输出端口
   PWME_PWME5 = 1;          //PWME        PWM使能寄存器                    使能PWM5，PWM5为输出端口
   PWME_PWME7 = 1;          //PWME        PWM使能寄存器                    使能PWM7，PWM7为输出端口
  
 }
 

/*********************************************************************
函数名:       RTI_Init                          
作用:         初始化RTI定时中断
输入管脚:     None               
输出管脚:     None                                                   
备注:         设置RTI中断频率，每1ms中断一次                                                 
*********************************************************************/
  
void RTI_Init(void)
{
    
   RTICTL = 0x97;              //中断时间：2ms    1011 1111  实时中断的溢出时钟周期=（RTR[3:0]+1) x (2的（RTR[6:4] + 9）次方)/OSCCLK
                               // 0x97~1ms中断~16*1000分频;0xbf~4ms中断  0x59~10ms中断  0x54~5ms中断   0x9F~2ms中断   0x97~1ms中断
   CRGINT = 0x80;              //使能RTI中断
}

/*********************************************************************
函数名:       ATD_Init                          
作用:         AD转换初始化
输入管脚:     AN0~AN7               
输出管脚:     None                                                   
备注:         AD转换初始化是XS单片机与DG单片机区别最大的地方                                              
*********************************************************************/

void ATD_Init(void)
{  
     
    ATD0CTL0=0x07;              //多通道转换，转换16个通道，在AN7完成后回到AN2   
    ATD0CTL1=0x20;              //10位精度，外部触发源为AN0，采样前不放电    
    ATD0CTL2=0x40;              //禁止ATD比较中断，ATD队列转换完成中断使能，禁止外部触发，标志位快速清零    
    ATD0CTL3=0xc0;              //右对齐，每个转换序列的长度为5，非FIFO存储模式    
    ATD0CTL4=0x1f;              //采样时间包含4个ATD时钟周期，AD时钟为BUS_CLK/(2*(9+1))
                                           //A/D时钟频率应满足500Hz<=ATD_CLK<=2MHz      
    ATD0CTL5=0x10;              //特殊转换通道被使能，单独的转换序列，几个通道循环采样，从AN8通道开始采样
    
    
    /*
     ATD0CTL4 = 0x04;                    //Set sample time and prescaler 
    ATD0CTL3 = 0x88;                    //Right justified data,Conversion Sequence Length = 1 
    ATD0CTL0 = 0x0F;                    // Set wrap around 
    ATD0CTL1 = 0x4F;                    // 12-bit data 
    ATD0CTL2 = 0x40;                    // Fast Flag Clear
      */

}

/*********************************************************************
函数名:       System_Init                          
作用:         调用其他子函数，对单片机各模块进行初始化 
输入管脚:     None               
输出管脚:     None                                                  
备注:                                                
*********************************************************************/

void System_Init(void)     
{
    
    FBE_Init();                        //初始化总线时钟
    SCI0_Init();
    PORT_Init();                       //初始化普通I/O端口
    CCD_IO_Init();                    //初始化CCD时钟控制
    Init_Pixel_Array();               //初始化像素信息  
    Forward_Init();                    //初始化PWM23、PWM45、PWM6和PWM7，控制电机    
    ATD_Init();                        //初始化AD模块   
    RTI_Init();                        //初始化RTI定时中断，定时1ms
    
}

