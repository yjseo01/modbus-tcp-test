/* Server.c */

#include "Server.h"

const int NB_BITS = 16;
const int NB_INPUT_BITS = 16;
const int NB_REGISTERS = 16;
const int NB_INPUT_REGISTERS = 16;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("<usage> : %s <ip> \n", argv[0]);
        exit(1);
    }

    int slave_sock;
    int rc = 0;
    uint8_t buf[MODBUS_TCP_MAX_ADU_LENGTH] = {};

    modbus_t *ctx;

    modbus_mapping_t *map = modbus_mapping_new_start_address(0, NB_BITS, 0, NB_INPUT_BITS, 0, NB_REGISTERS, 0, NB_INPUT_REGISTERS);
    if (map == NULL)
    {
        fprintf(stderr, "failed to allocate the mapping: %s\n",
                modbus_strerror(errno));
        exit(1);
    }
    initMap(map);

    ctx = modbus_new_tcp(argv[1], 502);

    slave_sock = modbus_tcp_listen(ctx, 1);
    printf("Waiting for client(master)... \n");

    while (modbus_tcp_accept(ctx, &slave_sock) < 1)
    {
        continue;
    }

    while (1)
    {
        printf("----------------------------------------------\n");
        uint16_t st_addr;
        uint16_t length;
        int error = 0;

        do
        {
            rc = modbus_receive(ctx, buf);
        } while (rc == 0);

        if (rc < 0)
        {
            fprintf(stderr, "%s\n", modbus_strerror(errno));
            close(slave_sock);
            break;
        }

        printf("modbus_receive succeed. (rc: %d) \n", rc);
        struct mb_tcp *frame = (struct mb_tcp *)buf;

        printf("function code is 0x%02X\n", frame->f_code);
        printf("protocol id : %d\n", frame->p_id);
        printf("transaction id : %d\n", (uint16_t)(buf[0] << 8 | buf[1])); // big endian to little endian

        /* handle invalid adress access error */
        st_addr = (uint16_t)(buf[10] << 8 | buf[9]); // start address
        printf("start_addr: %d\n", st_addr);

        switch (frame->f_code)
        {
        case WMR:
        case RMR:
            length = buf[11];
            printf("length: %d\n", length);
            if (st_addr < 0 || st_addr > NB_REGISTERS - 1)
            {
                fprintf(stderr, "Invalid address access: start address out of range \n");
                error = -1;
            }
            else if (st_addr + length > NB_REGISTERS - 1)
            {
                fprintf(stderr, "Invalid address access: quantity of registers out of range \n");
                error = -1;
            }
            break;
        case WSR:
            if (st_addr < 0 || st_addr > NB_REGISTERS - 1)
            {
                fprintf(stderr, "Invalid address access: start address out of range \n");
                error = -1;
            }
            break;
        case RIR:
            length = buf[11];
            printf("length: %d\n", length);
            if (st_addr < 0 || st_addr > NB_INPUT_REGISTERS - 1)
            {
                fprintf(stderr, "Invalid address access: start address out of range \n");
                error = -1;
            }
            else if (st_addr + length > NB_INPUT_REGISTERS - 1)
            {
                fprintf(stderr, "Invalid address access: quantity of registers out of range \n");
                error = -1;
            }
            break;
        case WMC:
        case RC:
            length = buf[11];
            printf("length: %d\n", length);
            if (st_addr < 0 || st_addr > NB_BITS - 1)
            {
                fprintf(stderr, "Invalid address access: start address out of range \n");
                error = -1;
            }
            else if (st_addr + length > NB_BITS - 1)
            {
                fprintf(stderr, "Invalid address access: quantity of coils out of range \n");
                error = -1;
            }
            break;
        case WSC:
            if (st_addr < 0 || st_addr > NB_BITS - 1)
            {
                fprintf(stderr, "Invalid address access: start address out of range \n");
                error = -1;
            }
            break;
        case RDI:
            length = buf[11];
            printf("length: %d\n", length);
            if (st_addr < 0 || st_addr > NB_INPUT_BITS - 1)
            {
                fprintf(stderr, "Invalid address access: start address out of range \n");
                error = -1;
            }
            else if (st_addr + length > NB_INPUT_BITS - 1)
            {
                fprintf(stderr, "Invalid address access: quantity of coils out of range \n");
                error = -1;
            }
            break;

        default:
            break;
        }

        rc = modbus_reply(ctx, buf, rc, map);

        if (rc < 0)
        {
            fprintf(stderr, "%s\n", modbus_strerror(errno));
            break;
        }
        else
        {
            if (error != -1)
                printf("modbus_reply succeed. (rc: %d) \n", rc);
        }
    }

    close(slave_sock);
    modbus_free(ctx);
    modbus_mapping_free(map);

    return 0;
}