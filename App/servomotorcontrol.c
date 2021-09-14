#include "servomotorcontrol.h"
#include "include.h"
#include "roadrecog.h"
#include "ADcollect.h"
#include "PID.h"



s32 kongmax=55250;      //  �� max:    56200       8000  now:  7050
s32 kongmin=41150;     //   �� min:    39850       8350 

s32 circle_kongmax=55900;  //���������     7700
s32 circle_kongmin=40500;

extern float Kp1;
extern float Kd1;
extern float ADrelative[5];
extern s32 set_speed;
extern s32 circle_flag;

int32 kong=48200;        
float aa= 1.45;                  ////////1.35;                     //��̬Pֵ���κ���������ϵ��
float bb,cc=260;                //345;                  //��̬Pֵ���κ���һ����ϵ���ͳ�����

float dist_max=22;           //��������ƫ�������ֵ��ƫ�������ֵ�������KP1�����Ƕ����ƫռ�ձ���������С��ֵ����ô���������ƫ������Сʱ����ƫ��С�����У�
float dist_max_circle=20;    //Բ�������ƫ�ƾ���
float ADadd1=0;              //��ߵ��֮��
float ADadd2=0;              //�Ҳ���֮��


void servomotor_control(float distance)
{
   
   int32 duty;
   static int32 pre_duty;
   static int32 circle_pre_duty;
   

   ADadd1=(ADrelative[0]+ADrelative[1]);
   ADadd2=(ADrelative[3]+ADrelative[4]);

   if(circle_flag==0)
   {
      bb=(kongmax-kong)/dist_max/dist_max-dist_max*aa-cc/dist_max;
      Kp1=aa*distance*distance+bb*distance+cc;
   }
   else if(circle_flag!=0)
   {
      bb=(circle_kongmax-kong)/dist_max_circle/dist_max_circle;
      Kp1=distance*bb;                           
   }
   
   
   if((ADrelative[0]+ADrelative[1]+ADrelative[3]+ADrelative[4])<30.0)//��ƫ�ƾ���ܴ�ʱ�������жϷ��������ˮƽ���ֵ��Ϊ�㣬�޷��жϷ������ϴε�
     duty=pre_duty;
   else
   {
     
     if(ADadd1>=ADadd2)
           duty=kong+PID1(distance,Kp1,0,0);
       if(ADadd1<ADadd2)
           duty=kong-PID1(distance,Kp1,0,0);
     if(circle_flag==0)
     {
         
       if(duty<kongmin)
         duty=kongmin;
       else if(duty>kongmax)
         duty=kongmax;
     }
     
      else
     { 
          if(duty>circle_kongmax)
            duty=circle_kongmax;
          else if(duty<circle_kongmin)
            duty=circle_kongmin;
     }         
   }  
   pre_duty=duty; 
   
   tpm_pwm_duty(TPM1,TPM_CH0,duty);
}
   
 /**********�˺�����������������ռ�ձȹ�ϵ���õ������������Сռ�ձ�*********/
void servmotor_degree_zhan(unsigned long int duty)
{
  tpm_pwm_duty(TPM1, TPM_CH0, duty);
}