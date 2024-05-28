/*
 * software_timer.h
 *
 *  Created on: May 28, 2024
 *      Author: NguyenTienLuan
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_


extern int timer1_flag;
extern int timer2_flag;
extern int timer3_flag;
extern int timer4_flag;
extern int timer5_flag;
extern int timer6_flag;
extern int timer7_flag;
extern int timer8_flag;

void setTimer1(int duration);
void timer1Run();
void setTimer2(int duration);
void timer2Run();
void setTimer3(int duration);
void timer3Run();
void setTimer4(int duration);
void timer4Run();
void setTimer5(int duration);
void timer5Run();
void setTimer6(int duration);
void timer6Run();
void setTimer7(int duration);
void timer7Run();
void setTimer8(int duration);
void timer8Run();



#endif /* INC_SOFTWARE_TIMER_H_ */
