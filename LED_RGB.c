/*
 * LED_RGB.c
 *
 * Created on: 3 feb 2023
 *      Author: Hegui Tahirí Ramos Ugalde
 */

#include "LED_RGB.h"
#include "bits.h"
#include "fsl_gpio.h"
#include "fsl_clock.h"
#include "fsl_port.h"

void init_RGB(void)
{
	gpio_pin_config_t gpio_output_config = {
				        kGPIO_DigitalOutput,
				        1,
				    };
	//habilita los clocks de los puertos A, C y E
	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortE);
	CLOCK_EnableClock(kCLOCK_PortC);

	//config led azul
	PORT_SetPinMux(PORTA, bit_11, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOA, bit_11, &gpio_output_config);

	//config led rojo
	PORT_SetPinMux(PORTC, bit_9, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOC, bit_9, &gpio_output_config);

	//config led verde
	PORT_SetPinMux(PORTE, bit_6, kPORT_MuxAsGpio);
	GPIO_PinInit(GPIOE, bit_6, &gpio_output_config);
}

void set_color(RGB_colors_t color)
{
	switch(color)
	{
		case RED:	 	// caso 0 = encender led en rojo
			GPIO_PortClear(GPIOC, BIT_RED);	// enciende rojo
			GPIO_PortSet(GPIOE, BIT_GREEN);	// apaga verde
			GPIO_PortSet(GPIOA, BIT_BLUE);	// apaga azul
		break;

		case YELLOW:	 // caso 1 = encender led en rojo
			GPIO_PortSet(GPIOC, BIT_RED);	// apaga rojo
			GPIO_PortSet(GPIOE, BIT_GREEN);	// apaga verde
			GPIO_PortSet(GPIOA, BIT_BLUE);	// apaga azul
			GPIO_PortClear(GPIOC, BIT_RED);		// enciende rojo
			GPIO_PortClear(GPIOE, BIT_GREEN);	// enciende verde
		break;

		case GREEN:		// caso 2 = encender led en verde
			GPIO_PortClear(GPIOE, BIT_GREEN);	// enciende verde
			GPIO_PortSet(GPIOC, BIT_RED);	// apaga rojo
			GPIO_PortSet(GPIOA, BIT_BLUE);	// apaga azul
		break;

		case CYAN:	 // caso 3 = encender led en rojo
			GPIO_PortSet(GPIOC, BIT_RED);	// apaga rojo
			GPIO_PortSet(GPIOE, BIT_GREEN);	// apaga verde
			GPIO_PortSet(GPIOA, BIT_BLUE);	// apaga azul
			GPIO_PortClear(GPIOE, BIT_GREEN);	// enciende verde
			GPIO_PortClear(GPIOA, BIT_BLUE);	// enciende rojo
		break;

		case BLUE:		// caso 4 = encender led en azul
			GPIO_PortClear(GPIOA, BIT_BLUE);	// enciende azul
			GPIO_PortSet(GPIOC,  BIT_RED);	// apaga rojo
			GPIO_PortSet(GPIOE, BIT_GREEN);	// apaga verde
		break;

		case MAGENTA:	 // caso 5 = encender led en rojo
			GPIO_PortSet(GPIOC, BIT_RED);	// apaga rojo
			GPIO_PortSet(GPIOE, BIT_GREEN);	// apaga verde
			GPIO_PortSet(GPIOA, BIT_BLUE);	// apaga azul
			GPIO_PortClear(GPIOA, BIT_BLUE);	// enciende azul
			GPIO_PortClear(GPIOC, BIT_RED);		// enciende rojo
		break;

		case WHITE:		// caso 6 = encender led en blanco (rojo, azul y verde)
			GPIO_PortToggle(GPIOC, BIT_RED);	//enciende rojo
			GPIO_PortToggle(GPIOA, BIT_BLUE);	//enciende azul
			GPIO_PortToggle(GPIOE, BIT_GREEN);	//enciende verde
		break;

		case NONE:
			GPIO_PortSet(GPIOE, BIT_GREEN);	// apaga verde
			GPIO_PortSet(GPIOC, BIT_RED);	// apaga rojo
			GPIO_PortSet(GPIOA, BIT_BLUE);	// apaga azul
		break;
		default: 		// No existe esa opción
		break;
	}
}
