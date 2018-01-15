/*
 * ax5043.c
 *
 *  Created on: Dec 14, 2017
 *      Author: ffwxjw
 */

#include "ax5043.h"
#include "mbed.h"

// Create the SPI objects
SPI spiMaster(AX5043_MOSI, AX5043_MISO, AX5043_SCLK);
DigitalOut chipSelect(AX5043_CS);

void ax5043_spi_init() {
	// Set to 8 bit mode, drive chip select high
	spiMaster.format(8,0);
	chipSelect = 1;
}

void ax5043_spi_transaction(char * tx_buffer, int tx_length, char *  rx_buffer, int rx_length) {
	chipSelect = 0;
    spiMaster.write(tx_buffer, tx_length, rx_buffer, rx_length);
    chipSelect = 1;
}

void ax5043_set_register(uint16_t address, uint8_t data) {
	char txBuffer[3];
	char rxBuffer[3];
    txBuffer[0] = 0xF0 | address>>8;    // Get upper nibble of 12 byte address, mask with write command 0xF
    txBuffer[1] = 0xFF & address;       // Use bottom byte of address
    txBuffer[2] = data;
    ax5043_spi_transaction(txBuffer, 3, rxBuffer, 3);
}

char ax5043_get_register(uint16_t address) {
	char txBuffer[3];
	char rxBuffer[3];
	txBuffer[0] = 0x70 | address>>8;    // Get upper nibble of 12 byte address, mask with read command 0x7
    txBuffer[1] = 0xFF & address;       // Use bottom byte of address
    txBuffer[2] = 0x00;
    ax5043_spi_transaction(txBuffer, 3, rxBuffer, 3);
    return rxBuffer[2];
}

