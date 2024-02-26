/* ServerFunc.c */

#include "Server.h"

void initMap(modbus_mapping_t *map)
{
    srand(time(NULL));

    for (int i = 0; i < NB_INPUT_REGISTERS; i++)
        map->tab_input_registers[i] = rand() % 100;

    for (int i = 0; i < NB_REGISTERS; i++)
        map->tab_registers[i] = i;

    for (int i = 0; i < NB_BITS; i++)
        map->tab_bits[i] = 0;

    for (int i = 0; i < NB_INPUT_BITS; i++)
        map->tab_input_bits[i] = rand() % 2;
}