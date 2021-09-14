#include "common.h"
#include "roadrecog.h"
#include "ADcollect.h"
#include "math.h"

extern uint8 stopcar_flag;
extern s32 circle_flag;
extern float dist_max;
extern float dist_max_circle;
extern float ADrelative[8];

float delta_center=0.0;
float delta_side=0.0;

char temp2 = 0;


/**********圆环路*******************/
void circle_recognite(void)
{
  static float temp=100;

  float distance=0;
  
  
  
  delta_side=abs(ADrelative[4]+ADrelative[3]-ADrelative[0]-ADrelative[1])/2;
  delta_center=abs(temp-ADrelative[2]);
  
  
  if(ADrelative[2]>25&&ADrelative[2]<50&&delta_side<15)
  {
     
      if(ADrelative[0]<=30&&ADrelative[4]<=30&&ADrelative[0]>=5&&ADrelative[4]>=5)
      {
        circle_flag=1;
        temp=ADrelative[2];

       return;
      }
  }
  
  //圆环标志位清零
  
    if(ADrelative[2]>60&&circle_flag!=0)
    {
       temp2 = 1;
    }
    if((ADrelative[1]>70||ADrelative[3]>70)&&circle_flag!=0)
    { 
      circle_flag=0;
      temp2 = 0;
  
    }
    temp=ADrelative[2];
    
}


/*****************  路径检测   ***************************/

float Common_Road_recognite(void)
{
 

 
  float x1;
  float distance;
  
  circle_recognite(); //圆环单独识别
  gpio_set(PTB9,!circle_flag);

  
  if(circle_flag==1)   //进入圆环 第3路电感值相对值X2
  {
      
      if(temp2==1)
      {  
          ADrelative[2]+=5;
      }
      
      
      x1=2*ADrelative[2];
         if(x1>100) x1=100;
      distance=(-0.00006075)*x1*x1*x1+0.01111*x1*x1-0.85*x1+35.07;
      if(distance<2)
          distance=0;
      if(distance>dist_max_circle)
          distance=dist_max_circle;
  }
  
  else        //未进入圆环
  {
      x1=ADrelative[2];
      distance=(-0.00006075)*x1*x1*x1+0.01111*x1*x1-0.85*x1+35.07;
      if(distance<2)
        distance=0;
      if(distance>dist_max)
         distance=dist_max;

  }
  
  return distance;
}
