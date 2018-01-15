/*
 * ax5043_config.h
 *
 *  Created on: Dec 15, 2017
 *      Author: ffwxjw
 */

#ifndef AX5043_CONFIG_H_
#define AX5043_CONFIG_H_

// Configurable radio parameters
#define PREAMBLE_LEN_BYTES 4
#define PREAMBLE_CHAR 0x55
#define PREAMBLE_FLAGS 0x38
#define SYNCWORD_FLAGS 0x18
#define SYNCWORD 0xAACCAACC
#define XTALFREQ 48e6
#define RSSIOFFSET 64

// SPI pins defined here
#define AX5043_MOSI D11
#define AX5043_MISO D12
#define AX5043_SCLK D13
#define AX5043_CS 	D14

#endif /* AX5043_CONFIG_H_ */
