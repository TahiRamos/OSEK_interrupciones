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

int main (void)
{
	gpio_init();
	os_init();
	while (1);
}

