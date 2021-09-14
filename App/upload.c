
#include "common.h"
#include "include.h"
#include "upload.h"
#include "roadrecog.h"

extern float ADresult[8];
extern float ADmax[8];
extern float ADmin[8];
extern float ADrelative[8];

extern float Kp1;
extern float Kd1;
extern float Kp2;
extern float Ki2;
extern float Kd2;
extern float threshold;

extern float aa;   
extern float bb;
extern float cc;
extern float dist_max; 
extern float dist_max_circle;

extern s32 real_speed;
extern s32 set_speed;
extern s32 speedmin;
extern s32 pwmtestL;

extern u32 kong;
extern float dist;


extern s32 pp;
extern s32 bang;

extern float delta_center;
extern float delta_side;
extern s32   circle_flag;
extern float ADadd1;            //左边电感之和
extern float ADadd2;


#define BYTE0(dwTemp)       ( *( (char *)(&dwTemp)) )
#define BYTE1(dwTemp)       ( *( (char *)(&dwTemp) + 1) )
#define BYTE2(dwTemp)       ( *( (char *)(&dwTemp) + 2) )
#define BYTE3(dwTemp)       ( *( (char *)(&dwTemp) + 3) )
unsigned char data_to_send[150];



 void Song_Send_UserData(float x)
{
    unsigned char _cnt=0;
    float _temp;
    unsigned char sum = 0;
    unsigned char i;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xF1;
    data_to_send[_cnt++]=0;

    _temp = x;

    data_to_send[_cnt++]=BYTE3(_temp);
    data_to_send[_cnt++]=BYTE2(_temp);
    data_to_send[_cnt++]=BYTE1(_temp);
    data_to_send[_cnt++]=BYTE0(_temp);

    data_to_send[3] = _cnt-4;


    for(i=0;i<_cnt;i++)
        sum += data_to_send[i];
    data_to_send[_cnt++]=sum;

    uart_putbuff(UART1,data_to_send, _cnt);

}

/*************发送第一帧数据：5个电感的最大值和最小值*****************/
void Song_Send_UserData1(void)
{
    unsigned char _cnt=0;
    
    unsigned char sum = 0;
    unsigned char i;
    unsigned char j;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xF1;
    data_to_send[_cnt++]=0;

   
    for(j=0;j<5;j++)
    {
      
      data_to_send[_cnt++]=BYTE3(ADmax[j]);//五个电感的最大值
      data_to_send[_cnt++]=BYTE2(ADmax[j]);
      data_to_send[_cnt++]=BYTE1(ADmax[j]);
      data_to_send[_cnt++]=BYTE0(ADmax[j]);
    }
   
   
         for(j=0;j<5;j++)
    {
      
      data_to_send[_cnt++]=BYTE3(ADmin[j]);//五个电感的最小值
      data_to_send[_cnt++]=BYTE2(ADmin[j]);
      data_to_send[_cnt++]=BYTE1(ADmin[j]);
      data_to_send[_cnt++]=BYTE0(ADmin[j]);
    }
    
    
    data_to_send[3] = _cnt-4;
    for(i=0;i<_cnt;i++)
        sum += data_to_send[i];
    data_to_send[_cnt++]=sum;

    uart_putbuff(UART1,data_to_send, _cnt);

}

/***************发送第二帧数据：5个电感的实际值和相对值************************/
void Song_Send_UserData2(void)
{
    unsigned char _cnt=0;
    
    unsigned char sum = 0;
    unsigned char i;
    unsigned char j;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xF2;
    data_to_send[_cnt++]=0;

    
    for(j=0;j<5;j++)
    {
      
      data_to_send[_cnt++]=BYTE3(ADresult[j]);//五个电感的实际值
      data_to_send[_cnt++]=BYTE2(ADresult[j]);
      data_to_send[_cnt++]=BYTE1(ADresult[j]);
      data_to_send[_cnt++]=BYTE0(ADresult[j]);
    }
   

    for(j=0;j<5;j++)
    {
      
      data_to_send[_cnt++]=BYTE3(ADrelative[j]);//五个电感的相对值
      data_to_send[_cnt++]=BYTE2(ADrelative[j]);
      data_to_send[_cnt++]=BYTE1(ADrelative[j]);
      data_to_send[_cnt++]=BYTE0(ADrelative[j]);
    }

   
    data_to_send[3] = _cnt-4;
    for(i=0;i<_cnt;i++)
        sum += data_to_send[i];
    data_to_send[_cnt++]=sum;

    uart_putbuff(UART1,data_to_send, _cnt);

}