// This function is populated with output from RadioLab config.c file
// Update accordingly for customizations.
void ax5043_radio_setup_tx() {
	// TX: fcarrier=868.300MHz bw= 15.000kHz br= 10.000kBit/s
    ax5043_set_register(AX5043_MODULATION     , 0x08);
    ax5043_set_register(AX5043_ENCODING       , 0x00);
    ax5043_set_register(AX5043_FRAMING        , 0x26);
    ax5043_set_register(AX5043_PINFUNCSYSCLK  , 0x01);
    /*
    ax5043_set_register(AX5043_PINFUNCDCLK    , 0x01);
    ax5043_set_register(AX5043_PINFUNCDATA    , 0x01);
    ax5043_set_register(AX5043_PINFUNCANTSEL  , 0x01);
    ax5043_set_register(AX5043_PINFUNCPWRAMP  , 0x07);
    ax5043_set_register(AX5043_WAKEUPXOEARLY  , 0x01);
    ax5043_set_register(AX5043_IFFREQ1        , 0x01);
    ax5043_set_register(AX5043_IFFREQ0        , 0x06);
    ax5043_set_register(AX5043_DECIMATION     , 0x29);
    ax5043_set_register(AX5043_RXDATARATE2    , 0x00);
    ax5043_set_register(AX5043_RXDATARATE1    , 0x3C);
    ax5043_set_register(AX5043_RXDATARATE0    , 0xF9);
    ax5043_set_register(AX5043_MAXDROFFSET2   , 0x00);
    ax5043_set_register(AX5043_MAXDROFFSET1   , 0x00);
    ax5043_set_register(AX5043_MAXDROFFSET0   , 0x00);
    ax5043_set_register(AX5043_MAXRFOFFSET2   , 0x80);
    ax5043_set_register(AX5043_MAXRFOFFSET1   , 0x02);
    ax5043_set_register(AX5043_MAXRFOFFSET0   , 0x5F);
    ax5043_set_register(AX5043_FSKDMAX1       , 0x00);
    ax5043_set_register(AX5043_FSKDMAX0       , 0xA6);
    ax5043_set_register(AX5043_FSKDMIN1       , 0xFF);
    ax5043_set_register(AX5043_FSKDMIN0       , 0x5A);
    ax5043_set_register(AX5043_AMPLFILTER     , 0x00);
    ax5043_set_register(AX5043_RXPARAMSETS    , 0xF4);
    ax5043_set_register(AX5043_AGCGAIN0       , 0xD6);
    ax5043_set_register(AX5043_AGCTARGET0     , 0x84);
    ax5043_set_register(AX5043_TIMEGAIN0      , 0xF8);
    ax5043_set_register(AX5043_DRGAIN0        , 0xF2);
    ax5043_set_register(AX5043_PHASEGAIN0     , 0xC3);
    ax5043_set_register(AX5043_FREQUENCYGAINA0,	0x0F);
    ax5043_set_register(AX5043_FREQUENCYGAINB0, 0x1F);
    ax5043_set_register(AX5043_FREQUENCYGAINC0, 0x09);
    ax5043_set_register(AX5043_FREQUENCYGAIND0, 0x09);
    ax5043_set_register(AX5043_AMPLITUDEGAIN0 , 0x06);
    ax5043_set_register(AX5043_FREQDEV10      , 0x00);
    ax5043_set_register(AX5043_FREQDEV00      , 0x00);
    ax5043_set_register(AX5043_BBOFFSRES0     , 0x00);
    ax5043_set_register(AX5043_AGCGAIN1       , 0xD6);
    ax5043_set_register(AX5043_AGCTARGET1     , 0x84);
    ax5043_set_register(AX5043_AGCAHYST1      , 0x00);
    ax5043_set_register(AX5043_AGCMINMAX1     , 0x00);
    ax5043_set_register(AX5043_TIMEGAIN1      , 0xF6);
    ax5043_set_register(AX5043_DRGAIN1        , 0xF1);
    ax5043_set_register(AX5043_PHASEGAIN1     , 0xC3);
    ax5043_set_register(AX5043_FREQUENCYGAINA1, 0x0F);
    ax5043_set_register(AX5043_FREQUENCYGAINB1, 0x1F);
    ax5043_set_register(AX5043_FREQUENCYGAINC1, 0x09);
    ax5043_set_register(AX5043_FREQUENCYGAIND1, 0x09);
    ax5043_set_register(AX5043_AMPLITUDEGAIN1 , 0x06);
    ax5043_set_register(AX5043_FREQDEV11      , 0x00);
    ax5043_set_register(AX5043_FREQDEV01      , 0x43);
    ax5043_set_register(AX5043_FOURFSK1       , 0x16);
    ax5043_set_register(AX5043_BBOFFSRES1     , 0x00);
    ax5043_set_register(AX5043_AGCGAIN3       , 0xFF);
    ax5043_set_register(AX5043_AGCTARGET3     , 0x84);
    ax5043_set_register(AX5043_AGCAHYST3      , 0x00);
    ax5043_set_register(AX5043_AGCMINMAX3     , 0x00);
    ax5043_set_register(AX5043_TIMEGAIN3      , 0xF5);
    ax5043_set_register(AX5043_DRGAIN3        , 0xF0);
    ax5043_set_register(AX5043_PHASEGAIN3     , 0xC3);
    ax5043_set_register(AX5043_FREQUENCYGAINA3, 0x0F);
    ax5043_set_register(AX5043_FREQUENCYGAINB3, 0x1F);
    ax5043_set_register(AX5043_FREQUENCYGAINC3, 0x0D);
    ax5043_set_register(AX5043_FREQUENCYGAIND3, 0x0D);
    ax5043_set_register(AX5043_AMPLITUDEGAIN3 , 0x06);
    ax5043_set_register(AX5043_FREQDEV13      , 0x00);
    ax5043_set_register(AX5043_FREQDEV03      , 0x43);
    ax5043_set_register(AX5043_FOURFSK3       , 0x16);
    ax5043_set_register(AX5043_BBOFFSRES3     , 0x00);
    */
    ax5043_set_register(AX5043_MODCFGF        , 0x03);
    ax5043_set_register(AX5043_FSKDEV2        , 0x00);
    ax5043_set_register(AX5043_FSKDEV1        , 0x04);
    ax5043_set_register(AX5043_FSKDEV0        , 0x8D);
    ax5043_set_register(AX5043_MODCFGA        , 0x05);
    ax5043_set_register(AX5043_TXRATE2        , 0x00);
    ax5043_set_register(AX5043_TXRATE1        , 0x0D);
    ax5043_set_register(AX5043_TXRATE0        , 0xA7);
    ax5043_set_register(AX5043_TXPWRCOEFFB1   , 0x0F);
    ax5043_set_register(AX5043_TXPWRCOEFFB0   , 0xFF);
    ax5043_set_register(AX5043_PLLVCOI        , 0x99);
    ax5043_set_register(AX5043_PLLRNGCLK      , 0x05);
    /*
    ax5043_set_register(AX5043_BBTUNE         , 0x0F);
    ax5043_set_register(AX5043_BBOFFSCAP      , 0x77);
    ax5043_set_register(AX5043_PKTADDRCFG     , 0x01);
    ax5043_set_register(AX5043_PKTLENCFG      , 0x80);
    ax5043_set_register(AX5043_PKTLENOFFSET   , 0x00);
    ax5043_set_register(AX5043_PKTMAXLEN      , 0xC8);
    ax5043_set_register(AX5043_MATCH0PAT3     , 0xAA);
    ax5043_set_register(AX5043_MATCH0PAT2     , 0xCC);
    ax5043_set_register(AX5043_MATCH0PAT1     , 0xAA);
    ax5043_set_register(AX5043_MATCH0PAT0     , 0xCC);
    ax5043_set_register(AX5043_MATCH0LEN      , 0x1F);
    ax5043_set_register(AX5043_MATCH0MAX      , 0x1F);
    ax5043_set_register(AX5043_MATCH1PAT1     , 0x55);
    ax5043_set_register(AX5043_MATCH1PAT0     , 0x55);
    ax5043_set_register(AX5043_MATCH1LEN      , 0x8A);
    ax5043_set_register(AX5043_MATCH1MAX      , 0x0A);
    */
    ax5043_set_register(AX5043_TMGTXBOOST     , 0x5B);
    ax5043_set_register(AX5043_TMGTXSETTLE    , 0x3E);
    /*
	ax5043_set_register(AX5043_TMGRXBOOST     , 0x5B);
    ax5043_set_register(AX5043_TMGRXSETTLE    , 0x3E);
    ax5043_set_register(AX5043_TMGRXOFFSACQ   , 0x00);
    ax5043_set_register(AX5043_TMGRXCOARSEAGC , 0x9C);
    ax5043_set_register(AX5043_TMGRXRSSI      , 0x03);
    ax5043_set_register(AX5043_TMGRXPREAMBLE2 , 0x35);
    ax5043_set_register(AX5043_RSSIABSTHR     , 0xE0);
    ax5043_set_register(AX5043_BGNDRSSITHR    , 0x00);
    ax5043_set_register(AX5043_PKTCHUNKSIZE   , 0x0D);
    ax5043_set_register(AX5043_PKTACCEPTFLAGS , 0x20);
    ax5043_set_register(AX5043_DACVALUE1      , 0x00);
    ax5043_set_register(AX5043_DACVALUE0      , 0x00);
    ax5043_set_register(AX5043_DACCONFIG      , 0x00);
    */
    ax5043_set_register(AX5043_REF            , 0x03);
    ax5043_set_register(AX5043_XTALOSC        , 0x04);
    ax5043_set_register(AX5043_XTALAMPL       , 0x00);
    /*
    ax5043_set_register(AX5043_0xF1C          , 0x07);
    ax5043_set_register(AX5043_0xF21          , 0x68);
    ax5043_set_register(AX5043_0xF22          , 0xFF);
    ax5043_set_register(AX5043_0xF23          , 0x84);
    ax5043_set_register(AX5043_0xF26          , 0x98);
    ax5043_set_register(AX5043_0xF34          , 0x08);
    ax5043_set_register(AX5043_0xF35          , 0x11);
    ax5043_set_register(AX5043_0xF44          , 0x25);
     */
    // Tx Registers
    ax5043_set_register(AX5043_PLLLOOP        , 0x09);
    ax5043_set_register(AX5043_PLLCPI         , 0x02);
    ax5043_set_register(AX5043_PLLVCODIV      , 0x20);
    ax5043_set_register(AX5043_XTALCAP        , 0x00);
    ax5043_set_register(AX5043_0xF00          , 0x0F);
    ax5043_set_register(AX5043_0xF18          , 0x06);

    // Frequency related
    uint32_t f = 0x1216EEEF;
	ax5043_set_register(AX5043_FREQA0, f);
	ax5043_set_register(AX5043_FREQA1, f >> 8);
	ax5043_set_register(AX5043_FREQA2, f >> 16);
	ax5043_set_register(AX5043_FREQA3, f >> 24);
}

