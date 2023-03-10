 /*
 * OSEK.c
 *
 *  Created on: 3 feb 2023
 *      Author: Tahirí & Laura
 *
 */

#include "OSEK.h"
#include "LED_RGB.h"
#include "fsl_gpio.h"
#include "GPIO.h"

extern Task_struct_t task_list[3];
static uint8_t g_interrupt_count;

void os_init()
{
    //validación de autostart
	task_list[1].state = SUSPENDED;
	activate_task(0);
}

/*
 *  The specified task is transferred from the suspended state
 *  into the ready state
 */
void activate_task(uint8_t task_ID)
{
    task_list[task_ID].state = READY;    // 3:wait    2:running    1:ready    0:suspend

    scheduler(); //barrido de tareas
}


/*
 * After termination of the calling task an other task is
 * activated sequentially
 */
void chained_task(uint8_t task_ID)
{
	for(uint8_t i= 0; i <TOTAL_TASKS; i++)
		{
			if(task_list[i].state == RUNNING)
			{
				task_list[i].state = SUSPENDED;
			}
		}
	activate_task(task_ID);
}


/*
 * The calling task is transferred from the running state into
 * the suspended state
 */
void terminate_task(void)
{
	for(uint8_t i= 0; i <TOTAL_TASKS; i++)
	{
		if(task_list[i].state == RUNNING)
		{
			task_list[i].state = SUSPENDED;
			scheduler();
		}
	}
}

/*
 * Using this service the task explicitly yields control to a
 * higher-priority ready task (if any exists)
 */


void scheduler()
{
	//guardar contexto
	for(int8_t i = TOTAL_PRIORITY; i>=0 ; i--)
	{
		for(int8_t j = 0; j<TOTAL_TASKS ; j++)
		{
			if((task_list[j].state == READY)&&(task_list[j].priority == i))
			{
				task_list[j].state = RUNNING;
				//restaurar contexto
				task_list[j].ptr_funct();
				break;
			}
		}
	}
}



void delay(uint32_t delay)
{
    volatile uint32_t j;
    for(j = delay; j > 0; j--)
    {
        __asm("nop");
    }
}


//TASKs
void task_A (void)
{
	set_color(GREEN);
	delay(2000000);
	GPIO_callback_init(GPIO_A, tasks);
	set_color(GREEN);
	delay(2000000);
	GPIO_callback_init(GPIO_A, tasks);
}

void task_B (void)
{
	set_color(RED);
	delay(2000000);
	GPIO_callback_init(GPIO_A, tasks);
}

void task_C (void)
{
	set_color(BLUE);
	delay(2000000);
	GPIO_callback_init(GPIO_A, tasks);
}

void tasks(void)
{
	if(1 == g_interrupt_count)
	{
		activate_task(task_B_ID);
		g_interrupt_count++;
	}
	else if(2 == g_interrupt_count)
	{
		chained_task(task_C_ID);
		g_interrupt_count++;
	}
	else if(3 == g_interrupt_count)
	{
		terminate_task();
		g_interrupt_count++;
	}
	else if(4 == g_interrupt_count)
	{
		terminate_task();
		g_interrupt_count = 0;
	}
}

