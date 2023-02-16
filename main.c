/*
 * Practica OSEC con Interrupciones
 *
 * Diseñar e implementar los siguientes servicios de OSEK, llamados desde una interrupción
 * activate_task(task_id)
 * terminate_task()
 * chain_task (task_id)
 *
 * Miembros del equipo:
 *		Laura García
 * 		Tahirí Ramos
 *
 * 13/02/2023
 *
 */

#include "OSEK.h"
#include "LED_RGB.h"

int main (void)
{
	init_RGB();
	os_init();
	while (1)
	{

	}
	return 0 ;
}
