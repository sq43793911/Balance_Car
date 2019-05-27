/************************************************************************************

* Balance_Control.c
* ����:�ǶȽ��ٶ��˲�������ģֱ������

* ��֧�ֵ�оƬ:9S12XS
* ��֧�ֵı�������CodeWarrior 5.X

* ���ߣ�    ��ǫ       (���߽���)


* ����汾��V1.70 
* ����ʱ�䣺2013-05-25

*************************************************************************************/
                              

/*--------------- I N C L U D E S ------------------------------------*/

#include  "Include_def.h"

/*****************����*****************/
////////////////////////////////////////////
int16s_t g_nCarAcceVal;           //���ٶ�
int16s_t g_nCarGyroVal;           //�Ǽ��ٶ�
int16s_t g_nCarAngle;             //����Ƕ�
int32s_t g_lnCarAngleSigma;       //�Ǽ��ٶȻ���

////////////////////////////////////////////
float  Angle_m;                   //���ٶȼ�����ĽǶ�
float  Gyro_m;                    //�����Ǽ�����Ľ��ٶ�
 
////////////////////////////////////////////
int16s_t g_nLeftMotorOut;
int16s_t g_nRightMotorOut;

int16s_t Filter_AngleDot;
int16u_t Cnt_ErrAngle = 0;        //�쳣�Ƕ��ۼ�


//====================================
//������飬���ڶԴ� -1~+1 �� asin ��Ӧ�ĽǶ�
//====================================
const float  Asin_to_Angle[201]={ -90.000000,-81.890386,-78.521659,-75.930132,-73.739795,-71.805128,-70.051556,-68.434815,
-66.926082,-65.505352,-64.158067,-62.873247,-61.642363,-60.458639,-59.316583,-58.211669,-57.140120,-56.098738,-55.084794,
-54.095931,-53.130102,-52.185511,-51.260575,-50.353889,-49.464198,-48.590378,-47.731416,-46.886394,-46.054480,-45.234915,
-44.427004,-43.630109,-42.843643,-42.067065,-41.299873,-40.541602,-39.791819,-39.050123,-38.316134,-37.589503,-36.869898,
-36.157008,-35.450543,-34.750226,-34.055798,-33.367013,-32.683639,-32.005455,-31.332251,-30.663830,-30.000000,-29.340582,
-28.685402,-28.034297,-27.387108,-26.743684,-26.103881,-25.467560,-24.834587,-24.204835,-23.578178,-22.954499,-22.333683,
-21.715617,-21.100196,-20.487315,-19.876874,-19.268775,-18.662925,-18.059230,-17.457603,-16.857956,-16.260205,-15.664267,
-15.070062,-14.477512,-13.886540,-13.297072,-12.709033,-12.122352,-11.536959,-10.952784,-10.369760,-9.787819,-9.206896,
-8.626927,-8.047846,-7.469592,-6.892103,-6.315316,-5.739170,-5.163607,-4.588566,-4.013987,-3.439813,-2.865984,-2.292443,
-1.719131,-1.145992,-0.572967,0.000000,0.572967,1.145992,1.719131,2.292443,2.865984,3.439813,4.013987,4.588566,5.163607,
5.739170,6.315316,6.892103,7.469592,8.047846,8.626927,9.206896,9.787819,10.369760,10.952784,11.536959,12.122352,12.709033,
13.297072,13.886540,14.477512,15.070062,15.664267,16.260205,16.857956,17.457603,18.059230,18.662925,19.268775,19.876874,
20.487315,21.100196,21.715617,22.333683,22.954499,23.578178,24.204835,24.834587,25.467560,26.103881,26.743684,27.387108,
28.034297,28.685402,29.340582,30.000000,30.663830,31.332251,32.005455,32.683639,33.367013,34.055798,34.750226,35.450543,
36.157008,36.869898,37.589503,38.316134,39.050123,39.791819,40.541602,41.299873,42.067065,42.843643,43.630109,44.427004,
45.234915,46.054480,46.886394,47.731416,48.590378,49.464198,50.353889,51.260575,52.185511,53.130102,54.095931,55.084794,
56.098738,57.140120,58.211669,59.316583,60.458639,61.642363,62.873247,64.158067,65.505352,66.926082,68.434815,70.051556,
71.805128,73.739795,75.930132,78.521659,81.890386,90.000000,
};





