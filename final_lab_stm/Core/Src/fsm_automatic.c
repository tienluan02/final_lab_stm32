/*
 * fsm_automatic.c
 *
 *  Created on: May 6, 2024
 *      Author: Administrator
 */

#include "fsm_automatic.h"
#include "led.h"
#include "software_timer.h"
#include "button.h"
#include "main.h"

#define LONG_PRESS_INTERVAL 3000 // 3 second
#define IDLE_TIMEOUT 2000 // 10 seconds

void fsm_automatic() {
	switch (status) {
	case INIT:
		status = START;
		setTimer1(100); // for display update
		setTimer2(100); // for LED toggling
		setTimer4(IDLE_TIMEOUT); // initialize idle timer
		break;
	case START:
		if (timer1_flag == 1) {
			display7SEG(count);
			setTimer1(100);
			timer1_flag = 0; // Reset the flag
		}
		if (timer2_flag == 1) {
			HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			setTimer2(100);
			timer2_flag = 0; // Reset the flag
		}
		if (timer3_flag == 1) {
			if (isButton2LongPressed()) {
				if (count < 9) {
					count++;
				} else {
					count = 0;
				}
				setTimer3(LONG_PRESS_INTERVAL);
			}
			if (isButton3LongPressed()) {
				if (count > 0) {
					count--;
				} else {
					count = 9;
				}
				setTimer3(LONG_PRESS_INTERVAL);
			}
			timer3_flag = 0; // Reset the flag
		}
		if (timer4_flag == 1) {
			if (count > 0) {
				count--;
				setTimer1(1000); // Count down each second
			}
			setTimer4(IDLE_TIMEOUT); // Reset idle timer after each decrement
			timer4_flag = 0; // Reset the flag
		}
		break;
	default:
		break;
	}
}

void fsm_simple_buttons_run() {
//	precount = count;

	if (isButton1Pressed() == 1) {
		count = 0;
		setTimer3(1000);
	}

	if (isButton2Pressed() == 1) { // increase time in count but not update in count
		if (count <= 9) {
			count = count + 1;
		}
		if (count == 10) {
			count = 0;
		}
		setTimer3(1000);
	}

	if (isButton3Pressed() == 1) { // set increase time
		if (count >= 0) {
			count = count - 1;
		}
		if (count < 0) {
			count = 9;
		}
		setTimer3(1000);
	}

	if (timer3_flag == 1) {
		if (timer4_flag == 1) {
			count--;
			setTimer4(100);
		}
	}
}

void fsm_button() {
	// Button 1: Reset
	if (isButton1Pressed() == 1) {
		count = 0;
		setTimer4(IDLE_TIMEOUT); // Reset idle timer
	}

	// Button 2: Increase
	if (isButton2Pressed() == 1) {
		if (count < 9) {
			count++;
		} else {
			count = 0;
		}
		setTimer4(IDLE_TIMEOUT); // Reset idle timer
	} else if (isButton2LongPressed()) {
		setTimer3(LONG_PRESS_INTERVAL); // Start long press timer
		setTimer4(IDLE_TIMEOUT); // Reset idle timer
	}

	// Button 3: Decrease
	if (isButton3Pressed() == 1) {
		if (count > 0) {
			count--;
		} else {
			count = 9;
		}
		setTimer4(IDLE_TIMEOUT); // Reset idle timer
	} else if (isButton3LongPressed()) {
		setTimer3(LONG_PRESS_INTERVAL); // Start long press timer
		setTimer4(IDLE_TIMEOUT); // Reset idle timer
	}
}

