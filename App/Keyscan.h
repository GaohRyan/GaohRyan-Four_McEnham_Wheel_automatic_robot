#ifndef _KEYSCAN_H_
#define _KEYSCAN_H_


void KeySet_Scan(void);

#define   KEY1			(gpio_get(PTB3))			//按键1
#define   KEY2			(gpio_get(PTB2))			//按键2
#define   KEY3			(gpio_get(PTB7))			//按键3
#define   KEY4			(gpio_get(PTB8))			//按键4

#define   KEY5			(gpio_get(PTB17))			//拨码开关1
#define   KEY6			(gpio_get(PTB18))			//拨码开关2
#define   KEY7			(gpio_get(PTB16))			//拨码开关3
#define   KEY8			(gpio_get(PTB10))			//拨码开关4

#endif