void ax5043_radio_setup_rx() {
	// RX: fcarrier=868.300MHz bw= 15.000kHz br= 10.000kBit/s
	ax5043_set_register(AX5043_MODULATION            , 0x08);
	ax5043_set_register(AX5043_ENCODING              , 0x00);
	ax5043_set_register(AX5043_FRAMING               , 0x26);
	ax5043_set_register(AX5043_PINFUNCSYSCLK         , 0x01);
	/*
	ax5043_set_register(AX5043_PINFUNCDCLK           , 0x01);
	ax5043_set_register(AX5043_PINFUNCDATA           , 0x01);
	ax5043_set_register(AX5043_PINFUNCANTSEL         , 0x01);
	ax5043_set_register(AX5043_PINFUNCPWRAMP         , 0x07);
	ax5043_set_register(AX5043_WAKEUPXOEARLY         , 0x01);
	*/
	ax5043_set_register(AX5043_IFFREQ1               , 0x02);
	ax5043_set_register(AX5043_IFFREQ0               , 0x22);
	ax5043_set_register(AX5043_DECIMATION            , 0x14);
	ax5043_set_register(AX5043_RXDATARATE2           , 0x00);
	ax5043_set_register(AX5043_RXDATARATE1           , 0x3C);
	ax5043_set_register(AX5043_RXDATARATE0           , 0x00);
	ax5043_set_register(AX5043_MAXDROFFSET2          , 0x00);
	ax5043_set_register(AX5043_MAXDROFFSET1          , 0x00);
	ax5043_set_register(AX5043_MAXDROFFSET0          , 0x00);
	ax5043_set_register(AX5043_MAXRFOFFSET2          , 0x80);
	ax5043_set_register(AX5043_MAXRFOFFSET1          , 0x02);
	ax5043_set_register(AX5043_MAXRFOFFSET0          , 0x5F);
	/*
 	ax5043_set_register(AX5043_FSKDMAX1              , 0x05);
	ax5043_set_register(AX5043_FSKDMAX0              , 0x99);
	ax5043_set_register(AX5043_FSKDMIN1              , 0xFA);
	ax5043_set_register(AX5043_FSKDMIN0              , 0x67);
	*/
	ax5043_set_register(AX5043_AMPLFILTER            , 0x00);
	ax5043_set_register(AX5043_RXPARAMSETS           , 0xF4);
	ax5043_set_register(AX5043_AGCGAIN0              , 0xC5);
	ax5043_set_register(AX5043_AGCTARGET0            , 0x84);
	ax5043_set_register(AX5043_TIMEGAIN0             , 0xF8);
	ax5043_set_register(AX5043_DRGAIN0               , 0xF2);
	ax5043_set_register(AX5043_PHASEGAIN0            , 0xC3);
	ax5043_set_register(AX5043_FREQUENCYGAINA0       , 0x0F);
	ax5043_set_register(AX5043_FREQUENCYGAINB0       , 0x1F);
	ax5043_set_register(AX5043_FREQUENCYGAINC0       , 0x08);
	ax5043_set_register(AX5043_FREQUENCYGAIND0       , 0x08);
	ax5043_set_register(AX5043_AMPLITUDEGAIN0        , 0x06);
	ax5043_set_register(AX5043_FREQDEV10             , 0x00);
	ax5043_set_register(AX5043_FREQDEV00             , 0x00);
	ax5043_set_register(AX5043_BBOFFSRES0            , 0x00);
	ax5043_set_register(AX5043_AGCGAIN1              , 0xC5);
	ax5043_set_register(AX5043_AGCTARGET1            , 0x84);
	ax5043_set_register(AX5043_AGCAHYST1             , 0x00);
	ax5043_set_register(AX5043_AGCMINMAX1            , 0x00);
	ax5043_set_register(AX5043_TIMEGAIN1             , 0xF6);
	ax5043_set_register(AX5043_DRGAIN1               , 0xF1);
	ax5043_set_register(AX5043_PHASEGAIN1            , 0xC3);
	ax5043_set_register(AX5043_FREQUENCYGAINA1       , 0x0F);
	ax5043_set_register(AX5043_FREQUENCYGAINB1       , 0x1F);
	ax5043_set_register(AX5043_FREQUENCYGAINC1       , 0x08);
	ax5043_set_register(AX5043_FREQUENCYGAIND1       , 0x08);
	ax5043_set_register(AX5043_AMPLITUDEGAIN1        , 0x06);
	ax5043_set_register(AX5043_FREQDEV11             , 0x00);
	ax5043_set_register(AX5043_FREQDEV01             , 0x43);
	ax5043_set_register(AX5043_FOURFSK1              , 0x16);
	ax5043_set_register(AX5043_BBOFFSRES1            , 0x00);
	ax5043_set_register(AX5043_AGCGAIN3              , 0xFF);
	ax5043_set_register(AX5043_AGCTARGET3            , 0x84);
	ax5043_set_register(AX5043_AGCAHYST3             , 0x00);
	ax5043_set_register(AX5043_AGCMINMAX3            , 0x00);
	ax5043_set_register(AX5043_TIMEGAIN3             , 0xF5);
	ax5043_set_register(AX5043_DRGAIN3               , 0xF0);
	ax5043_set_register(AX5043_PHASEGAIN3            , 0xC3);
	ax5043_set_register(AX5043_FREQUENCYGAINA3       , 0x0F);
	ax5043_set_register(AX5043_FREQUENCYGAINB3       , 0x1F);
	ax5043_set_register(AX5043_FREQUENCYGAINC3       , 0x0C);
	ax5043_set_register(AX5043_FREQUENCYGAIND3       , 0x0C);
	ax5043_set_register(AX5043_AMPLITUDEGAIN3        , 0x06);
	ax5043_set_register(AX5043_FREQDEV13             , 0x00);
	ax5043_set_register(AX5043_FREQDEV03             , 0x43);
	ax5043_set_register(AX5043_FOURFSK3              , 0x16);
	ax5043_set_register(AX5043_BBOFFSRES3            , 0x00);
	/*
	ax5043_set_register(AX5043_MODCFGF               , 0x02);
	*/
	ax5043_set_register(AX5043_FSKDEV2               , 0x00);
	ax5043_set_register(AX5043_FSKDEV1               , 0x04);
	ax5043_set_register(AX5043_FSKDEV0               , 0x8D);
	/*
 	ax5043_set_register(AX5043_MODCFGA               , 0x05);
	ax5043_set_register(AX5043_TXRATE2               , 0x00);
	ax5043_set_register(AX5043_TXRATE1               , 0x10);
	ax5043_set_register(AX5043_TXRATE0               , 0x62);
	ax5043_set_register(AX5043_TXPWRCOEFFB1          , 0x0F);
	ax5043_set_register(AX5043_TXPWRCOEFFB0          , 0xFF);
	*/
	ax5043_set_register(AX5043_PLLVCOI               , 0x99);
	ax5043_set_register(AX5043_PLLRNGCLK             , 0x05);
	ax5043_set_register(AX5043_BBTUNE                , 0x0F);
	ax5043_set_register(AX5043_BBOFFSCAP             , 0x77);
	/*
	ax5043_set_register(AX5043_PKTADDRCFG            , 0x00);
	ax5043_set_register(AX5043_TMGTXBOOST            , 0x57);
	ax5043_set_register(AX5043_TMGTXSETTLE           , 0x39);
	 */
	ax5043_set_register(AX5043_TMGRXBOOST            , 0x5B);
	ax5043_set_register(AX5043_TMGRXSETTLE           , 0x3E);
	ax5043_set_register(AX5043_TMGRXOFFSACQ          , 0x00);
	ax5043_set_register(AX5043_TMGRXCOARSEAGC		  ,	0x9C);
	/*
	ax5043_set_register(AX5043_TMGRXRSSI             , 0x03);
	*/
	ax5043_set_register(AX5043_TMGRXPREAMBLE2        , 0x35);
	/*
	ax5043_set_register(AX5043_RSSIABSTHR            , 0xE8);
	ax5043_set_register(AX5043_BGNDRSSITHR           , 0x00);
	 */
	ax5043_set_register(AX5043_PKTCHUNKSIZE          , 0x0D);
	ax5043_set_register(AX5043_PKTACCEPTFLAGS        , 0x20);
	/*
	ax5043_set_register(AX5043_DACVALUE1             , 0x00);
	ax5043_set_register(AX5043_DACVALUE0             , 0x00);
	ax5043_set_register(AX5043_DACCONFIG             , 0x00);
	 */
	ax5043_set_register(AX5043_REF                   , 0x03);
	ax5043_set_register(AX5043_XTALOSC               , 0x04);
	ax5043_set_register(AX5043_XTALAMPL              , 0x00);
	ax5043_set_register(AX5043_0xF1C                 , 0x07);
	ax5043_set_register(AX5043_0xF21                 , 0x68);
	ax5043_set_register(AX5043_0xF22                 , 0xFF);
	ax5043_set_register(AX5043_0xF23                 , 0x84);
	ax5043_set_register(AX5043_0xF26                 , 0x98);
	ax5043_set_register(AX5043_0xF34                 , 0x08);
	ax5043_set_register(AX5043_0xF35                 , 0x11);
	ax5043_set_register(AX5043_0xF44                 , 0x25);

	// settings from ax5043_set_register(set_registers_rx(void)  [config.c  from AX-RadioLab project]
	ax5043_set_register(AX5043_PLLLOOP               , 0x07);
	ax5043_set_register(AX5043_PLLCPI                , 0x08);
	ax5043_set_register(AX5043_PLLVCODIV             , 0x20);
	ax5043_set_register(AX5043_XTALCAP               , 0x00);
	ax5043_set_register(AX5043_0xF00                 , 0x0F);
	ax5043_set_register(AX5043_0xF18                 , 0x06);

	// settings from ax5043_set_registers_rxcont(void)  [config.c  from AX-RadioLab project]
	ax5043_set_register(AX5043_TMGRXAGC              , 0x00);
	ax5043_set_register(AX5043_TMGRXPREAMBLE1        , 0x00);
	ax5043_set_register(AX5043_PKTMISCFLAGS          , 0x00);

    // Frequency related
    uint32_t f = 0x1216EEEF;
	ax5043_set_register(AX5043_FREQA0, f);
	ax5043_set_register(AX5043_FREQA1, f >> 8);
	ax5043_set_register(AX5043_FREQA2, f >> 16);
	ax5043_set_register(AX5043_FREQA3, f >> 24);

	// RSSI
    ax5043_set_register(AX5043_RSSIREFERENCE, 0xF7 + RSSIOFFSET); // value from axradio_phy_rssireference [config.c  from AX-RadioLab project]

	// Sync word matching
	// note: the LSB (bit and byte) of MATCH0PAT[3..0] is the first bit received. The bit after the MSB of  MATCH0PAT[3..0] is the first bit going into the FIFO
	// when matching a pattern shorter than 32 bit it must be MSB aligned in MATCH0PAT[3..0]
	// A successful sync word match (MATCH0 unit) triggers receiption into the FIFO.
    //
    // Further AX5043_RADIOSTATE changes from 0x0C to 0x0D after a successfull preamble match (MATCH1 unit) and to 0xF
	// after a succesfull sync word match. This causes the radio controler demand the RX parameter sets 0, 1 and 3 (Radiostate = 0x0C, 0x0D, 0x0F)
	// This mechanism allows the use of fairly aggressive tracking loops for fast settling on the praeamble and switch to less aggressive settings
	// once for sync word detection and actual packet receiption
	// Consult the "Receiver State Machine" section in the AX5043 programming manual for details and mind the indirection layer provided by AX5043_RXPARAMSETS
    ax5043_set_register(AX5043_MATCH0PAT3            , (SYNCWORD>>24) & 0xFF);
	ax5043_set_register(AX5043_MATCH0PAT2            , (SYNCWORD>>16) & 0xFF);
	ax5043_set_register(AX5043_MATCH0PAT1            , (SYNCWORD>>8) & 0xFF);
	ax5043_set_register(AX5043_MATCH0PAT0            , (SYNCWORD>>0) & 0xFF);
	ax5043_set_register(AX5043_MATCH0LEN             , 0x1F); // 32bit exact match
	ax5043_set_register(AX5043_MATCH0MAX             , 0x1F); // 32bit exact match

	// Preamble matching
	ax5043_set_register(AX5043_MATCH1PAT1            , PREAMBLE_CHAR);
	ax5043_set_register(AX5043_MATCH1PAT0            , PREAMBLE_CHAR);
	ax5043_set_register(AX5043_MATCH1LEN             , 0x8A); // 11 bit exact match
	ax5043_set_register(AX5043_MATCH1MAX             , 0x0A); // 11 bit exact match

	// Length byte configuration
	// 8 bit length byte at position 0 after sync word (length byte also counts the lengh byte itself,
	// but not the CRC bytes. Deviations can be programmed in AX5043_PKTLENOFFSET
    ax5043_set_register(AX5043_PKTLENCFG             , 0x80);
	ax5043_set_register(AX5043_PKTLENOFFSET          , 0x00); // value is added to received length byte. Signed.
	ax5043_set_register(AX5043_PKTMAXLEN             , 0xC8); // maximum packet length is 240byte

	// Store RSSI and frequency offset
    ax5043_set_register(AX5043_PKTSTOREFLAGS , 0x14);
}

