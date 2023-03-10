/*
 * Prueba OSEK
 *
 * Miembros del equipo:
 *		Laura García
 * 		Tahirí Ramos
 *
 * 07/02/2023
 *
 */
#include "OSEK.h"
#include "LED_RGB.h"
#include "PUSH_BUTTONS.h"
#include "NVIC.h"
#include "GPIO.h"

#define MODE1 0x00000100;
Task_struct_t task_list[3];

int main (void)
{
	//TASK A
	task_list[0].priority = 0;
	task_list[0].schedule = FULL;
	task_list[0].autostart = TRUE;
	task_list[0].state = SUSPENDED;
	task_list[0].ptr_funct = task_A;

	//TASK B
	task_list[1].priority = 1;
	task_list[1].schedule = FULL;
	task_list[1].autostart = FALSE;
	task_list[1].state = SUSPENDED;
	task_list[1].ptr_funct = task_B;


	//TASK C
	task_list[2].priority = 2;
	task_list[2].schedule = FULL;
	task_list[2].autostart = FALSE;
	task_list[2].state = SUSPENDED;
	task_list[2].ptr_funct = task_C;

	NVIC_set_basepri_threshold(PRIORITY_10);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_4);

	init_RGB();
	gpio_init();
	os_init();
	while (1);
}

