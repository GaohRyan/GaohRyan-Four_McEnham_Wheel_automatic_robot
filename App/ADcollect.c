#include "common.h"
#include "include.h"
#include "ADcollect.h"


#define FILTER_N 20
float ADresult[5] = {0};
float ADmax[5] = {0};
float ADmin[5] = {3.3,3.3,3.3,3.3,3.3};
float ADrelative[5] = {0};

/*************************** AD1中位值平均滤波***********************************/
int Filter1(void) {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = adc_once(ADC0_SE6a, ADC_8bit);
    
  }
  // 采样值从小到大排列（冒泡法）
  for(j = 0; j < FILTER_N - 1; j++) {
    for(i = 0; i < FILTER_N - 1 - j; i++) {
      if(filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  // 去除最大最小极值后求平均 
  for(i = 2; i < FILTER_N - 2; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 4);
}


/*************************** AD2中位值平均滤波***********************************/
int Filter2(void) {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = adc_once(ADC0_SE2 , ADC_8bit);
    
  }
  // 采样值从小到大排列（冒泡法）
  for(j = 0; j < FILTER_N - 1; j++) {
    for(i = 0; i < FILTER_N - 1 - j; i++) {
      if(filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  // 去除最大最小极值后求平均
  for(i = 1; i < FILTER_N - 1; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 2);
}

/*************************** AD3中位值平均滤波***********************************/
int Filter3(void) {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = adc_once(ADC0_SE0 , ADC_8bit);
    
  }
  // 采样值从小到大排列（冒泡法）
  for(j = 0; j < FILTER_N - 1; j++) {
    for(i = 0; i < FILTER_N - 1 - j; i++) {
      if(filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  // 去除最大最小极值后求平均
  for(i = 1; i < FILTER_N - 1; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 2);
}

/*************************** AD4中位值平均滤波***********************************/
int Filter4(void) {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = adc_once(ADC0_SE4a, ADC_8bit);
    
  }
  // 采样值从小到大排列（冒泡法）
  for(j = 0; j < FILTER_N - 1; j++) {
    for(i = 0; i < FILTER_N - 1 - j; i++) {
      if(filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  // 去除最大最小极值后求平均
  for(i = 1; i < FILTER_N - 1; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 2);
}

/*************************** AD5中位值平均滤波***********************************/
int Filter5(void) {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = adc_once(ADC0_SE5a , ADC_8bit);
    
  }
  // 采样值从小到大排列（冒泡法）
  for(j = 0; j < FILTER_N - 1; j++) {
    for(i = 0; i < FILTER_N - 1 - j; i++) {
      if(filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  // 去除最大最小极值后求平均
  for(i = 1; i < FILTER_N - 1; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 2);
}

/***************************** AD信号采集 *************************************/
void ADget(void)
{
  ADresult[0] = (float)Filter1()/255*3.3;
  ADresult[1] = (float)Filter2()/255*3.3;
  ADresult[2] = (float)Filter3()/255*3.3;
  ADresult[3] = (float)Filter4()/255*3.3;
  ADresult[4] = (float)Filter5()/255*3.3;

}
/***************************** 获得各路AD的最大值和最小值 ******************/
void ADgetmaxmin(void)
{
  int i;
  ADget();
  for(i=0;i<5;i++)
  {
    if(ADresult[i]>ADmax[i])
      ADmax[i]=ADresult[i];
    if(ADresult[i]<ADmin[i])
      ADmin[i]=ADresult[i];
  }
       
}

/***************************** 获得各路AD的相对值 ******************/
void ADgetrelative(void)
{
  int i;
  ADget();
  for(i=0;i<5;i++)
  {
    
     ADrelative[i]=(ADresult[i]-ADmin[i])/(ADmax[i]-ADmin[i])*100;
      
  }
       
}
//注意在定时器中断中，设置数组来保存两个或三个定时中断，传感器的值，即用历史值和现在值做为判断
//例如，10ms采集一   次传感器值，20ms控制一次，这样每当控制时，就有两组传感器的值，历史值和现在值
//初步打算用两个八字电感做差比积，中间电感做标定,再加两个水平电感差比积，用来判断有没有串道