//==========================================
//�������BCarVoltageGet()
//���ã��Ƕȡ����ٶȲ������ǶȲ���
//==========================================
void CarVoltageGet(void) 
{

      
	  int32s_t lnDeltaValue;
      //test = 1;
#if Filter_Method == 0  //////////////////////////                       //�������˲�

    lnDeltaValue = (int16s_t)CV_ACCE_VAL;
    lnDeltaValue = lnDeltaValue - (int16s_t)(CV_ACCE_Z_ZERO); 
    lnDeltaValue = (int32u_t)(lnDeltaValue*5000L/1024);                  //��õ�ѹֵ
    lnDeltaValue = lnDeltaValue * 10L / 56;                              //��� Z ����ٶ� 600mV/g
    if(lnDeltaValue> 100)    lnDeltaValue= 100;                          //������ֵ
    if(lnDeltaValue<-100)    lnDeltaValue=-100;  
    Angle_m = Asin_to_Angle[lnDeltaValue+100];                           //����Ƕ� 
    
    lnDeltaValue = (int16s_t)CV_GYRO_VAL;                                //��ȡ������ADֵ
    lnDeltaValue = (int16s_t)CV_GYRO_ZERO - lnDeltaValue;                //��ȥ��ƫ��ֵ
    lnDeltaValue = (int32u_t)(lnDeltaValue*5000L/1024);                  //��õ�ѹֵ 
    Gyro_m = lnDeltaValue * 10.0 / 67;                                   //����ǽ��ٶ�,��ԭʼ��·���Ѿ��Ŵ��� 10 ��
      
    Kalman_Filter( Angle_m, Gyro_m);                                     //�������˲�
    
    g_nCarAngle   = (int16s_t)( Angle * 10 );                             //��������Ƕ�
    g_nCarGyroVal = (int16s_t)( Angle_dot * 10);                         //����������ٶ�        
     
    // test = 0;

#else  /////////////////////////////////////////////                     //�����˲�
	 
	  lnDeltaValue = (int16s_t)CV_ACCE_VAL;                                //��ȡ���ٶȴ�����ADֵ
    lnDeltaValue = lnDeltaValue - (int16s_t)CV_ACCE_Z_ZERO;              //��ȥ��ƫ��ֵ	
	  g_nCarAcceVal = (int16s_t)(lnDeltaValue * CV_ACCE_RATIO_INT / 100);  //�Ƕȹ�һ��
	
	  lnDeltaValue = (int16s_t)CV_GYRO_VAL;                                //��ȡ������ADֵ
	  lnDeltaValue = lnDeltaValue - (int16s_t)CV_GYRO_ZERO;                //��ȥ��ƫ��ֵ	
	  g_nCarGyroVal = (int16s_t)(lnDeltaValue * CAR_GYRO_RATIO_INT / 100); //���ٶȹ�һ��
                                                              
	  g_nCarAngle = (int16s_t)(g_lnCarAngleSigma >> 5);                    //����Ƕȼ���
	  lnDeltaValue = g_nCarAcceVal - g_nCarAngle;                          //�Ƕ�У��
	  lnDeltaValue = (int32s_t)(lnDeltaValue * CAR_ACCE_RATIO_INT / 1000); //�Ƕȷ���
	  g_lnCarAngleSigma += (g_nCarGyroVal + lnDeltaValue);	               //���ٶȻ���
	  
#endif  ///////////////////////////////////////////



}

//==========================================
//�������BCarAngleControl()
//���ã�����Ƕȿ��ƣ��ڻ�
//==========================================
/*void CarAngleControl(void)
{
    int32s_t nLeft, nRight;
	  int32s_t nSpeed;
	  int32s_t nP, nD;
	    
	  nP = g_nCarAngle;                                //g_nCarAngle:-1000~1000	                     
    nP = (nP * CAR_AA_P_INT);              //�Ƕ�P����
    nD = g_nCarGyroVal;
    nD = (nD * CAR_AA_D_INT);              //�Ƕ�D����
    
    nSpeed = (nP + nD) / 1000;
    
	  if(nSpeed > MOTOR_SPEED_SET_MAX) 	
	  {
	    nSpeed = MOTOR_SPEED_SET_MAX;
	  }
	  else if(nSpeed < MOTOR_SPEED_SET_MIN)	
	  {
	    nSpeed = MOTOR_SPEED_SET_MIN;
	  }
	 
	  
	  nLeft  = nSpeed ;        //�Ƕȿ���
	  nRight = nSpeed ;        //�Ƕȿ���   

    g_nLeftMotorOut = (int16s_t)nLeft;
    g_nRightMotorOut = (int16s_t)nRight;
    
    Motor_Control();      
}*/ 
void CarAngleControl(void)
{
     
    
     int16s_t nLeft, nRight;
	  int32s_t nSpeed;
	  int32s_t nP, nD;
	   //test = 1;  
	  nP = g_nCarAngle;                                //g_nCarAngle:-1000~1000	                     
    nP = (nP * CAR_AA_P_INT);              //�Ƕ�P����
    nD = g_nCarGyroVal;
    nD = (nD * CAR_AA_D_INT);              //�Ƕ�D����
    
    nSpeed = (nP + nD) / 100;
    
	  if(nSpeed > MOTOR_SPEED_SET_MAX) 	
	  {
	    nSpeed = MOTOR_SPEED_SET_MAX;
	  }
	  else if(nSpeed < MOTOR_SPEED_SET_MIN)	
	  {
	    nSpeed = MOTOR_SPEED_SET_MIN;
	  }
	 
	  
	  nLeft  = (int16s_t)nSpeed - PI_Out;// +DirectionOut_L ;        //�Ƕȿ���
	  nRight = (int16s_t)nSpeed - PI_Out;// + DirectionOut_R ;        //�Ƕȿ���   

    g_nLeftMotorOut = nLeft;
    g_nRightMotorOut = nRight;
    
    //test = 0;
    
    Motor_Control(); 
    
         
}