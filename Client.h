/* Client.h */

#ifndef CLIENT_H
#define CLIENT_H

#include <errno.h>
#include <inttypes.h>
#include <modbus/modbus-tcp.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* function code */
#define RDI 0x02 // Read Discrete Inputs
#define RC 0x01  // Read Coils
#define WSC 0x05 // Write Single Coil
#define WMC 0x0F // Write Multiple Coils

#define RIR 0x04 // Read Input Registers
#define RMR 0x03 // Read Multiple Registers
#define WSR 0x06 // Write Single Register
#define WMR 0x10 // Write Multiple Registers

/* size of the modbus map */
extern const int NB_BITS;
extern const int NB_INPUT_BITS;
extern const int NB_REGISTERS;
extern const int NB_INPUT_REGISTERS;

#endif