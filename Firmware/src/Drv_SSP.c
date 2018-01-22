/*
 * Drv_SSP.c
 *
 *  Created on: 17/11/2015
 *      Author: Agustin Solano (asolano@gmail.com) y Juan Ignacio Cerrudo (juanicerrudo@gmail.com)
 */

#include "Drv_SSP.h"
#include "chip.h"
/**
 * @brief Init the SSP module
 */
void Drv_SSP_init()
{

	Chip_SSP_Init(LPC_SSP); //select which of the modules to initialize
	/* Set up clock and power for SSP1 module */
	/* Configure SSP1 pins */
	Chip_SCU_PinMuxSet(0xf, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC0)); /* CLK0 */
	Chip_SCU_PinMuxSet(0x1, 3, (SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC5)); /* MISO1 */
	Chip_SCU_PinMuxSet(0x1, 4, (SCU_MODE_PULLUP | SCU_MODE_FUNC5)); /* MOSI1 */
}

/**
 * @brief De-Init the SSP module
 */
void Drv_SSP_deInit()
{
	Chip_SSP_DeInit(LPC_SSP); //select which of the modules to de-initialize
}

/**
 * @brief Configuration of format and data of the SSP module
 */
void Drv_SSP_setup()
{
	static SSP_ConfigFormat ssp_format;
	ssp_format.frameFormat = SSP_FRAMEFORMAT_SPI; //configure the module with SPI protocol
	ssp_format.bits = SSP_BITS_8; // 8 bits by frame
	ssp_format.clockMode = SSP_CLOCK_MODE1; // see Clock Modes

	Chip_SSP_SetFormat(LPC_SSP, ssp_format.bits, ssp_format.frameFormat, ssp_format.clockMode);

	Chip_SSP_Enable(LPC_SSP);

	Chip_SSP_SetMaster(LPC_SSP, 1); //set SSP module as Master

//	uint32_t clk = Chip_Clock_GetPCLKDiv(SYSCTL_PCLK_SSP0);
//	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_SSP0,1);   ojo con esto!!!!
//	clk = Chip_Clock_GetPCLKDiv(SYSCTL_PCLK_SSP0)

	//Chip_SSP_SetBitRate(LPC_SSP, 16000000); //set bit rate
	Chip_SSP_SetBitRate(LPC_SSP, 3000000); //set bit rate

	//LPC_SSP->CR0 = 0x0077;

}


/**
 * @brief Send and Receive a byte via SSP
 * @param to_send Byte to be sent
 * @return Received byte 
 */
uint8_t Drv_SSP_transferByte(uint8_t to_send)
{
	uint8_t ssp_tx_buf = to_send; //buffer of data to be sent
	uint8_t ssp_rx_buf = 0; //buffer of received data

	Chip_SSP_DATA_SETUP_T ssp_xf;
	ssp_xf.length = 1; //transfer one byte
	ssp_xf.rx_cnt = 0;
	ssp_xf.rx_data = &ssp_rx_buf;
	ssp_xf.tx_cnt = 0;
	ssp_xf.tx_data = &ssp_tx_buf;

	Chip_SSP_RWFrames_Blocking(LPC_SSP, &ssp_xf);

	return ssp_rx_buf;
}


/**
 * @brief Faster way to transfer a single a byte via SSP
 * @param out Byte to be sent
 * @return in Received byte
 */

uint8_t spi_rw( uint8_t out )
{
  uint8_t in;
  LPC_SSP->DR = out & 0xFFFF;
  while (LPC_SSP->SR & 0x10 ) { ; }
  in = LPC_SSP->DR;

  return in;
}

/**
 * @brief Send and Receive a byte via SSP
 * @param to_send Byte to be sent
 * @return Received byte
 */
void Drv_SSP_transferMultiplBytes(uint8_t* to_send, uint8_t* to_recive, uint8_t length)
{
	uint8_t* ssp_tx_buf = to_send; //buffer of data to be sent
	uint8_t* ssp_rx_buf = to_recive; //buffer of received data

	Chip_SSP_DATA_SETUP_T ssp_xf;
	ssp_xf.length = length; //transfer one byte
	ssp_xf.rx_cnt = 0;
	ssp_xf.rx_data = ssp_rx_buf;
	ssp_xf.tx_cnt = 0;
	ssp_xf.tx_data = ssp_tx_buf;

	Chip_SSP_RWFrames_Blocking(LPC_SSP, &ssp_xf);


}
