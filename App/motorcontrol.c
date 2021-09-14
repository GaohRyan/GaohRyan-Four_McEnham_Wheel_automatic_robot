#include "motorcontrol.h"
#include "include.h"
#include "roadrecog.h"
#include "ADcollect.h"
#include "PID.h"


extern float Kp2;
extern float Ki2;
extern float Kd2;

s32 pwmtestL=0;
float para_speed=0.47;
s32 real_speed;
s32 set_speed=280;
s32 set_speed_flag = 1;
s32 pre_set_speed=0; 

float threshold=30;

s32 pp= 118;           //195;       // V=  290  260  240
s32 speedmin=270;

s32 speedmax =275;
s32 bang = 1500;     //3000


 s32 set_speed1=320;
 s32 set_speed2=290;
 s32 set_speed3=280;
 s32 set_speed4=250;
 s32 circle_speed=240;

extern s32 circle_flag;
extern uint8 stopcar_flag;
extern uint8 pre_stopcar_flag;


/***********������ٺ���***********************/
void motor_speed(void)  //ע����øú���ʱ����Ҫ���������е���KalmanFilterInit()���Կ������˲���ʼ����ӦΪ�ú����е����˿������˲�
{
   static s32 pre_pwmtestL=240;
   
   real_speed= tpm_pulse_get(TPM2);
   tpm_pulse_clean (TPM2); //�����
   pwmtestL=real_speed;
   pwmtestL=para_speed*pwmtestL+(1-para_speed)*pre_pwmtestL;//һ�׻����˲�
   pre_pwmtestL=pwmtestL;
   
   //�����ٵĲ��η��ֲ�ƽ�ȣ������ǻ�е���Ĳ��ã���ʹ���ĺã�����Ҳ���в�ƽ�ȣ���������ü��ϲ����˲�
   
}


/**********�˺�������������̶�ռ�ձȣ�������ٶ���ռ�ձȵĹ�ϵ*********/
void motor_speed_zhan(unsigned long int duty)
{
  tpm_pwm_duty(TPM0, TPM_CH2, 10000-duty);
}

/****************���� ���ת�ٱջ����ں���************/
void motor_control1(float distance)
{
   
   s32 duty;
   s32 temp=0;
   
   s32 real_distance;
   real_distance=(distance-14);
   real_distance*=real_distance;
   real_distance*=(distance-14); 
 
   if(circle_flag==1)
   { 
      set_speed = circle_speed;
   }  

   if(circle_flag==0)
   {
     if(pre_set_speed>set_speed)///��ֹ��ת�ƶ�ʱ����
     {
        set_speed_flag = 0;//����״̬
     }
     else 
     {
        set_speed_flag = 1;//����״̬
     }
     
     if(distance<=7)
     {
          set_speed=set_speed1; 
     }
     else if(distance>7&&distance<=12)
     {
          set_speed=set_speed2; 
     }
     else if(distance>12&&distance<=18)
     {
          set_speed=set_speed3; 
     }
     else if(distance>18)
     {
          set_speed=set_speed4; 
     }  
    // set_speed=(speedmax-distance*distance*distance*speedmax/(pp*1000)  );
    // set_speed=speedmin-5*real_distance*speedmin/(pp*1000);
     pre_set_speed = set_speed;
   }

   duty=PID2((set_speed-pwmtestL),Kp2,Ki2,Kd2,threshold);
   temp = abs(set_speed - pwmtestL);
   if (temp>5)
    {
       if(set_speed > pwmtestL)
       {
          duty=duty+bang;
       
       }
       else if(set_speed < pwmtestL)
       {
          duty=duty-bang;
       }
      
    }
    if(duty<0)
        duty=0;
      if(duty>10000)
        duty=10000;
      tpm_pwm_duty(TPM0, TPM_CH2, 10000-duty);
   
   return;
}



/****************�����תͣ���ջ�����***********/
void motor_control_stop(void)
{
   s32 duty;
  if(pwmtestL>10&&pre_stopcar_flag)
  {
   tpm_pwm_duty(TPM0, TPM_CH2, 10000);
   tpm_pwm_duty(TPM0, TPM_CH3, 10000-5000);
  }
  else
  {
   tpm_pwm_duty(TPM0, TPM_CH2, 10000);
   tpm_pwm_duty(TPM0, TPM_CH3, 10000);
   pre_stopcar_flag = 0;
  }
}