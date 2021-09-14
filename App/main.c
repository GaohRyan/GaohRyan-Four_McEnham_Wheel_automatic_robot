/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��KL26 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.2
 * @date       2014-10-26
 */

#include "common.h"
#include "include.h"
#include "math.h"
#include "initialize.h"
#include "Keyscan.h"
#include "ADcollect.h"
#include "upload.h"
/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� LPTMR �������ʵ�飬��Ҫ�̽� PTC5 �� PTE30
 */
void  main(void)
{
    Init(); 
    KeySet_Scan();
   // LCD_CLS();    
  //  LCD_P8x16Str(0,0,"ADCollected");
    pit_init_ms(PIT0, 1); 
    NVIC_EnableIRQ( PIT_IRQn );
    uart_rx_irq_en(UART1);
    enable_irq(PORTC_PORTD_IRQn);  //ʹ�ܸɻɹ��ж�
    while(1)
    {
     Song_Send_UserData1();//������Сֵ
     Song_Send_UserData2();//���ʵ��ֵ�����ֵ
     Song_Send_UserData3();//ƫ�ƾ���͵���ٶ�
     Song_Send_UserData4();//���ջ�����
     Song_Send_UserData5();
    }
}