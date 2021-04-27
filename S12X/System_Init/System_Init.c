/************************************************************************************

* System_Init.c
* ����:�Ĵ������ã��������໷��I/O��PWMģ�顢ʵʱʱ�ӡ�AD

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.10 
* ����ʱ�䣺2013-05-25

*************************************************************************************/

/*--------------- I N C L U D E S ------------------------------------*/

#include  "Include_def.h"

/*********************************************************************
������:       PORT_Init                          
����:         ��ʼ����ͨI/O�˿�
����ܽ�:     PTIT               
����ܽ�:     PTT                                                
��ע:         ��紫�����������;                                            
*********************************************************************/
void PORT_Init(void)
{

   //PTT_PTT2 Ϊ��� ������   
   //DDRT_DDRT2=1;    //  PTT_PTT2 Ϊ���
   //PTT_PTT2=0; 
   
   //PTT_PTT6 ���ټ���������
   DDRT_DDRT4=1;  
   DDRT_DDRT6=1;//PTT 6,7λΪ�����ʽ
   PTT_PTT4=1;
   PTT_PTT6=1;  //Clear1;
   
   //PORTA PORTB GPIO�� �����ټ�������ֵ  
   DDRA=0X00;    //A��Ϊ���뷽ʽ    
   DDRB=0X00;    //B��Ϊ���뷽ʽ   
   PUCR_PUPAE=0; //A������
   PUCR_PUPBE=0; //B������ 
   
   //PS0��PS1ʶ��������ת
   //DDRS&=0xFC;   //PS0��PS1��Ϊ����
   
   //���������У��ָʾ��
   //DDRH_DDRH0=1; //��PH0��Ϊ���
                     
}

/*********************************************************************
������:       CCD_IO_Init                         
����:         ��ʼ����ͨI/O�˿�
����ܽ�:     PTIT               
����ܽ�:     PTT                                                
��ע:         CCD                                            
*********************************************************************/
void CCD_IO_Init(void) {
    TSL1401_CLK_DDR = 1;
    TSL1401_SI_DDR  = 1;
    TSL1401_CLK = 0;
    TSL1401_SI  = 0;
    
    
    ////////������
    
    test_DDR  = 1 ;
    test = 0;
}

 /*********************************************************************
������:       Init_Pixel_Array                         
����:         ��ʼ����ͨI/O�˿�
����ܽ�:     PTIT               
����ܽ�:     PTT                                                
��ע:         CCD                                            
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
������:       FBE_Init                          
����:         ��������ʱ��
����ܽ�:     None               
����ܽ�:     None                                                   
��ע:         ����Ƶ��(OSC):16MHz������Ƶ��(BUS):80MHz����λʱ��:0.0125us                                              
*********************************************************************/

void FBE_Init(void)            //��������:��������ʱ��
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
������:       SCI0_Init                          
����:         ���ô���
����ܽ�:     None               
����ܽ�:     None                                                   
��ע:         ����Ƶ��(OSC):16MHz������Ƶ��(BUS):80MHz����λʱ��:0.0125us��������:115200                                              
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
������:       PWMA_Init��PWMB_Init                          
����:         ��ʼ��PWM������Ʋ�
����ܽ�:     None               
����ܽ�:     PWM1(PP1),PWM3(PP3),PWM5(PP5)     
                                              
��ע:         ������ơ����PWM����һ��Ϊ0.1ms(10kHz).

              
              ����Ƭ������8·8λ��ר��PWM�˿ڣ�Ϊ����߿��ƾ��ȣ�����ϲ�Ϊ4·16λPWM.                               
*********************************************************************/

