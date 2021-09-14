
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
	
	static float e_s1=0,sum1=0;//e_s1���ڱ�����һ�ε����ֵ�����ڼ���΢���Sum1���ڼ����ۼӺͣ���������
	float r;
	sum1+=e;//��������ۼӺ�
        if(stopcar_flag==0)
        {
            e_s1=0;sum1=0;
        }
	r=kp*e+ki*sum1+kd*(e-e_s1);//�������ҷֱ��Ǳ���������΢����
	e_s1=e;//������һ�ε����ֵ������һ��΢�ּ���

	return (int32)r;
}

int32 PID2(float e,float kp,float ki,float kd,float yuzhi)
{
        static float e_s2=0,sum2=0;//e_s���ڱ�����һ�ε����ֵ�����ڼ���΢���Sum���ڼ����ۼӺͣ���������
	float r;
        unsigned char para; 
       	sum2+=e;//��������ۼӺ�           
        
        if(stopcar_flag==0)
        {
            e_s2=0;sum2=0;
        }
     
        para=1;
	r=kp*e+para*ki*sum2+kd*(e-e_s2);//�������ҷֱ��Ǳ���������΢����
	e_s2=e;//������һ�ε����ֵ������һ��΢�ּ���


	return (int32)r;
}
