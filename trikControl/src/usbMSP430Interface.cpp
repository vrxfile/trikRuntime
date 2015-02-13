/*
 * usbMSP430Interface.cpp
 *
 *  Created on: Fabruary 12, 2015
 *      Author: Rostislav Varzar
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <QByteArray>
#include <QDebug>
#include "usbMSP430Interface.h"

/// Extract number from packet
uint32_t hex2num(char *string, uint16_t pos, uint16_t numsize)
{
    uint32_t resnum = 0;
    uint32_t tmpnum = 0;
    char c = 0;
    for (uint16_t i = 0; i < numsize; i++)
    {
        c = toupper(string[pos+i]);
        tmpnum = c > '9' ? c - 'A' + 10 : c - '0';
        resnum |= (tmpnum << ((numsize - i - 1) * 4));
    }
    return resnum;
}


/// Make write register packet
void makeWriteRegPacket(char *msp_packet, uint8_t dev_addr, uint8_t reg_addr, uint32_t reg_val)
{
    uint8_t crc = (0xFF - (dev_addr + WRITE_FUNC + reg_addr + uint8_t(reg_val & 0xFF) + uint8_t((reg_val >> 8) & 0xFF) +
                   uint8_t((reg_val >> 16) & 0xFF) + uint8_t((reg_val >> 24) & 0xFF)) + 1) & 0xFF;  // Checksum
    sprintf(msp_packet, ":%02X%02X%02X%08X%02X\n", dev_addr, WRITE_FUNC, reg_addr, reg_val, crc);
}

/// Make read register packet
void makeReadRegPacket(char *msp_packet, uint8_t dev_addr, uint8_t reg_addr)
{
    uint8_t crc = (0xFF - (dev_addr + READ_FUNC + reg_addr) + 1) & 0xFF;  // Checksum
    sprintf(msp_packet, ":%02X%02X%02X%02X\n", dev_addr, READ_FUNC, reg_addr, crc);
}

/// Function for decoding received packet
uint32_t decodeReceivedPacket(char *msp_packet, uint8_t &dev_addr, uint8_t &func_code, uint8_t &reg_addr, uint32_t &reg_val)
{
    uint8_t crc1 = 0; //Received cheksum
    uint8_t crc2 = 0; //Calculated checksum
    if (msp_packet[0] != ':')                           // Start condition error
        return START_ERROR;
    if (strlen(msp_packet) != RECV_PACK_LEN)            // Incorrect packet length
        return LENGTH_ERROR;
    dev_addr = hex2num(msp_packet, 1, NUM_BYTE);        // Get device address
    func_code = hex2num(msp_packet, 3, NUM_BYTE);       // Get function
    reg_addr = hex2num(msp_packet, 5, NUM_BYTE);        // Get register address
    reg_val = hex2num(msp_packet, 7, NUM_DWORD);        // Get register value
    crc1 = hex2num(msp_packet, 15, NUM_BYTE);           // Get CRC from packet
    crc2 = (0xFF - (dev_addr + func_code + reg_addr + uint8_t(reg_val & 0xFF) + uint8_t((reg_val >> 8) & 0xFF) +
                       uint8_t((reg_val >> 16) & 0xFF) + uint8_t((reg_val >> 24) & 0xFF)) + 1) & 0xFF;   // Calculate CRC
    if (crc1 != crc2)                                   // Check CRC
        return CRC_ERROR;
    return NO_ERROR;                                    // Return NO ERROR
}

/// Send packet via USB port
void sendUSBPacket(char *usb_name, char *in_msp_packet, char *out_msp_packet)
{
    FILE *fusb;
    fusb = fopen(usb_name, "w");
    fprintf(fusb, in_msp_packet);
    fclose(fusb);
}

/// Write data to MSP430 via USB
void writeUSBMSP(QByteArray const &i2c_data)
{
    if (i2c_data.size() == 2)
    {
        switch (i2c_data[0])
        {
            case i2cMOT1:

                break;
            default:
                break;
        }
    }
    else
    {

    }
}

/// Read data from MSP430 via USB
uint32_t readUSBMSP(QByteArray const &i2c_data)
{
    if (i2c_data.size() == 2)
    {
        switch (i2c_data[0])
        {
            case i2cENC1:

                break;
            default:
                break;
        }
    }
    else
    {

    }
    return 0x00;
}