//========================================================================================
//��������Forward_Init
//���ã���ʼ��PWM01,PWM23��PWM45��PWM67�ֱ������������ҵ������ת��PWMռ�ձ�Խ�ߣ����ת��Խ��
//      ע��PWM23��PWM45����ͬʱ�����
//========================================================================================

 void Forward_Init(void)         //�������ã���ʼ��PWMB�����PWM��������˿�ΪPWM1,PWM3��PWM5,PWM7�ӵ������
 {
   PWMCTL_CON01 = 1;
   PWMCTL_CON23 = 1;          
   PWMCTL_CON45 = 1;      
   PWMCTL_CON67 = 1;        //PWMCTL      PWM���ƼĴ��� ʹ������8λ�˿�PWM0��PWM1��PWM2��PWM3��PWM4��PWM5��PWM6��PWM7������16λPWM�� 
  

   PWME_PWME1 = 0;
   PWME_PWME3 = 0;			      
   PWME_PWME5 = 0;   
   PWME_PWME7 = 0;          //PWME        PWMʹ�ܼĴ���   ��ֹͣPWM1��PWM3��PWM5��PWM7.
  
   PWMPRCLK_PCKA = 4;         //PWMPRCLK    PWMʱ��Ԥ��Ƶ�Ĵ���       clockA  16��Ƶ��clockA = busclk/16 = 5MHz;
   PWMPRCLK_PCKB = 4;         //PWMPRCLK    PWMʱ��Ԥ��Ƶ�Ĵ���       clockB  16��Ƶ��clockB = busclk/16 = 5MHz; 								 
   PWMSCLA=1;                 // Clock SA = Clock A / (2 * PWMSCLA)  = 2.5 M
	 PWMSCLB=1;                 // Clock SB = Clock B / (2 * PWMSCLA)  = 2.5 M
	                              
   PWMCLK_PCLK3 = 0;        //PWMCLK      PWMʱ��ѡ��Ĵ���                PWM3ʹ��clockBΪʱ�ӣ���λʱ��Ϊ0.2us         
   PWMCLK_PCLK7 = 0;        //PWMCLK      PWMʱ��ѡ��Ĵ���                PWM7ʹ��clockAΪʱ�ӣ���λʱ��Ϊ0.2us     
   PWMCLK_PCLK1 = 1;        //ͨ��1ѡ�� Clock SB
	 PWMCLK_PCLK5 = 1;        //ͨ��5ѡ�� Clock SB     
   
   PWMPOL |= 0b10101010;    // ͨ��1357������� ����Ϊ�� ռ�ձȼ�����������ϱ�Ϊ��  
  
   PWMCNT01 =  0;
   PWMCNT23 =  0;              
   PWMCNT45 =  0;
   PWMCNT67 =  0;              //PWMCNTx     PWM�����Ĵ���     PWM01��PWM23��PWM45��PWM67����������(�����ͼ�����)
  
   PWMDTY01 = 20;
   PWMDTY23 = 20;           
   PWMDTY45 = 20;
   PWMDTY67 = 20;              //PWMDTYx     PWM�ȽϼĴ���(PWM�ߵ�ƽ)    �������Ƚ�ƥ��������Ӧ�ĵ�ƽ:PWM�ߵ�ƽʱ�䣺0����λʱ�ӣ�ռ�ձ�0/2000 = 0%    
   
   PWMCAE   = 0x00;   //����ģʽΪ�����ģʽ
   
   PWMPER01 = 250;          
   PWMPER23 = 500;
   PWMPER45 = 250;            
   PWMPER67 = 500;     //PWMPERx     PWMԤ�����Ĵ���(PWM����)    PWM����, 500����λʱ�ӣ�ԼΪ100us(10kHz)         
  
   PWME_PWME1 = 1;          //PWME        PWMʹ�ܼĴ���                    ʹ��PWM1��PWM1Ϊ����˿�
   PWME_PWME3 = 1;          //PWME        PWMʹ�ܼĴ���                    ʹ��PWM3��PWM3Ϊ����˿�
   PWME_PWME5 = 1;          //PWME        PWMʹ�ܼĴ���                    ʹ��PWM5��PWM5Ϊ����˿�
   PWME_PWME7 = 1;          //PWME        PWMʹ�ܼĴ���                    ʹ��PWM7��PWM7Ϊ����˿�
  
 }
 

/*********************************************************************
������:       RTI_Init                          
����:         ��ʼ��RTI��ʱ�ж�
����ܽ�:     None               
����ܽ�:     None                                                   
��ע:         ����RTI�ж�Ƶ�ʣ�ÿ1ms�ж�һ��                                                 
*********************************************************************/
  
void RTI_Init(void)
{
    
   RTICTL = 0x97;              //�ж�ʱ�䣺2ms    1011 1111  ʵʱ�жϵ����ʱ������=��RTR[3:0]+1) x (2�ģ�RTR[6:4] + 9���η�)/OSCCLK
                               // 0x97~1ms�ж�~16*1000��Ƶ;0xbf~4ms�ж�  0x59~10ms�ж�  0x54~5ms�ж�   0x9F~2ms�ж�   0x97~1ms�ж�
   CRGINT = 0x80;              //ʹ��RTI�ж�
}

/*********************************************************************
������:       ATD_Init                          
����:         ADת����ʼ��
����ܽ�:     AN0~AN7               
����ܽ�:     None                                                   
��ע:         ADת����ʼ����XS��Ƭ����DG��Ƭ���������ĵط�                                              
*********************************************************************/

void ATD_Init(void)
{  
     
    ATD0CTL0=0x07;              //��ͨ��ת����ת��16��ͨ������AN7��ɺ�ص�AN2   
    ATD0CTL1=0x20;              //10λ���ȣ��ⲿ����ԴΪAN0������ǰ���ŵ�    
    ATD0CTL2=0x40;              //��ֹATD�Ƚ��жϣ�ATD����ת������ж�ʹ�ܣ���ֹ�ⲿ��������־λ��������    
    ATD0CTL3=0xc0;              //�Ҷ��룬ÿ��ת�����еĳ���Ϊ5����FIFO�洢ģʽ    
    ATD0CTL4=0x1f;              //����ʱ�����4��ATDʱ�����ڣ�ADʱ��ΪBUS_CLK/(2*(9+1))
                                           //A/Dʱ��Ƶ��Ӧ����500Hz<=ATD_CLK<=2MHz      
    ATD0CTL5=0x10;              //����ת��ͨ����ʹ�ܣ�������ת�����У�����ͨ��ѭ����������AN8ͨ����ʼ����
    
    
    /*
     ATD0CTL4 = 0x04;                    //Set sample time and prescaler 
    ATD0CTL3 = 0x88;                    //Right justified data,Conversion Sequence Length = 1 
    ATD0CTL0 = 0x0F;                    // Set wrap around 
    ATD0CTL1 = 0x4F;                    // 12-bit data 
    ATD0CTL2 = 0x40;                    // Fast Flag Clear
      */

}

/*********************************************************************
������:       System_Init                          
����:         ���������Ӻ������Ե�Ƭ����ģ����г�ʼ�� 
����ܽ�:     None               
����ܽ�:     None                                                  
��ע:                                                
*********************************************************************/

void System_Init(void)     
{
    
    FBE_Init();                        //��ʼ������ʱ��
    SCI0_Init();
    PORT_Init();                       //��ʼ����ͨI/O�˿�
    CCD_IO_Init();                    //��ʼ��CCDʱ�ӿ���
    Init_Pixel_Array();               //��ʼ��������Ϣ  
    Forward_Init();                    //��ʼ��PWM23��PWM45��PWM6��PWM7�����Ƶ��    
    ATD_Init();                        //��ʼ��ADģ��   
    RTI_Init();                        //��ʼ��RTI��ʱ�жϣ���ʱ1ms
    
}

