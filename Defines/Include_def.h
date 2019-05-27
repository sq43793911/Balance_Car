
/************************************************************************************

* Include_def.h
* 描述:包含各文件的头文件，屏蔽部分无意义警告

* 所支持的芯片:9S12XS
* 所支持的编译器：CodeWarrior 5.X

* 作者：    孙谦       (第七届电磁)


* 程序版本：V1.10 
* 更新时间：2013-05-25

*************************************************************************************/
#ifndef Include_def_H        //if no define
#define Include_def_H        //define  即如果没有定义的话，则定义。。。。(防止其他函数多次调用此头文件时而重复定义)

/* 头文件包含 */
#include <hidef.h>            /* common defines and macros */
#include <MC9S12XS128.h>      /* derivative information */

#include <math.h>

#include "Com_def.h"         //公共宏定义
#include "System_Init.h"      //初始化模块函数          
#include "Delay.h"            //延时模块
#include "Kalman_Filter.h"    //卡尔曼滤波函数
#include "Speed_PID.h"        //速度PID和差速PID
#include "Sample_AD.h"        //AD采样及数据处理函数
#include "Balance_Control.h"  //角度角速度采样，及平衡控制
#include "Speed_Control.h"    //电机控制
#include  "CCD.h"                   //线性CCD自动曝光及图像采集
#include  "Direction_Control.h" //赛道单边黑线提取及方向控制
#include  "SCI0.h"                    //串口

/* 屏蔽编译器的部分warning */
#pragma MESSAGE DISABLE C5905   /* warning-数据被1乘 */
#pragma MESSAGE DISABLE C12056  /* warning-函数被优化 */

#endif //结束定义，配合#ifndef使用