/*
 * scheduler.c
 *
 *  Created on: May 28, 2024
 *      Author: NguyenTienLuan
 */


#include "scheduler.h"

sTasks SCH_tasks_G[SCH_MAX_TASKS];

uint8_t current_index_task =0;

void SCH_Init(void){
	current_index_task= 0;

	unsigned int i;
	for(i = 0 ; i < SCH_MAX_TASKS; i++){
		SCH_Delete(i);
	}
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD){

	while(SCH_tasks_G[current_index_task].pTask != 0 && current_index_task < SCH_MAX_TASKS){
		current_index_task++;
	}

	if(current_index_task == SCH_MAX_TASKS){
		return;
	}

	if(current_index_task < SCH_MAX_TASKS){
		SCH_tasks_G[current_index_task].pTask = pFunction;
		SCH_tasks_G[current_index_task].Delay = DELAY;
		SCH_tasks_G[current_index_task].Period = PERIOD;
		SCH_tasks_G[current_index_task].RunMe = 0;

		SCH_tasks_G[current_index_task].TaskID = current_index_task;

		current_index_task++;
	}
}

void SCH_Update(void){
	for(int i = 0 ; i < current_index_task; i++ ){
		if(SCH_tasks_G[i].Delay > 0){
			SCH_tasks_G[i].Delay--;
		}else{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe +=1;
		}
	}
}

void SCH_Dispatch_Tasks(void){
	for(int i = 0 ; i < current_index_task; i++ ){
		if(SCH_tasks_G[i].RunMe > 0){
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();

			if(SCH_tasks_G[i].Period == 0){
				SCH_Delete(i);
			}
		}
	}

}

void SCH_Delete(uint32_t ID){
	if(SCH_tasks_G[ID].pTask ==0){
		return;
	}
	else{
		SCH_tasks_G[ID].pTask = 0x0000;
		SCH_tasks_G[ID].Delay = 0;
		SCH_tasks_G[ID].Period = 0;
		SCH_tasks_G[ID].RunMe = 0;
	}

}

