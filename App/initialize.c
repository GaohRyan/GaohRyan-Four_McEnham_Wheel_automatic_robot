#include "common.h"
#include "include.h"
#include "initialize.h"
//#include "servomotorcontrol.h"
//#include "motorcontrol.h"
#include    "MKL_it.h"
extern uint32 kong;

#define INT_COUNT  0xFFFF                                       //LPTMR �����жϵļ�������


/********************************** ��ʼ�� ************************************/
void Init(void)
{
    DisableInterrupts;                           	//��ֹ���ж�
    
	//set_irq_priority (PORTA_IRQn,  0);     //�ɻɹ�A17
        set_irq_priority (PORTC_PORTD_IRQn,  0);     //�ɻɹ�D7
	set_irq_priority (PIT_IRQn ,  1);
        set_irq_priority (UART1_IRQn ,  2);
        
        tpm_pwm_init(TPM0, TPM_CH0,12000, 10000);  //�����·��������E24��25��29��30
        tpm_pwm_init(TPM0, TPM_CH1,12000, 10000);
        tpm_pwm_init(TPM0, TPM_CH2,12000, 10000);
        tpm_pwm_init(TPM0, TPM_CH3,12000, 10000);
        
        
        
	lptmr_pulse_init(LPT0_ALT2,INT_COUNT, LPT_Rising);          //PTC5,��·������٣���ʼ���������������LPT0_ALT2����PTC5���룬ÿ��INT_COUNT�����жϣ���Ҫ���жϲ��ܲ����жϣ��������ش���		
        tpm_pulse_init(TPM2,TPM_CLKIN1,TPM_PS_1);     //��·������٣�PTC13,TPM_PS_1Ϊ1��Ƶ����
        
	         	
	tpm_pwm_init(TPM1, TPM_CH0,300, kong);                   //PTA12 ����ʼ������������壬Ƶ��300��10000Ϊ��ռ�ձ�
        
        
	gpio_init(PTB2 , GPI, 1);		//����KEY��PTB2��3��7��8
	gpio_init(PTB3, GPI, 1);
	gpio_init(PTB7, GPI, 1);
	gpio_init(PTB8, GPI, 1);
	
        
        gpio_init(PTB17, GPI, 1);              //��ʼ�����뿪�ؽӿ�Ϊ����
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
        
        
        //LCD_Oled_Init();              //Һ����ʼ��

        gpio_init (PTB9, GPO,0);   //PTB9��
        
        gpio_init (PTB11, GPO,0);
        port_init (PTD7,ALT1| IRQ_FALLING| PULLUP );      //�øɻɹܽӿ�Ϊ�½��ش����ж� ������������
        set_vector_handler(PORTC_PORTD_VECTORn,PORTD_IRQHandler);
        //port_init_NoALT (PTA17, IRQ_FALLING); //���øɻɹܽӿ�Ϊ�½��ش����ж�
        
        uart_init (UART1, 115200);
        
        
   EnableInterrupts; //�����ж�   
    
}