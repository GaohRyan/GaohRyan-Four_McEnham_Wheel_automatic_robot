/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外KL26 平台主程序
 * @author     山外科技
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
 *  @brief      main函数
 *  @since      v5.0
 *  @note       山外 LPTMR 脉冲计数实验，需要短接 PTC5 和 PTE30
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
    enable_irq(PORTC_PORTD_IRQn);  //使能干簧管中断
    while(1)
    {
     Song_Send_UserData1();//电感最大、小值
     Song_Send_UserData2();//电感实际值和相对值
     Song_Send_UserData3();//偏移距离和电机速度
     Song_Send_UserData4();//各闭环参数
     Song_Send_UserData5();
    }
}