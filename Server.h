/* Server.h */

#ifndef SERVER_H
#define SERVER_H

#include <errno.h>
#include <modbus/modbus-tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

/* size of the modbus map */
extern const int NB_BITS;
extern const int NB_INPUT_BITS;
extern const int NB_REGISTERS;
extern const int NB_INPUT_REGISTERS;

/* structure of modbus tcp packet  */
struct mb_tcp
{
    uint16_t t_id;  // transaction id
    uint16_t p_id;  // protocol id (Modbus TCP is 0)
    uint16_t len;   // length
    uint8_t u_id;   // unit id
    uint8_t f_code; // function code
    uint8_t data[]; // data
};

#endif