#include "servomotorcontrol.h"
#include "include.h"
#include "roadrecog.h"
#include "ADcollect.h"
#include "PID.h"



s32 kongmax=55250;      //  左 max:    56200       8000  now:  7050
s32 kongmin=41150;     //   右 min:    39850       8350 

s32 circle_kongmax=55900;  //环内最大打角     7700
s32 circle_kongmin=40500;

extern float Kp1;
extern float Kd1;
extern float ADrelative[5];
extern s32 set_speed;
extern s32 circle_flag;

int32 kong=48200;        
float aa= 1.45;                  ////////1.35;                     //动态P值二次函数二次项系数
float bb,cc=260;                //345;                  //动态P值二次函数一次项系数和常数项

float dist_max=22;           //用来设置偏移量最大值，偏移量最大值乘以最大KP1，就是舵机满偏占空比增量。调小该值，那么舵机可以在偏移量较小时就满偏，小车内切！
float dist_max_circle=20;    //圆环内最大偏移距离
float ADadd1=0;              //左边电感之和
float ADadd2=0;              //右侧电感之和


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
   
   
   if((ADrelative[0]+ADrelative[1]+ADrelative[3]+ADrelative[4])<30.0)//当偏移距离很大时，用来判断方向的两个水平电感值变为零，无法判断方向，用上次的
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
   
 /**********此函数用来调舵机打角与占空比关系，得到舵机打角最大最小占空比*********/
void servmotor_degree_zhan(unsigned long int duty)
{
  tpm_pwm_duty(TPM1, TPM_CH0, duty);
}