/***************发送第三帧数据：偏移距离、测到的电机速度、控制舵机打角的占空比************************/
void Song_Send_UserData3(void)
{
    unsigned char _cnt=0;
    
    unsigned char sum = 0;
    unsigned char i;
    float temp;
    temp=(float)kong;
    
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xF3;
    data_to_send[_cnt++]=0;

 
  // 1  
      data_to_send[_cnt++]=BYTE3(dist);  //偏移距离  11
      data_to_send[_cnt++]=BYTE2(dist);
      data_to_send[_cnt++]=BYTE1(dist);
      data_to_send[_cnt++]=BYTE0(dist);
      
      
   // 2   
      data_to_send[_cnt++]=BYTE3(real_speed);//电机的实测转速  22
      data_to_send[_cnt++]=BYTE2(real_speed);
      data_to_send[_cnt++]=BYTE1(real_speed);
      data_to_send[_cnt++]=BYTE0(real_speed);
      
      
   // 3   
      data_to_send[_cnt++]=BYTE3(set_speed);//电机的设定转速  33
      data_to_send[_cnt++]=BYTE2(set_speed);
      data_to_send[_cnt++]=BYTE1(set_speed);
      data_to_send[_cnt++]=BYTE0(set_speed);
      
  //4    
      data_to_send[_cnt++]=BYTE3(pwmtestL);//电机滤波后的转速
      data_to_send[_cnt++]=BYTE2(pwmtestL);
      data_to_send[_cnt++]=BYTE1(pwmtestL);
      data_to_send[_cnt++]=BYTE0(pwmtestL);
      
      
    // 5  
      data_to_send[_cnt++]=BYTE3(temp);   //控制舵机的PWM占空比  44
      data_to_send[_cnt++]=BYTE2(temp);
      data_to_send[_cnt++]=BYTE1(temp);
      data_to_send[_cnt++]=BYTE0(temp);
   
      
    // 6 
      data_to_send[_cnt++]=BYTE3(speedmin);//电机的最大转速   55
      data_to_send[_cnt++]=BYTE2(speedmin);
      data_to_send[_cnt++]=BYTE1(speedmin);
      data_to_send[_cnt++]=BYTE0(speedmin);
      
      
    // 7 
      data_to_send[_cnt++]=BYTE3(dist_max_circle);  //圆环的最大偏移距离    66
      data_to_send[_cnt++]=BYTE2(dist_max_circle);
      data_to_send[_cnt++]=BYTE1(dist_max_circle);
      data_to_send[_cnt++]=BYTE0(dist_max_circle);
      
      
   // 8  
      data_to_send[_cnt++]=BYTE3(bang);  //bang_bang control    77
      data_to_send[_cnt++]=BYTE2(bang);
      data_to_send[_cnt++]=BYTE1(bang);
      data_to_send[_cnt++]=BYTE0(bang);
    
      
    data_to_send[3] = _cnt-4;
    for(i=0;i<_cnt;i++)
        sum += data_to_send[i];
    data_to_send[_cnt++]=sum;

    uart_putbuff(UART1,data_to_send, _cnt);

}


