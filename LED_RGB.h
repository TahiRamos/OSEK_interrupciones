/*
 * LED_RGB.h
 *
 *Created on: 3 feb 2023
 *      Author: Hegui Tahirí Ramos Ugalde
 */

#ifndef RAMOS_UGALDE_T4_LED_RGB_H_
#define RAMOS_UGALDE_T4_LED_RGB_H_

#include "stdint.h"

#define BIT_BLUE  	1<<11
#define BIT_RED	  	1<<9
#define BIT_GREEN	1<<6

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

//Enciende los leds para el color que queremos segun el caso

void init_RGB(void);

void set_color(RGB_colors_t);


#endif /* RAMOS_UGALDE_T4_LED_RGB_H_ */
