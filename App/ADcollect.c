#include "common.h"
#include "include.h"
#include "ADcollect.h"


#define FILTER_N 20
float ADresult[5] = {0};
float ADmax[5] = {0};
float ADmin[5] = {3.3,3.3,3.3,3.3,3.3};
float ADrelative[5] = {0};

/*************************** AD1��λֵƽ���˲�***********************************/
int Filter1(void) {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = adc_once(ADC0_SE6a, ADC_8bit);
    
  }
  // ����ֵ��С�������У�ð�ݷ���
  for(j = 0; j < FILTER_N - 1; j++) {
    for(i = 0; i < FILTER_N - 1 - j; i++) {
      if(filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  // ȥ�������С��ֵ����ƽ�� 
  for(i = 2; i < FILTER_N - 2; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 4);
}


/*************************** AD2��λֵƽ���˲�***********************************/
int Filter2(void) {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = adc_once(ADC0_SE2 , ADC_8bit);
    
  }
  // ����ֵ��С�������У�ð�ݷ���
  for(j = 0; j < FILTER_N - 1; j++) {
    for(i = 0; i < FILTER_N - 1 - j; i++) {
      if(filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  // ȥ�������С��ֵ����ƽ��
  for(i = 1; i < FILTER_N - 1; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 2);
}

/*************************** AD3��λֵƽ���˲�***********************************/
int Filter3(void) {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = adc_once(ADC0_SE0 , ADC_8bit);
    
  }
  // ����ֵ��С�������У�ð�ݷ���
  for(j = 0; j < FILTER_N - 1; j++) {
    for(i = 0; i < FILTER_N - 1 - j; i++) {
      if(filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  // ȥ�������С��ֵ����ƽ��
  for(i = 1; i < FILTER_N - 1; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 2);
}

/*************************** AD4��λֵƽ���˲�***********************************/
int Filter4(void) {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = adc_once(ADC0_SE4a, ADC_8bit);
    
  }
  // ����ֵ��С�������У�ð�ݷ���
  for(j = 0; j < FILTER_N - 1; j++) {
    for(i = 0; i < FILTER_N - 1 - j; i++) {
      if(filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  // ȥ�������С��ֵ����ƽ��
  for(i = 1; i < FILTER_N - 1; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 2);
}

/*************************** AD5��λֵƽ���˲�***********************************/
int Filter5(void) {
  int i, j;
  int filter_temp, filter_sum = 0;
  int filter_buf[FILTER_N];
  for(i = 0; i < FILTER_N; i++) {
    filter_buf[i] = adc_once(ADC0_SE5a , ADC_8bit);
    
  }
  // ����ֵ��С�������У�ð�ݷ���
  for(j = 0; j < FILTER_N - 1; j++) {
    for(i = 0; i < FILTER_N - 1 - j; i++) {
      if(filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  // ȥ�������С��ֵ����ƽ��
  for(i = 1; i < FILTER_N - 1; i++) filter_sum += filter_buf[i];
  return filter_sum / (FILTER_N - 2);
}

/***************************** AD�źŲɼ� *************************************/
void ADget(void)
{
  ADresult[0] = (float)Filter1()/255*3.3;
  ADresult[1] = (float)Filter2()/255*3.3;
  ADresult[2] = (float)Filter3()/255*3.3;
  ADresult[3] = (float)Filter4()/255*3.3;
  ADresult[4] = (float)Filter5()/255*3.3;

}
/***************************** ��ø�·AD�����ֵ����Сֵ ******************/
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

/***************************** ��ø�·AD�����ֵ ******************/
void ADgetrelative(void)
{
  int i;
  ADget();
  for(i=0;i<5;i++)
  {
    
     ADrelative[i]=(ADresult[i]-ADmin[i])/(ADmax[i]-ADmin[i])*100;
      
  }
       
}
//ע���ڶ�ʱ���ж��У���������������������������ʱ�жϣ���������ֵ��������ʷֵ������ֵ��Ϊ�ж�
//���磬10ms�ɼ�һ   �δ�����ֵ��20ms����һ�Σ�����ÿ������ʱ���������鴫������ֵ����ʷֵ������ֵ
//�����������������ֵ������Ȼ����м������궨,�ټ�����ˮƽ��в�Ȼ��������ж���û�д���