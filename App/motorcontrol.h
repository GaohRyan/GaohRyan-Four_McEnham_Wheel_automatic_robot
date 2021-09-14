#ifndef _MOTORCONTROL_H_
#define _MOTORCONTROL_H_

void motor_speed(void);
void motor_control(float distance);
void motor_speed_zhan(unsigned 	long int duty);
void motor_control1(float distance);
void motor_control_stop(void);
void motor_control_cs(unsigned int set_speedx);
void motor_control2(void);
#endif