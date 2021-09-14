/*******************************按键 *****************************************/
#include "common.h"
#include "include.h"
#include "Keyscan.h"
#include "ADcollect.h"
#include "servomotorcontrol.h"
#include "roadrecog.h"

extern uint8 stopcar_flag;

extern float Kp1;
extern float Kd1;
extern float Kp2;
extern float Ki2;
  
extern  float aa;
extern  float cc;
  
extern  s32 kongmax;
extern  s32 kongmin;

extern  s32 circle_speed;  
extern  s32 circle_kongmax;
extern  s32 circle_kongmin;
  
extern  float dist_max;           
extern float dist_max_circle;

extern s32 set_speed1;
extern s32 set_speed2;
extern s32 set_speed3;
extern s32 set_speed4;
extern s32 circle_speed;

void SpeedMode(void);



typedef struct SPEED
{
  
   //圆环内速度
  s32 circle_speed;
  
  float aa;
  float cc;
  
  s32 kongmax;
  s32 kongmin;
  
  s32 circle_kongmax;
  s32 circle_kongmin;
  
  float dist_max;           
  float dist_max_circle;
  
  //分段速度
   s32 set_speed1; //     if(distance<=7)
   s32 set_speed2; //     else if(distance>7&&distance<=12)
   s32 set_speed3; //    else if(distance>12&&distance<=18)
   s32 set_speed4; //     else if(distance>18)
   
  

}SPEED_LEVEL;


//未赋值



//第三速度
    SPEED_LEVEL speed_level1={
    .circle_speed= 260 ,

    .aa=      1.57   ,
    .cc=       285  ,
    
    .kongmax =   55550 ,
    .kongmin =   40850,
    
    .circle_kongmax= 56200 ,
    .circle_kongmin= 40200 ,
    
    .dist_max=     22     ,     
    .dist_max_circle= 20  ,
   //速度分段
    . set_speed1=    360     ,
    . set_speed2=    320  , 
    . set_speed3=    310   ,
    .set_speed4=     290  
      
    };
  

    //第二速度 
    SPEED_LEVEL speed_level2={
     .circle_speed= 260 ,
     
    .aa= 1.615,        
    .cc= 290,      
    
    .kongmax=  55550  ,
    .kongmin=  40850  ,
    
    .circle_kongmax=  56200,
    .circle_kongmin=  40200,
    
    .dist_max=    22    ,     
    .dist_max_circle=  20 ,
  
    //速度分段       
    . set_speed1=  350    ,
   . set_speed2=   310    , 
   . set_speed3=   310    ,
   .set_speed4=    280
    };
 

//第一速度
  SPEED_LEVEL speed_level3={
   .circle_speed=  240 ,

    
    .aa=     1.45     ,
    .cc=     260    ,
    
    .kongmax=   55250 ,
    .kongmin=   41150 ,
    
    .circle_kongmax= 55900 ,
    .circle_kongmin= 40500,
    
    .dist_max=   22     ,     
    .dist_max_circle= 20,
       
    . set_speed1=  320   ,
    . set_speed2=  290    , 
    . set_speed3=  280    ,
    .set_speed4=   250
 };





void KeySet_Scan(void)
{
   while(KEY8==0)
  {
    ADgetmaxmin();      
  }

  while(KEY8==1&&KEY7==1&&KEY6==1&&KEY5==1)
  {
          ADgetrelative();
          servomotor_control(Common_Road_recognite());
  }  
  SpeedMode();
}


///函数作用：按键检测中的速度模式选择
///无入口参数，无返回值

void SpeedMode(void)
{
          
      if(KEY5==0)//第一等速度
      {
        circle_speed   =  speed_level3.circle_speed;
      
        aa=speed_level3.aa;
        cc= speed_level3.cc;
      
        kongmax=speed_level3.kongmax;
        kongmin= speed_level3.kongmin;
      
        circle_kongmax=speed_level3.circle_kongmax;
        circle_kongmin=speed_level3.circle_kongmin;
      
        dist_max = speed_level3.dist_max;           
        dist_max_circle=speed_level3.dist_max_circle;
        
        set_speed1=speed_level3.set_speed1;
        set_speed2=speed_level3.set_speed2;
        set_speed3=speed_level3.set_speed3;
        set_speed4=speed_level3.set_speed4;
        

      }
  
      else if(KEY6==0)//第二等速度
      {

        circle_speed   =  speed_level2.circle_speed;
      
        aa         = speed_level2.aa;
        cc         = speed_level2.cc;
      
        kongmax    = speed_level2.kongmax;
        kongmin    = speed_level2.kongmin;
      
        circle_kongmax  = speed_level2.circle_kongmax;
        circle_kongmin  = speed_level2.circle_kongmin;
      
        dist_max        = speed_level2.dist_max;           
        dist_max_circle =speed_level2.dist_max_circle;
        
        
        set_speed1=speed_level2.set_speed1;
        set_speed2=speed_level2.set_speed2;
        set_speed3=speed_level2.set_speed3;
        set_speed4=speed_level2.set_speed4;
        

      }
      
      
        
     else if(KEY7==0)//第三等速度
      {
        circle_speed   =  speed_level1.circle_speed;
      
        aa          =  speed_level1.aa;
        cc          = speed_level1.cc;
      
        kongmax     =  speed_level1.kongmax;
        kongmin     = speed_level1.kongmin;
      
        circle_kongmax  = speed_level1.circle_kongmax;
        circle_kongmin  = speed_level1.circle_kongmin;
      
        dist_max        = speed_level1.dist_max;           
        dist_max_circle = speed_level1.dist_max_circle;
        
        set_speed1=speed_level1.set_speed1;
        set_speed2=speed_level1.set_speed2;
        set_speed3=speed_level1.set_speed3;
        set_speed4=speed_level1.set_speed4;

      }



}