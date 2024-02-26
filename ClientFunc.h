/* ClientFunc.h */

#ifndef CLIENTFUNC_H
#define CLIENTFUNC_H

#include "Client.h"

/* function code input function */
uint8_t inputFunctionCode();

/* function code processing */
void ReadDiscreteInputs(modbus_t *ctx); // Read Discrete Inputs
void ReadCoils(modbus_t *ctx);          // Read Coils
void WriteSingleCoil(modbus_t *ctx);    // Write Single Coil
void WriteMultipleCoils(modbus_t *ctx); // Write Multiple Coils

void ReadInputRegisters(modbus_t *ctx);     // Read Input Registers
void ReadMultipleRegisters(modbus_t *ctx);  // Read Multiple Registers
void WriteSingleRegister(modbus_t *ctx);    // Write Single Register
void WriteMultipleRegisters(modbus_t *ctx); // Write Multiple Registers

#endif