void ax5043_reset() {
	// AX5043 requires the programmer to set and then clear the reset bit to do a reset
	// Set reset bit, and enable crystal ocsillator,
	// enable reference, and don't care for wake from deep sleep (used a 0)
	// Set power mode to 0111 which is FIFO enabled with xtal
	ax5043_set_register(AX5043_PWRMODE, 0xE7);

	// Clear reset bit with same settings as above
	ax5043_set_register(AX5043_PWRMODE, 0x67);
}

uint8_t ax5043_pll_ranging() {
	uint8_t pllloop_save, pllcpi_save, pllrng;

	// Save current loop filter bandwidth and charge pump current settings
	pllloop_save = ax5043_get_register(AX5043_PLLLOOP);
    pllcpi_save = ax5043_get_register(AX5043_PLLCPI);

    // Default to 100kHz loop filter bandwidth and default starting point for charge pump current
    ax5043_set_register(AX5043_PLLLOOP, 0x09);
	ax5043_set_register(AX5043_PLLCPI, 0x08);

	// Turn on XTAL and wait for it to be stablilized
	ax5043_set_register(AX5043_PWRMODE, AX5043_PWRSTATE_XTAL_ON);
	ax5043_wait_for_xtal();

	// Enable PLL auto ranging interrupt and do the ranging starting at range 8
	ax5043_set_register(AX5043_IRQMASK1, 0x10);
	ax5043_set_register(AX5043_PLLRANGINGA, 0x18);
	for (;;) {
		if (ax5043_get_register(AX5043_IRQREQUEST1) & 0x10)
			break;
	}
	// Done, clear interrupt
	ax5043_set_register(AX5043_IRQMASK1, 0x00);

	pllrng = ax5043_get_register(AX5043_PLLRANGINGA);

	// Restore settings
	ax5043_set_register(AX5043_PLLLOOP, pllloop_save);
	ax5043_set_register(AX5043_PLLCPI, pllcpi_save);

	// Ranging error, power down AX5043
	if( pllrng & 0x20 ) // ranging error, power down AX5043
	{
		ax5043_set_register(AX5043_PWRMODE, AX5043_PWRSTATE_POWERDOWN);
		return 1;
	}
	return 0;
}

