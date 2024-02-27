/* ClientFunc.h */

#include "ClientFunc.h"

uint8_t inputFunctionCode()
{
    uint8_t function_code;
    printf("function code: ");
    if (scanf("%" SCNx8, &function_code) != 1)
        return 0;

    return function_code;
}

void WriteMultipleRegisters(modbus_t *ctx)
{
    int nb;
    int start_addr;
    uint16_t *tab_reg;
    int write_registers;

    printf("holding registers address (0 ~ %d) \n\n", NB_REGISTERS - 1);

    printf("start address: ");
    scanf("%d", &start_addr);
    printf("quantity of registers: ");
    scanf("%d", &nb);

    tab_reg = (uint16_t *)malloc(nb * (sizeof(uint16_t)));

    printf("data (0 ~ 255)\n");
    for (int i = 0; i < nb; i++)
    {
        printf("data[%d]: ", i);
        scanf("%hu", &(tab_reg[i]));
    }
    printf("\n");

    printf("writing registers...\n");

    write_registers =
        modbus_write_registers(ctx, start_addr, nb, tab_reg);

    if (write_registers == nb)
    {
        printf("Successful writing to (%d) registers. \n\n", write_registers);
    }
    else
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
    }

    free(tab_reg);
}

void ReadMultipleRegisters(modbus_t *ctx)
{
    int start_addr;
    int nb;
    uint16_t *dest;
    int read_registers;
    printf("holding registers address (0 ~ %d) \n\n", NB_REGISTERS - 1);

    printf("start address: ");
    scanf("%d", &start_addr);
    printf("quantity of registers: ");
    scanf("%d", &nb);
    printf("\n");

    dest = (uint16_t *)malloc(sizeof(uint16_t) * nb);

    printf("reading registers...\n");

    read_registers = modbus_read_registers(ctx, start_addr, nb, dest);

    if (read_registers == nb)
    {
        printf("Successful reading to (%d) registers. \n\n", read_registers);

        for (int i = 0; i < nb; i++)
            printf("    Register %d: %d\n", start_addr + i, dest[i]);
    }
    else
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
    }

    free(dest);
}

void ReadInputRegisters(modbus_t *ctx)
{
    int start_addr;
    int nb;
    uint16_t *dest;
    int read_registers;
    printf("input registers address (0 ~ %d) \n\n", NB_INPUT_REGISTERS - 1);

    printf("start address: ");
    scanf("%d", &start_addr);
    printf("quantity of registers: ");
    scanf("%d", &nb);
    printf("\n");

    dest = (uint16_t *)malloc(sizeof(uint16_t) * nb);

    printf("reading registers...\n");

    read_registers = modbus_read_input_registers(ctx, start_addr, nb, dest);

    if (read_registers == nb)
    {
        printf("Successful reading to (%d) registers. \n\n", read_registers);

        for (int i = 0; i < nb; i++)
            printf("    Register %d: %d\n", start_addr + i, dest[i]);
    }
    else
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
    }

    free(dest);
}

void ReadCoils(modbus_t *ctx)
{
    int start_addr;
    int nb;
    uint8_t *dest;
    int read_coils;
    printf("coils address (0 ~ %d) \n\n", NB_BITS - 1);

    printf("start address: ");
    scanf("%d", &start_addr);
    printf("quantity of coils: ");
    scanf("%d", &nb);
    printf("\n");

    dest = (uint8_t *)malloc(sizeof(uint8_t) * nb);

    printf("reading coils... \n");

    read_coils = modbus_read_bits(ctx, start_addr, nb, dest);
    if (read_coils == nb)
    {
        printf("Successful reading to (%d) coils. \n\n", read_coils);
        printf("    coils: ");
        for (int i = 0; i < nb; i++)
            printf("%hhu ", dest[i]);
        printf("\n");
    }
    else
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
    }

    free(dest);
}

void ReadDiscreteInputs(modbus_t *ctx)
{
    int start_addr;
    int nb;
    uint8_t *dest;
    int read_coils;
    printf("input coils address (0 ~ %d) \n\n", NB_BITS - 1);

    printf("start address: ");
    scanf("%d", &start_addr);
    printf("quantity of coils: ");
    scanf("%d", &nb);
    printf("\n");

    dest = (uint8_t *)malloc(sizeof(uint8_t) * nb);

    printf("reading coils... \n");

    read_coils = modbus_read_input_bits(ctx, start_addr, nb, dest);
    if (read_coils == nb)
    {
        printf("Successful reading to (%d) coils. \n\n", read_coils);
        printf("    coils: ");
        for (int i = 0; i < nb; i++)
            printf("%hhu ", dest[i]);
        printf("\n");
    }
    else
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
    }

    free(dest);
}

void WriteSingleCoil(modbus_t *ctx)
{
    int start_addr;
    int status;
    int write_bit;
    printf("input coils address (0 ~ %d) \n\n", NB_BITS - 1);

    printf("address: ");
    scanf("%d", &start_addr);
    printf("status: ");
    scanf("%d", &status);

    printf("writing bit... \n");

    write_bit = modbus_write_bit(ctx, start_addr, status);

    if (write_bit == 1)
    {
        printf("Successful writing to (%d) bit. \n\n", write_bit);
    }
    else
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
    }
}

void WriteSingleRegister(modbus_t *ctx)
{
    int reg_addr;
    uint16_t data;
    int write_register;

    printf("holding registers address (0 ~ %d) \n\n", NB_REGISTERS - 1);

    printf("start address: ");
    scanf("%d", &reg_addr);

    printf("data (0 ~ 255)\n");
    printf("data: ");
    scanf("%hu", &data);
    printf("\n");

    printf("writing register...\n");

    write_register =
        modbus_write_register(ctx, reg_addr, data);

    if (write_register == 1)
    {
        printf("Successful writing to (%d) register. \n\n", write_register);
    }
    else
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
    }
}

void WriteMultipleCoils(modbus_t *ctx)
{
    int start_addr;
    int nb;
    uint8_t *tab_coils;
    int write_bits;
    printf("input coils address (0 ~ %d) \n\n", NB_BITS - 1);

    printf("start address: ");
    scanf("%d", &start_addr);
    printf("quantity of coils: ");
    scanf("%d", &nb);

    tab_coils = (uint8_t *)malloc(nb * (sizeof(uint8_t)));
    printf("status (0 or 1) \n");
    for (int i = 0; i < nb; i++)
    {
        printf("status[%d]: ", i);
        scanf("%hhd", &(tab_coils[i]));
    }
    printf("\n");

    printf("writing bits...\n");

    write_bits = modbus_write_bits(ctx, start_addr, nb, tab_coils);

    if (write_bits == nb)
    {
        printf("Successful writing to (%d) bit. \n\n", write_bits);
    }
    else
    {
        fprintf(stderr, "%s\n", modbus_strerror(errno));
    }

    free(tab_coils);
}