/*
 * ax5043.h
 *
 *  Created on: Dec 14, 2017
 *      Author: ffwxjw
 */

#ifndef AX5043_H_
#define AX5043_H_

#include <stdint.h>
#include "ax5043_spi_registers.h"
#include "ax5043_config.h"

// Power states
#define AX5043_PWRSTATE_POWERDOWN       0x0
#define AX5043_PWRSTATE_DEEPSLEEP       0x1
#define AX5043_PWRSTATE_REGS_ON         0x4
#define AX5043_PWRSTATE_XTAL_ON         0x5
#define AX5043_PWRSTATE_FIFO_ON         0x7
#define AX5043_PWRSTATE_SYNTH_RX        0x8
#define AX5043_PWRSTATE_FULL_RX         0x9
#define AX5043_PWRSTATE_WOR_RX          0xB
#define AX5043_PWRSTATE_SYNTH_TX        0xC
#define AX5043_PWRSTATE_FULL_TX         0xD

// FIFO commands
#define AX5043_FIFOCMD_NOP				0x00
#define AX5043_FIFOCMD_DATA				0x01
#define AX5043_FIFOCMD_REPEATDATA		0x02
#define AX5043_FIFOCMD_TIMER			0x10
#define AX5043_FIFOCMD_RSSI				0x11
#define AX5043_FIFOCMD_FREQOFFS			0x12
#define AX5043_FIFOCMD_RSSI				0x11
#define AX5043_FIFOCMD_RFFREQOFFS		0x13
#define AX5043_FIFOCMD_DATARATE			0x14
#define AX5043_FIFOCMD_ANTRSSI			0x15
#define AX5043_FIFOCMD_TXCTRL			0x1C
#define AX5043_FIFOCMD_TXPWR			0x1D

// Radio error types
#define AXRADIO_ERR_NOERROR             0x00
#define AXRADIO_ERR_NOTSUPPORTED        0x01
#define AXRADIO_ERR_BUSY                0x02
#define AXRADIO_ERR_TIMEOUT             0x03
#define AXRADIO_ERR_INVALID             0x04
#define AXRADIO_ERR_NOCHIP              0x05
#define AXRADIO_ERR_RANGING             0x06
#define AXRADIO_ERR_LOCKLOST            0x07
#define AXRADIO_ERR_RETRANSMISSION      0x08
#define AXRADIO_ERR_RESYNC              0x09
#define AXRADIO_ERR_RESYNCTIMEOUT       0x0A
#define AXRADIO_ERR_RECEIVESTART		0x0B

// Function prototypes for spi communication
void ax5043_spi_init();
void ax5043_spi_transaction(char * tx_buffer, int tx_length, char *  rx_buffer, int rx_length);
void ax5043_set_register(uint16_t address, uint8_t data);
char ax5043_get_register(uint16_t address);

// Radio function prototypes
void ax5043_reset();
void ax5043_radio_setup_tx();
uint8_t ax5043_pll_ranging();
void ax5043_wait_for_xtal();
void ax5043_writefifo(const uint8_t *ptr, uint8_t len);
void ax5043_transmit(uint8_t *pkt, uint16_t pktlen);

#endif /* AX5043_H_ */