void ax5043_wait_for_xtal() {
	// Enable XTAL interrupt
	uint8_t oldIRQMask = ax5043_get_register(AX5043_IRQMASK1);
    ax5043_set_register(AX5043_IRQMASK1, (oldIRQMask |= 0x01));
    for(;;)
    {
        if (ax5043_get_register(AX5043_XTALSTATUS))
            break;
    }
    ax5043_set_register(AX5043_IRQMASK1, 0);
}

void ax5043_transmit(uint8_t *pkt, uint16_t pktlen) {
	// This function assumes that the chip is initialized and the PLL has been auto-ranged.
	// *pkt points to the packet without sync word, but including len byte (if desired)
	// CRC (computed over the entire *pkt) is added by the hardware automatically if configured in the register settings

	// Set sync word based on SYNCWORD definition
	uint8_t ax_syncword[4] = {(SYNCWORD)>>0 & 0xFF, (SYNCWORD)>>8 & 0xFF, (SYNCWORD)>>16 & 0xFF, (SYNCWORD)>>24 & 0xFF};

	// Clear the FIFO and set power mode to FULL_TX
    ax5043_set_register(AX5043_FIFOSTAT, 3); // clear FIFO
    ax5043_set_register(AX5043_PWRMODE, AX5043_PWRSTATE_FULL_TX);

    // Loop until the VDD for the modem is stable before writing to FIFO
    while (!(ax5043_get_register(AX5043_POWSTAT) & 0x08));

    // Write preamble to the FIFO using a REPEATDATA chunk
    ax5043_set_register(AX5043_FIFODATA, AX5043_FIFOCMD_REPEATDATA | (3 << 5));
    ax5043_set_register(AX5043_FIFODATA, PREAMBLE_FLAGS);
    ax5043_set_register(AX5043_FIFODATA, PREAMBLE_LEN_BYTES);
    ax5043_set_register(AX5043_FIFODATA, PREAMBLE_CHAR);

    // Write SYNC WORD to FIFO
    if ((ax5043_get_register(AX5043_FRAMING) & 0x0E) == 0x06) {
    	// Write SYNC word if framing mode is raw_patternmatch
    	uint8_t i;
        ax5043_set_register(AX5043_FIFODATA, (AX5043_FIFOCMD_DATA | ((sizeof(ax_syncword) + 1) << 5)));
        ax5043_set_register(AX5043_FIFODATA, SYNCWORD_FLAGS);
        for (i = 0; i < sizeof(ax_syncword); ++i) {
            ax5043_set_register(AX5043_FIFODATA, ax_syncword[i]);
        }
    }

    // Write packet to FIFO using a DATA chunk
    ax5043_set_register(AX5043_FIFODATA, AX5043_FIFOCMD_DATA | (7 << 5));
	ax5043_set_register(AX5043_FIFODATA, pktlen + 1);	// Write FIFO chunk length byte (length includes the flag byte, thus the +1)
    ax5043_set_register(AX5043_FIFODATA, 0x03); 		// pkt_start | pkt_end
    ax5043_writefifo(pkt, pktlen);
    ax5043_get_register(AX5043_RADIOEVENTREQ0);		// Clear flag
    ax5043_wait_for_xtal();						// Wait until cystal oscillator ready
    ax5043_set_register(AX5043_FIFOSTAT, 4);			// Commit the FIFO --> TX starts

    // Wait until TX is finished
    {
        ax5043_set_register(AX5043_RADIOEVENTMASK0, 0x01); // TX done flag
        ax5043_set_register(AX5043_IRQMASK0, 0x40); 		// Radio controller irq
        for(;;)
        {
            if(ax5043_get_register(AX5043_RADIOEVENTREQ0) & 0x01)
                break;
        }
    }

    // Transmit is done, go back to sleep
    ax5043_set_register(AX5043_PWRMODE, AX5043_PWRSTATE_POWERDOWN);
}

