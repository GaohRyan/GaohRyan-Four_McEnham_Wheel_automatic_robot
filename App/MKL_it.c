/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       MK60_it.c
 * @brief      山外K60 平台中断服务函数
 * @author     山外科技
 * @version    v5.0
 * @date       2013-06-26
 */

#include    "MKL_it.h"


#include "common.h"
#include "include.h"
#include "ADcollect.h"
#include "servomotorcontrol.h"
#include "motorcontrol.h"
#include "roadrecog.h"
#include "Keyscan.h"
#include "PID.h"
#include "Keyscan.h"

#define deltapid   0.001        //pid上位机调试的精度
#define SERVO_TEST 0             //舵机打角的调试开关，置0为关闭

float dist;
uint8 stopcar_flag=0;
uint8 pre_stopcar_flag=0;

extern float Kp1;
extern float Kd1;
extern float Kp2;
extern float Ki2;
extern float Kd2;
extern float aa;   
extern float bb;
extern float cc;

extern float dist_max;
extern float dist_max_circle;
extern u32 kong;
extern s32 set_speed;
extern s32 pre_set_speed;
extern s32 set_speed_flag;
extern float threshold;
extern s32 pwmtestL;

extern float dist;


extern s32 pp;
extern s32 bang;
s32 circle_flag=0;
//unsigned char startspeed_flag=0;
s32 IT=0;   //外部中断标志位
s32 IT_number= 0;  //触发次数计时 
s32 IT_stop = 0;
int stopcar_count=0;

void PIT0_IRQHandler(void)
{
 
     static char i = 0;
     static int j = 0;
     static int IT_delay = 0;
     NVIC_DisableIRQ( PIT_IRQn );
       //  gpio_turn (PTB9);//用来测试舵机控制周期  ///舵机周期1ms

     ADgetrelative();
     dist=Common_Road_recognite();
   
     
     
#if(SERVO_TEST==1)//开启调试舵机模式
    servmotor_degree_zhan(kong);
#elif(SERVO_TEST==0)
    servomotor_control(dist);
#endif
    
 /*****************延时发车3s************************/   
         if(stopcar_count<3000&&IT_stop==0)
     {
      stopcar_count++;
      
      stopcar_flag=0;
     }
     else if(stopcar_count>=3000&&IT_stop==0)
     {
       stopcar_count = 3000;
        stopcar_flag=1;
     }
 /******干簧管触发了 处理函数************/
     if(IT==1)   
     {
          if(IT_number>=1)   //过了起点后 经过终点 属于第二次触发
          {
           // if(j<2)
            if(j<10)
            {
              j++;
            }
            else if(!gpio_get(PTD7))
            {
               j= 0;
               stopcar_flag = 0;  //经过终点，停车
               IT_stop = 1;
               IT_number=2;
            }
          }
          
          if(IT_delay<1000)  //延迟
          {
            IT_delay++;
          }
          else if(IT_delay>=1000)
          {
             IT_delay = 0;             //清除延时计数
             if(j==0)
             {
               IT_number++;               //触发计数
             }
             IT = 0;                    //触发标志位置零
          }
      }
      if(pwmtestL==0&&IT_number==2)   //已停车 清零
          {
            IT_number = 0;
            IT = 0;
          }
     if(IT_number>=3)
       IT_number = 0 ;

     gpio_set (PTB11,!IT); 
 /**************************************/ 

     if(stopcar_flag==0)
     { 

       motor_speed();
 //     motor_speed_zhan(0);
      motor_control_stop();
      PID2(0,0,0,0,0);
      PID1(0,0,0,0);
     }
     
      
     if(stopcar_flag==1)
     {
       i++;
      
       if(i==10)    //电机控制周期10ms
       {
          
              motor_speed();
              motor_control1(dist);
    //       motor_control2();
      //     motor_control_cs(set_speed);
   //         motor_control(dist);
 //           gpio_turn (PTB9);//用来测试舵机控制周期
              i = 0;
        }
      
     }
     
     //motor_control(dist);
	

     PIT_Flag_Clear(PIT0);       //清中断标志位
    
     NVIC_EnableIRQ( PIT_IRQn );
}

void PORTD_IRQHandler()         //干簧管中断服务函数 端口PTD7
{
       uint32 m= 7 ;
 //      static uint32 number=0;
       
       if(PORTD_ISFR & (1 << m))           //PTE12触发中断
	{
          IT = 1; // 干簧管触发状态
 //         number++;
//          pp = number;
        
		// 以上为用户任务  
	   PORTD_ISFR  |= (1 << m);        //写1清中断标志位
	}

}



 /*********************************************************************************************
  *
  *    
  *此函数用来串口接收到上位机指令，更改相应参数值
  *
  *********************************************************************************************/
void USART1_IRQHandler()
{
   uint8 ch;
   uart_rx_irq_dis(UART1);
   uart_getchar (UART1,&ch);              //接收到一个数据
   
   if(ch==0xFF)
   {
     stopcar_flag=1;    
     pre_stopcar_flag = stopcar_flag;
  //   startspeed_flag=1;
   }
   if(ch==0xEE)
     stopcar_flag=0;

   
   if(ch==0xA0)
     aa=aa+deltapid;
   if(ch==0xA1)
     aa=aa-deltapid;
   
   if(ch==0xF2)
     cc=cc+0.5;
   if(ch==0xF3)
     cc=cc-0.5;
   
   if(ch==0xF4)
     dist_max=dist_max+1;
   if(ch==0xF5)
     dist_max=dist_max-1;
   
   if(ch==0xF6)
     dist_max_circle=dist_max_circle+1;
   if(ch==0xF7)
     dist_max_circle=dist_max_circle-1; 
   
   if(ch==0xB0)
     Kd1=Kd1+0.001;
   if(ch==0xB1)
     Kd1=Kd1-0.001;
   
   if(ch==0xC0)
     Kp2=Kp2+deltapid;
   if(ch==0xC1)
     Kp2=Kp2-deltapid;
   
   if(ch==0xD0)
     Ki2=Ki2+0.001;
   if(ch==0xD1)
     Ki2=Ki2-0.001;
   
   if(ch==0xD2)
     Kd2=Kd2+0.001;
   if(ch==0xD3)
     Kd2=Kd2-0.001;
   
   if(ch==0xD4)
     threshold=threshold+1;
   if(ch==0xD5)
     threshold=threshold-1;
   
   if(ch==0xE0)
     kong=kong+50;
   if(ch==0xE1)
     kong=kong-50;
  
   
   if(ch==0x65)
     pp=pp+1;
   if(ch==0x66)
     pp=pp-1;
   
   if(ch==0xAA)
     set_speed=set_speed+1;
   if(ch==0xBB)
     set_speed=set_speed-1;
  ////////////////////////////////////////
   if(ch==0x77)
   {
     if(pre_set_speed>set_speed)
     {
        set_speed_flag = 0;//减速状态
     }
     else 
     {
        set_speed_flag = 1;//加速状态
     }
     set_speed=300;
     pre_set_speed = set_speed;
   }
   if(ch==0x78)
   {
     if(pre_set_speed>set_speed)
     {
        set_speed_flag = 0;//减速状态
     }
     else 
     {
        set_speed_flag = 1;//加速状态
     }
     set_speed=200;
     pre_set_speed = set_speed;
   }
  ////////////////////////////////////////// 
   if(ch==0xb0)
     bang = bang+10;
   if(ch==0xb1)
     bang = bang-10;

   
   
   uart_rx_irq_en(UART1);
}





//PA口中断函数，没法删除。。
void PORTA_IRQHandler()
{

}

