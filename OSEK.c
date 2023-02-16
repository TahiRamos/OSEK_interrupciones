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

Task_struct_t task_list[3];

void os_init()
{
	Task_struct_t aux;

	//TASK A
	task_list[0].PRIORITY = 0;
	task_list[0].SCHEDULE = FULL;
	task_list[0].AUTOSTART = TRUE;
	task_list[0].ACTIVATION = 1;
	task_list[0].ptr_funct = task_A;

	//TASK B
	task_list[1].PRIORITY = 1;
	task_list[1].SCHEDULE = FULL;
	task_list[1].AUTOSTART = FALSE;
	task_list[1].ACTIVATION = 1;
	task_list[1].ptr_funct = task_B;

	//TASK C
	task_list[2].PRIORITY = 2;
	task_list[2].SCHEDULE = FULL;
	task_list[2].AUTOSTART = FALSE;
	task_list[2].ACTIVATION = 0;
	task_list[2].ptr_funct = task_C;


	for(int i = 0; i<3; i++)
	{
		if(TRUE == task_list[i].AUTOSTART) //validar autostart
		{
			for(int i = 0; i<3; i++)
			{
				for(int j = i+1; j<4; j++)
				{
					if(task_list[j].PRIORITY < task_list[i].PRIORITY)
					{
						aux=task_list[j];
						task_list[j] = task_list[i];
						task_list[i] = aux;
					}
					else{}
				}
			}
		}
		else
		{
			for(int k=0; k<3; k++)
			{
				for(int l=k+1; l<4; l++)
				{
					if(task_list[l].PRIORITY<task_list[k].PRIORITY)
					{
						aux=task_list[l];
						task_list[l]=task_list[k];
						task_list[k]=aux;
					}
				}
			}
		}
	}
	task_list[0].ptr_funct();

}

/*
 *  The specified task is transferred from the suspended state
 *  into the ready state
 */
void activate_task(uint8_t task_ID)
{
    task_list[task_ID].ACTIVATION = 1;    // 3:wait    2:running    1:ready    0:suspend

    scheduler(); //barrido de tareas
}

/*
 * After termination of the calling task an other task is
 * activated sequentially
 */
void chained_task(uint8_t task_ID)
{
	terminate_task(task_ID);
    activate_task(task_ID);
    scheduler();
}

/*
 * The calling task is transferred from the running state into
 * the suspended state
 */
void terminate_task(uint8_t task_ID)
{
    task_list[task_ID].ACTIVATION = 0;    // 3:wait    2:running    1:ready    0:suspend

    scheduler(); //barrido de tareas
}

/*
 * Using this service the task explicitly yields control to a
 * higher-priority ready task (if any exists)
 */
void scheduler()
{
	for(int i = 0; i<2; i++)
	{
		if((task_list[i+1].PRIORITY < task_list[i].PRIORITY)&&(task_list[i].ACTIVATION == 1)) //1: ready, and high priority
		{
			//task_list[i].ptr_funct();
		}
		else{}
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
	activate_task (task_B_ID);
	set_color(RED);
	delay(2000000);
	task_B();
}

void task_B (void)
{
	chained_task (task_C_ID);
	set_color(BLUE);
	delay(2000000);
	task_C();
}

void task_C (void)
{
	terminate_task (task_C_ID);
	set_color(GREEN);
	delay(2000000);
}


