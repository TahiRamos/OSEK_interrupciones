/*
 * OSEK.h
 *
 *  Created on: 3 feb 2023
 *      Author: Tahirí Ramos & Laura
 */

#ifndef OSEK_H_
#define OSEK_H_

#include "stdint.h"

#define task_A_ID    0
#define task_B_ID    1
#define task_C_ID    2

#define TOTAL_TASKS 3
#define TOTAL_PRIORITY 5

typedef enum{
	NON,
	FULL
}schedule_t;	// non preemtive, full preemtive

typedef enum{
    FALSE,
	TRUE
}boolean_t;		//for autostart

typedef enum{
	READY,
	WAITING,
	SUSPENDED,
	RUNNING
}state_t;

typedef struct
{
	void (*ptr_funct)(void);
    uint8_t priority;
    schedule_t schedule;
	boolean_t autostart;
	uint8_t activation;
	state_t state;
}Task_struct_t;


void os_init();
void activate_task(uint8_t);
void chained_task(uint8_t);
void terminate_task(void);
void scheduler();

void delay(uint32_t);
void task_A (void);
void task_B (void);
void task_C (void);
void tasks(void);

#endif /* OSEK_H_ */
