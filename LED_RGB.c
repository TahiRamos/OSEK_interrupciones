/*
 * LED_RGB.c
 *
 * Created on: 3 feb 2023
 *      Author: Hegui Tahirí Ramos Ugalde
 */

#include "LED_RGB.h"
#include "bits.h"

void init_RGB()
{
	SIM_5 = 0x00002400;
	PCR_PTA11 = 0x00000100;   //red
	PCR_PTC09 = 0x00000100;	  //blue
	PCR_PTE06 = 0x00000100;	  //green
}

void set_color(RGB_colors_t color)
{
	switch(color)
	{
		case RED:
			GPIO_C_PDOR = 0x000; 	// enciende rojo
			GPIO_E_PDOR = 0x40;		// apaga verde
			GPIO_A_PDOR = 0x800;	// apaga azul
		break;

		case YELLOW:
			GPIO_A_PDOR = 0x800;	// apaga azul
			GPIO_C_PDOR = 0x000;	// enciende rojo
			GPIO_E_PDOR = 0x00;		// enciende verde
		break;

		case GREEN:
			GPIO_E_PDOR = 0x00;		// enciende verde
			GPIO_C_PDOR = 0x200;	// apaga rojo
			GPIO_A_PDOR = 0x800;	// apaga azul
		break;

		case CYAN:
			GPIO_A_PDOR = 0x800;	// apaga azul
			GPIO_E_PDOR = 0x00;		// enciende verde
			GPIO_C_PDOR = 0x000;	// enciende rojo
		break;

		case BLUE:
			GPIO_A_PDOR = 0x000;	// enciende azul
			GPIO_C_PDOR = 0x200;	// apaga rojo
			GPIO_E_PDOR = 0x40;		// apaga verde
		break;

		case MAGENTA:
			GPIO_E_PDOR = 0x40;		// apaga verde
			GPIO_A_PDOR = 0x000;	// enciende azul
			GPIO_C_PDOR = 0x000;	// enciende rojo
		break;

		case WHITE:
			GPIO_C_PDOR = 0x000;	//enciende rojo
			GPIO_A_PDOR = 0x000;	//enciende azul
			GPIO_E_PDOR = 0x00;		//enciende verde
		break;

		case NONE:
			GPIO_E_PDOR = 0x40;		// apaga verde
			GPIO_C_PDOR = 0x200;	// apaga rojo
			GPIO_A_PDOR = 0x800;	// apaga azul
		break;
		default: 		// No existe esa opción
		break;
	}
}
