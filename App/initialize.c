#include "common.h"
#include "include.h"
#include "initialize.h"
//#include "servomotorcontrol.h"
//#include "motorcontrol.h"
#include    "MKL_it.h"
extern uint32 kong;

#define INT_COUNT  0xFFFF                                       //LPTMR 产生中断的计数次数


/********************************** 初始化 ************************************/
void Init(void)
{
    DisableInterrupts;                           	//禁止总中断
    
	//set_irq_priority (PORTA_IRQn,  0);     //干簧管A17
        set_irq_priority (PORTC_PORTD_IRQn,  0);     //干簧管D7
	set_irq_priority (PIT_IRQn ,  1);
        set_irq_priority (UART1_IRQn ,  2);
        
        tpm_pwm_init(TPM0, TPM_CH0,12000, 10000);  //电机四路驱动脉冲E24、25、29、30
        tpm_pwm_init(TPM0, TPM_CH1,12000, 10000);
        tpm_pwm_init(TPM0, TPM_CH2,12000, 10000);
        tpm_pwm_init(TPM0, TPM_CH3,12000, 10000);
        
        
        
	lptmr_pulse_init(LPT0_ALT2,INT_COUNT, LPT_Rising);          //PTC5,右路电机测速，初始化脉冲计数器，用LPT0_ALT2，即PTC5输入，每隔INT_COUNT产生中断（需要开中断才能产生中断），上升沿触发		
        tpm_pulse_init(TPM2,TPM_CLKIN1,TPM_PS_1);     //左路电机测速，PTC13,TPM_PS_1为1分频计数
        
	         	
	tpm_pwm_init(TPM1, TPM_CH0,300, kong);                   //PTA12 ，初始化舵机控制脉冲，频率300，10000为满占空比
        
        
	gpio_init(PTB2 , GPI, 1);		//按键KEY，PTB2、3、7、8
	gpio_init(PTB3, GPI, 1);
	gpio_init(PTB7, GPI, 1);
	gpio_init(PTB8, GPI, 1);
	
        
        gpio_init(PTB17, GPI, 1);              //初始化拨码开关接口为输入
        gpio_init(PTB18, GPI, 1);
        gpio_init(PTB16, GPI, 1);
        gpio_init(PTB10, GPI, 1);
        
	
        adc_init(ADC0_SE1);			// PTE16
	adc_init(ADC0_SE5a);		// PTE17
	adc_init(ADC0_SE2);			// PTE18
	adc_init(ADC0_SE6a);		// PTE19
	adc_init(ADC0_SE0);			// PTE20
	adc_init(ADC0_SE4a);		// PTE21
	adc_init(ADC0_SE3 );		// PTE22
	adc_init(ADC0_SE7a);		// PTE23  	      	
        
        
        //LCD_Oled_Init();              //液晶初始化

        gpio_init (PTB9, GPO,0);   //PTB9，
        
        gpio_init (PTB11, GPO,0);
        port_init (PTD7,ALT1| IRQ_FALLING| PULLUP );      //置干簧管接口为下降沿触发中断 内置上拉电阻
        set_vector_handler(PORTC_PORTD_VECTORn,PORTD_IRQHandler);
        //port_init_NoALT (PTA17, IRQ_FALLING); //设置干簧管接口为下降沿触发中断
        
        uart_init (UART1, 115200);
        
        
   EnableInterrupts; //开总中断   
    
}