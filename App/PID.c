
#include "common.h"
#include "include.h"
#include "PID.h"
#include "math.h"

float Kp1;
float Kd1=0.049;
float Kp2= 0.0961;//0.37 ;//0.34
float Ki2= 0.051;//0.078 ;//0.075;
float Kd2=0.015;

extern uint8 stopcar_flag;

int32 PID1(float e,float kp,float ki,float kd)
{
	
	static float e_s1=0,sum1=0;//e_s1用于保存上一次的误差值，用于计算微分项。Sum1用于计算累加和，计算积分项。
	float r;
	sum1+=e;//计算积分累加和
        if(stopcar_flag==0)
        {
            e_s1=0;sum1=0;
        }
	r=kp*e+ki*sum1+kd*(e-e_s1);//从左至右分别是比例项、积分项、微分项
	e_s1=e;//保存这一次的误差值用于下一次微分计算

	return (int32)r;
}

int32 PID2(float e,float kp,float ki,float kd,float yuzhi)
{
        static float e_s2=0,sum2=0;//e_s用于保存上一次的误差值，用于计算微分项。Sum用于计算累加和，计算积分项。
	float r;
        unsigned char para; 
       	sum2+=e;//计算积分累加和           
        
        if(stopcar_flag==0)
        {
            e_s2=0;sum2=0;
        }
     
        para=1;
	r=kp*e+para*ki*sum2+kd*(e-e_s2);//从左至右分别是比例项、积分项、微分项
	e_s2=e;//保存这一次的误差值用于下一次微分计算


	return (int32)r;
}
