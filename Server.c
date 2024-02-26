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

    printf("--------------------------------------------------\n");

    slave_sock = modbus_tcp_listen(ctx, 1);
    printf("Waiting for client(master)... \n");

    while (modbus_tcp_accept(ctx, &slave_sock) < 1)
    {
        continue;
    }

    while (1)
    {
        do
        {
            rc = modbus_receive(ctx, buf);
        } while (rc == 0);

        if (rc < 0)
        {
            printf("%d\n", rc);
            printf("error %s\n", modbus_strerror(errno));
            close(slave_sock);
            break;
        }

        printf("----------------------------------------------\n");
        struct mb_tcp *frame = (struct mb_tcp *)buf;

        printf("function code is 0x%02X\n", frame->f_code);
        printf("protocol id : %d\n", frame->p_id);
        printf("transaction id : %d\n", frame->t_id);

        rc = modbus_reply(ctx, buf, rc, map);
        if (rc < 0)
        {
            printf("%d%d\n", rc, rc);
            printf("Error %s\n", modbus_strerror(errno));
            close(slave_sock);
            break;
        }
    }

    close(slave_sock);
    modbus_free(ctx);
    modbus_mapping_free(map);

    return 0;
}