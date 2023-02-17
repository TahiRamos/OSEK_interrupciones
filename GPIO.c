/*
 * GPIO.c
 *
 *  Created on: 12 sep 2022
 *      Author: Tahirí Ramos
 */

#include "GPIO.h"
#include "bits.h"
#include "fsl_clock.h"

#include "fsl_gpio.h"
#include "fsl_port.h"


/*
 * 	Initialize GPIO for the periferics used in this project
 */

static void (*gpio_C_callback)(uint32_t flags) = 0;
static void (*gpio_A_callback)(uint32_t flags) = 0;

void GPIO_callback_init(gpio_name_t gpio, void (*handler)(uint32_t flags))
{
	if(GPIO_A == gpio)
	{
		gpio_A_callback = handler;
	}
	else
	{
		gpio_C_callback = handler;
	}

}

void PORTC_IRQHandler(void) //sw2
{

	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOC);

	if(gpio_C_callback)
	{
		gpio_C_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOC, irq_status); //Red


}

void PORTA_IRQHandler(void) //sw2
{

	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOA);

	if(gpio_A_callback)
	{
		gpio_A_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOA, irq_status); //Red


}

void gpio_init(void)
{
	gpio_pin_config_t gpio_input_config = {
				        kGPIO_DigitalInput,
				        0,
				    };

		gpio_pin_config_t gpio_output_config = {
				        kGPIO_DigitalOutput,
				        1,
				    };

		const port_pin_config_t button_config = {
				kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
				kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
				kPORT_PassiveFilterEnable,                              /* Passive filter is disabled */
				kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
				kPORT_HighDriveStrength,                                 /* High drive strength is configured */
				kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
				kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
			  };


		CLOCK_EnableClock(kCLOCK_PortA);
		CLOCK_EnableClock(kCLOCK_PortB);
		CLOCK_EnableClock(kCLOCK_PortC);
		CLOCK_EnableClock(kCLOCK_PortE);

		//Initialize SW2
		GPIO_PinInit(GPIOD, bit_11, &gpio_input_config);
		PORT_SetPinConfig(PORTD, bit_11, &button_config);
		PORT_SetPinInterruptConfig(PORTD, bit_11, kPORT_InterruptFallingEdge);

		//Initialize SW3
		GPIO_PinInit(GPIOA, bit_10, &gpio_input_config);
		PORT_SetPinConfig(PORTA, bit_10, &button_config);
		PORT_SetPinInterruptConfig(PORTA, bit_10, kPORT_InterruptFallingEdge);

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
