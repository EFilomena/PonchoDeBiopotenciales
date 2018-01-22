/*
 * Drv_GPIO.c
 *
 *  Created on: 13/11/2015
 *      Author: Agustin Solano (asolano@gmail.com) y Juan Ignacio Cerrudo (juanicerrudo@gmail.com)
 */

#include "Drv_GPIO.h"
#include "chip.h"

/**
 * @brief Initialize GPIO port
 */
void Drv_GPIO_init()
{
	/** Configuration of the GPIO port*/
	Chip_GPIO_Init(LPC_GPIO_PORT);

	/** Mapping of GPIO  pins*/
	// true (1) for output, false (0)for input
	Chip_SCU_PinMux(4,5,MD_PUP|MD_EZI|MD_ZI,FUNC0);  //Mapeo GPIO2[5] en P4_5    PWDN/
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,2,5,1);
	Chip_SCU_PinMux(4,6,MD_PUP|MD_EZI|MD_ZI,FUNC0);  //Mapeo GPIO2[6] en P4_6    DRDY/
    Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,2,6,0);
	Chip_SCU_PinMux(4,8,MD_PUP|MD_EZI|MD_ZI,FUNC4);  //Mapeo GPIO5[12] en P4_8   START
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,12,1);
	Chip_SCU_PinMux(4,9,MD_PUP|MD_EZI|MD_ZI,FUNC4);  //Mapeo GPIO5[13] en P4_9   CS/
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,13,1);
    Chip_SCU_PinMux(4,10,MD_PUP|MD_EZI|MD_ZI,FUNC4); //Mapeo GPIO5[14] en P4_10  RESET
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT,5,14,1);
}

/**
 * @brief De-Initialize GPIO port
 */
void Drv_GPIO_deInit()
{
	Chip_GPIO_DeInit(LPC_GPIO_PORT);
}

/**
 * @brief Set a GPIO pin state
 * @param port Number of GPIO port 
 * @param pin Number of GPIO pin
 * @param state TRUE for HIGH, FALSE for LOW
 */
void Drv_GPIO_setPinState(uint8_t port, uint8_t pin, bool state)
{
	Chip_GPIO_SetPinState(LPC_GPIO_PORT,port, pin, state);
}

/**
 * @brief Get a GPIO pin state
 * @param port Number of GPIO port 
 * @param pin Number of GPIO pin
 * @return TRUE if the GPIO is HIGH, FALSE if LOW
 */
bool Drv_GPIO_getPinState(uint8_t port, uint8_t pin)
{
	return Chip_GPIO_GetPinState(LPC_GPIO_PORT, port, pin);
}

/**
 * @brief Set GPIO direction for a single GPIO pin
 * @param port Number of GPIO port 
 * @param pin Number of GPIO pin
 * @param output: TRUE for OUTPUT, FALSE for INPUT
 */
void Drv_GPIO_setPinDir(uint8_t port, uint8_t pin, bool output)
{
	Chip_GPIO_SetPinDIR(LPC_GPIO_PORT, port, pin, output);
}

/**
 * @brief Get GPIO direction for a single GPIO pin
 * @param port Number of GPIO port 
 * @param pin Number of GPIO pin
 * @return TRUE in the GPIO is an OUTPUT, FALSE if INPUT
 */
bool Drv_GPIO_getPinDir(uint8_t port, uint8_t pin)
{
	return Chip_GPIO_GetPinDIR(LPC_GPIO_PORT, port, pin);
}

/**
 * @brief Toggle an individual GPIO output to the opposite state
 * @param port Number of GPIO port
 * @param pin Number of GPIO pin
 */
void Drv_GPIO_setPinToggle(uint8_t port, uint8_t pin)
{
	Chip_GPIO_SetPinToggle(LPC_GPIO_PORT, port, pin);
}









