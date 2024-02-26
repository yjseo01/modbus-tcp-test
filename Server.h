/* Server.h */

#ifndef SERVER_H
#define SERVER_H

#include <errno.h>
#include <modbus/modbus-tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    uint16_t t_id;
    uint16_t p_id;
    uint16_t len;
    uint8_t f_code;
    uint8_t data[];
};

#endif