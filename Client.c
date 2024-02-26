/* Client.c */

#include "Client.h"

const int NB_BITS = 16;
const int NB_INPUT_BITS = 16;
const int NB_REGISTERS = 16;
const int NB_INPUT_REGISTERS = 16;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("<usage> : %s <server_ip> \n", argv[0]);
        return -1;
    }

    modbus_t *ctx;

    ctx = modbus_new_tcp(argv[1], 502);
    if (modbus_connect(ctx) == -1)
    {
        fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
        exit(1);
    }

    printf("------------------function code--------------------\n");
    printf("Read Discrete Inputs: 0x%02x\n", RDI);
    printf("Read Coils: 0x%02x\n", RC);
    printf("Write Single Coil: 0x%02x\n", WSC);
    printf("Write Multiple Coils: 0x%02x\n", WMC);
    printf("Read Input Registers: 0x%02x\n", RIR);
    printf("Read Multiple Registers: 0x%02x\n", RMR);
    printf("Write Single Register: 0x%02x\n", WSR);
    printf("Write Multiple Registers: 0x%02x\n", WMR);

    while (1)
    {
        printf("\n-------------------------------------------------\n");
        uint8_t function_code = inputFunctionCode();

        switch (function_code)
        {
        case WMR:
            WriteMultipleRegisters(ctx);
            break;
        case RMR:
            ReadMultipleRegisters(ctx);
            break;
        case RIR:
            ReadInputRegisters(ctx);
            break;
        case RC:
            ReadCoils(ctx);
            break;
        case RDI:
            ReadDiscreteInputs(ctx);
            break;
        case WSC:
            WriteSingleCoil(ctx);
            break;
        case WSR:
            WriteSingleRegister(ctx);
            break;
        case WMC:
            WriteMultipleCoils(ctx);
            break;
        default:
            fprintf(stderr, "Invalid input for function code\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF)
                ;
            break;
        }

        sleep(1);
    }

    modbus_close(ctx);
    modbus_free(ctx);
    return 0;
}