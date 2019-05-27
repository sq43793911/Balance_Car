/************************************************************************************

* SCI0.c
* 描述:线性CCD自动曝光及图像采集

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.00 
* 更新时间：2013-07-14

*************************************************************************************/

#include  "Include_def.h"




/*
*********************************************************************************************************
* Description: SCI0_SendChar
*********************************************************************************************************
*/
int8u_t SCI0_SendChar(int8u_t Chr)
{
  if(SCI0SR1_TDRE == 0) {              /* Is the transmitter empty? */
    return ERR_TXFULL;                 /* If no then error */
  }
  SCI0DRL = (int8u_t)Chr;
  return ERR_OK;                       /* OK */
}


/*
*********************************************************************************************************
* Description: SCI0_SendChar1
*********************************************************************************************************
*/
void SCI0_SendChar1(int8u_t Chr)
{
  while(SCI0SR1_TDRE == 0) {           /* Is the transmitter empty? */
  }
  SCI0DRL = (int8u_t)Chr;
}



/*
*********************************************************************************************************
* Description: SCI0_RecvChar
*********************************************************************************************************
*/
int8u_t SCI0_RecvChar(int8u_t *Chr)
{
  int8u_t Result = ERR_OK;             /* Return error code */
  int8u_t StatReg = SCI0SR1;           /* Read status register */

  if (StatReg & (SCI0SR1_OR_MASK|SCI0SR1_NF_MASK|SCI0SR1_FE_MASK|SCI0SR1_PF_MASK)) { /* Is any error flag set? */
    Result = ERR_COMMON;               /* If yes then set common error value */
  } else if ((StatReg & SCI0SR1_RDRF_MASK) == 0) {  /* Is the reciver empty and no error is set? */
    return ERR_RXEMPTY;                /* If yes then error */
  } else {
    /* Else branch due to MISRA compliance */
  }
  *Chr = SCI0DRL;                      /* Read data from the receiver */
  return Result;                       /* Return error code */
}



/*
*********************************************************************************************************
* Description: SCI0_RecvChar1
*********************************************************************************************************
*/
int8u_t SCI0_RecvChar1(void)
{
  while(SCI0SR1_RDRF == 0) {           /* Is the reciver empty? */
  }
  return (int8u_t)SCI0DRL;             /* Read data from the receiver */
}