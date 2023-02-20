/*
 * LED_RGB.h
 *
 *Created on: 3 feb 2023
 *      Author: Hegui Tahirí Ramos Ugalde
 */

#ifndef RAMOS_UGALDE_T4_LED_RGB_H_
#define RAMOS_UGALDE_T4_LED_RGB_H_

#include "stdint.h"

#define SIM_5 (*((volatile uint32_t *)0x40048038))

#define PCR_PTA11 (*((volatile uint32_t *)0x4004902C))
#define PCR_PTC09 (*((volatile uint32_t *)0x4004B024))
#define PCR_PTE06 (*((volatile uint32_t *)0x4004D018))

#define GPIO_A_PDOR (*((volatile uint32_t *)0x400FF000))
#define GPIO_A_PDDR (*((volatile uint32_t *)0x400FF014))

#define GPIO_C_PDOR (*((volatile uint32_t *)0x400FF080))
#define GPIO_C_PDDR (*((volatile uint32_t *)0x400FF094))

#define GPIO_E_PDOR (*((volatile uint32_t *)0x400FF100))
#define GPIO_E_PDDR (*((volatile uint32_t *)0x400FF114))

typedef enum
{
	RED,
	YELLOW,		//0
	GREEN,      //1
	CYAN,		//2
	BLUE,		//3
	MAGENTA,	//4
	WHITE,		//5
	NONE,		//6
}RGB_colors_t;

void init_RGB(void);

//Enciende los leds para el color que queremos segun el caso
void set_color(RGB_colors_t);


#endif /* RAMOS_UGALDE_T4_LED_RGB_H_ */