/***************发送第四帧数据：各闭环参数************************/
void Song_Send_UserData4(void)
{
    unsigned char _cnt=0;
    
    unsigned char sum = 0;
    unsigned char i;
    float temp1;
    temp1=aa*10;

    
  
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xF4;
    data_to_send[_cnt++]=0;

    
  // 1
      data_to_send[_cnt++]=BYTE3(Kp1);
      data_to_send[_cnt++]=BYTE2(Kp1);
      data_to_send[_cnt++]=BYTE1(Kp1);
      data_to_send[_cnt++]=BYTE0(Kp1);
    
  // 2    
      data_to_send[_cnt++]=BYTE3(temp1);    //aa*10
      data_to_send[_cnt++]=BYTE2(temp1);
      data_to_send[_cnt++]=BYTE1(temp1);
      data_to_send[_cnt++]=BYTE0(temp1);

  //3      
      data_to_send[_cnt++]=BYTE3(bb);
      data_to_send[_cnt++]=BYTE2(bb);
      data_to_send[_cnt++]=BYTE1(bb);
      data_to_send[_cnt++]=BYTE0(bb);
  
     
  // 4
      data_to_send[_cnt++]=BYTE3(cc);
      data_to_send[_cnt++]=BYTE2(cc);
      data_to_send[_cnt++]=BYTE1(cc);
      data_to_send[_cnt++]=BYTE0(cc);
    
      
   // 5   
      data_to_send[_cnt++]=BYTE3(Kd1);
      data_to_send[_cnt++]=BYTE2(Kd1);
      data_to_send[_cnt++]=BYTE1(Kd1);
      data_to_send[_cnt++]=BYTE0(Kd1);
      
    
  //6    
      data_to_send[_cnt++]=BYTE3(Kp2);
      data_to_send[_cnt++]=BYTE2(Kp2);
      data_to_send[_cnt++]=BYTE1(Kp2);
      data_to_send[_cnt++]=BYTE0(Kp2);
   
      
  //7    
      data_to_send[_cnt++]=BYTE3(Ki2);
      data_to_send[_cnt++]=BYTE2(Ki2);
      data_to_send[_cnt++]=BYTE1(Ki2);
      data_to_send[_cnt++]=BYTE0(Ki2);
    
      
   //8   
      data_to_send[_cnt++]=BYTE3(Kd2);
      data_to_send[_cnt++]=BYTE2(Kd2);
      data_to_send[_cnt++]=BYTE1(Kd2);
      data_to_send[_cnt++]=BYTE0(Kd2);
      
      
   
    data_to_send[3] = _cnt-4;
    for(i=0;i<_cnt;i++)
        sum += data_to_send[i];
    data_to_send[_cnt++]=sum;

    uart_putbuff(UART1,data_to_send, _cnt);

}


/***************发送第五帧数据：各闭环参数************************/
void Song_Send_UserData5(void)
{
    unsigned char _cnt=0;
    
    unsigned char sum = 0;
    unsigned char i;
    
    
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xAA;
    data_to_send[_cnt++]=0xF5;
    data_to_send[_cnt++]=0;

  //1
      data_to_send[_cnt++]=BYTE3(threshold);
      data_to_send[_cnt++]=BYTE2(threshold);
      data_to_send[_cnt++]=BYTE1(threshold);
      data_to_send[_cnt++]=BYTE0(threshold);
      
      
   //2   
      data_to_send[_cnt++]=BYTE3(dist_max);
      data_to_send[_cnt++]=BYTE2(dist_max);
      data_to_send[_cnt++]=BYTE1(dist_max);
      data_to_send[_cnt++]=BYTE0(dist_max);
     
      
    //3  
      data_to_send[_cnt++]=BYTE3(pp);
      data_to_send[_cnt++]=BYTE2(pp);
      data_to_send[_cnt++]=BYTE1(pp);
      data_to_send[_cnt++]=BYTE0(pp);
     
      
   //4   
      data_to_send[_cnt++]=BYTE3(delta_center);
      data_to_send[_cnt++]=BYTE2(delta_center);
      data_to_send[_cnt++]=BYTE1(delta_center);
      data_to_send[_cnt++]=BYTE0(delta_center);
      
      
     //5         
      data_to_send[_cnt++]=BYTE3(delta_side);
      data_to_send[_cnt++]=BYTE2(delta_side);
      data_to_send[_cnt++]=BYTE1(delta_side);
      data_to_send[_cnt++]=BYTE0(delta_side);
      
       
     //6 
      data_to_send[_cnt++]=BYTE3(circle_flag);
      data_to_send[_cnt++]=BYTE2(circle_flag);
      data_to_send[_cnt++]=BYTE1(circle_flag);
      data_to_send[_cnt++]=BYTE0(circle_flag);
      
      
    //7    左边之和
      data_to_send[_cnt++]=BYTE3(ADadd1);
      data_to_send[_cnt++]=BYTE2(ADadd1);
      data_to_send[_cnt++]=BYTE1(ADadd1);
      data_to_send[_cnt++]=BYTE0(ADadd1);
 
      
    //8
      data_to_send[_cnt++]=BYTE3(ADadd2);
      data_to_send[_cnt++]=BYTE2(ADadd2);
      data_to_send[_cnt++]=BYTE1(ADadd2);
      data_to_send[_cnt++]=BYTE0(ADadd2);
      

    data_to_send[3] = _cnt-4;
    for(i=0;i<_cnt;i++)
        sum += data_to_send[i];
    data_to_send[_cnt++]=sum;

    uart_putbuff(UART1,data_to_send, _cnt);

}