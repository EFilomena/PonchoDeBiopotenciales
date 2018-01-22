/*
 * Drv_UART.c
 *
 *  Created on: 5/11/2015
 *      Author: Agustin Solano (asolano@gmail.com) y Juan Ignacio Cerrudo (juanicerrudo@gmail.com)
 */

#include "Drv_UART.h"
#include "chip.h"

/** @brief UART initial setup and initialization
 */
void Drv_UART_setup()
{
	Chip_UART_Init(UART_SELECTION);
	Chip_UART_SetBaud(UART_SELECTION, BAUD_RATE);
   	Chip_UART_SetupFIFOS(UART_SELECTION, UART_FCR_FIFO_EN | UART_FCR_TRG_LEV0);
   	Chip_UART_TXEnable(UART_SELECTION);
    Chip_SCU_PinMux(7, 1, MD_PDN, FUNC6);              /* P7_1: UART2_TXD */
	Chip_SCU_PinMux(7, 2, MD_PLN|MD_EZI|MD_ZI, FUNC6); /* P7_2: UART2_RXD */
}


/**
 * @brief Ring Buffers initialization
 */
void Drv_UART_RBinit(uint8_t rxbuff[], uint8_t txbuff[])
{
	/* Before using the ring buffers, initialize them using the ring
		   buffer init function */
		//RingBuffer_Init(&rxring, rxbuff, 1, UART_RRB_SIZE);
		//RingBuffer_Init(&txring, txbuff, 1, UART_SRB_SIZE);
}


/**
 * @brief Send data by UART
 * @param data[] Array of data to be sent
 * @param numByte Number of bytes to send by UART  
 */
void Drv_UART_Send(uint8_t data[], int numBytes)
{

	//Chip_UART_SendRB(UART_SELECTION, &txring, data, sizeof(data) - 1);
	//Chip_UART_SendByte(UART_SELECTION, 65);
	Chip_UART_SendBlocking(UART_SELECTION, data, numBytes);
	//bytes = Chip_UART_Send(UART_SELECTION, data, 40);
}

/**
 * @brief Receive data by UART
 */
int Drv_UART_ReceiveRB(uint8_t data[], int numBytes)
{	int receivedBytes = 0;
	//receivedBytes = Chip_UART_ReadRB(UART_SELECTION, &rxring, &data, numBytes);

	return receivedBytes;
}

/**
 * @brief Read one byte
 * @return Received byte
 */
uint8_t Drv_UART_ReadByte()
{
	uint8_t byte;

	byte = Chip_UART_ReadByte(UART_SELECTION);

	return byte;

}

/**
 * @brief Indicates if there is new data to be read
 * @return TRUE if there is new byte at UART buffer, FALSE if not
 */
bool Drv_UART_available()
{
	bool available = false;
	available = (Chip_UART_ReadLineStatus(UART_SELECTION) & UART_LSR_RDR);

	return available;
}

/** @brief UART de-initialization
 */
void Drv_UART_DeInit ()
{
	/* DeInitialize UART0 peripheral */
	//NVIC_DisableIRQ(IRQ_SELECTION);
	Chip_UART_DeInit(UART_SELECTION);
}

/**
 * @brief	UART 0 interrupt handler using ring buffers
 * @return	Nothing
 */
void HANDLER_NAME(void)
{
	//Chip_UART_IRQRBHandler(UART_SELECTION, &rxring, &txring);
}
