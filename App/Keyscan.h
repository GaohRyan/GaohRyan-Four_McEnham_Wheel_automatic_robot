#ifndef _KEYSCAN_H_
#define _KEYSCAN_H_


void KeySet_Scan(void);

#define   KEY1			(gpio_get(PTB3))			//����1
#define   KEY2			(gpio_get(PTB2))			//����2
#define   KEY3			(gpio_get(PTB7))			//����3
#define   KEY4			(gpio_get(PTB8))			//����4

#define   KEY5			(gpio_get(PTB17))			//���뿪��1
#define   KEY6			(gpio_get(PTB18))			//���뿪��2
#define   KEY7			(gpio_get(PTB16))			//���뿪��3
#define   KEY8			(gpio_get(PTB10))			//���뿪��4

#endif