void ax5043_writefifo(const uint8_t *ptr, uint8_t len) {
	if (!len)
		return;
	do {
		ax5043_set_register(AX5043_FIFODATA, *ptr++);
		//*(uint8_t *)(AX8052_RADIOBASE | FDATA) = *ptr++;
	} while (--len);
}

void ax5043_readfifo(uint8_t *ptr, uint8_t len) {
	if (!len)
		return;
	do {
		*ptr++ = ax5043_get_register(AX5043_FIFODATA);
		//*ptr++ = *(const uint8_t __xdata *)(AX8052_RADIOBASE | FDATA);
	} while (--len);
}

void ax5043_receiver_on_continuous() {
	// This function assumes that the chip is initialized and the PLL has been auto-ranged.
	//
	// Clear the FIFO and set power mode to FULL_RX
	// Set FIFO not empty interrupt
	ax5043_set_register(AX5043_FIFOSTAT, 3);
	ax5043_set_register(AX5043_IRQMASK0, 0x01);
	ax5043_set_register(AX5043_IRQMASK1, 0x00);
	ax5043_set_register(AX5043_PWRMODE, AX5043_PWRSTATE_FULL_RX);
}

void ax5043_receive_isr() {
    uint8_t fifo_cmd, flags;
    uint8_t i;

    // Clear request so interrupt does not fire again. sync_rx enables interrupt on radio state changed in order to wake up on SDF detected
    uint8_t len = ax5043_get_register(AX5043_RADIOEVENTREQ0);

    while (ax5043_get_register(AX5043_IRQREQUEST0) & 0x01) {    // while fifo not empty
        fifo_cmd = ax5043_get_register(AX5043_FIFODATA); // read command
        len = (fifo_cmd & 0xE0) >> 5; // top 3 bits encode payload len
        if (len == 7)
            len = ax5043_get_register(AX5043_FIFODATA); // 7 means variable length, -> get length byte
        fifo_cmd &= 0x1F;
        switch (fifo_cmd) {
			case AX5043_FIFOCMD_DATA:
				if (!len)
					break;
				flags = ax5043_get_register(AX5043_FIFODATA);
				--len;
				ax5043_readfifo(ax5043_rxbuffer, len);
				ax5043_pktlen = len;
				break;
		   case AX5043_FIFOCMD_RFFREQOFFS:
				i = ax5043_get_register(AX5043_FIFODATA);
				i &= 0x0F;
				i |= 1 + (uint8_t)~(i & 0x08);
				ax5043_offset = ((int8_t)i) >> 8;
				ax5043_offset <<=8;
				ax5043_offset |= i;
				ax5043_offset <<=8;
				ax5043_offset |= ax5043_get_register(AX5043_FIFODATA);
				ax5043_offset <<=8;
				ax5043_offset |= ax5043_get_register(AX5043_FIFODATA);
				// Determine the frequency offset in Hz
			    // Frequency offset:  conversion factor from register value to Hz is f_xtal / 2^24.
			    // For optimized code avoiding float computations use the AX-RadioLAB generated function axradio_conv_freq_tohz()
			    // offset_hz = (2.861*(float)ax5043_offset); // 48MHZ
			    ax5043_offset_hz = ( ((float)XTALFREQ) / ((float)((uint32_t)1<<24)) )*(float)ax5043_offset; // 40MHZ
				break;
			case AX5043_FIFOCMD_RSSI:
				if (len != 1) {
					// Fall through to the default case, to drop the chunk
				}
				else {
					// Otherwise, get the valid RSSI
					int8_t r = ax5043_get_register(AX5043_FIFODATA);
					ax5043_rssi = r - (int16_t)RSSIOFFSET;
					break;
				}
			default:
				// Unhandled chunk type, just remove it from FIFO
				if (!len)
					break;
				i = len;
				do {
					ax5043_get_register(AX5043_FIFODATA); // purge FIFO
				}
				while (--i);
				break;
			} // end switch(fifo_cmd)
    } // end while( fifo not empty )
}
