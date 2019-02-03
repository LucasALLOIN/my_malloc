/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** bit_table_operation.c
*/

#include "malloc.h"

void set_bit_used(size_t where, size_t to_set, char *bit_table)
{
    unsigned char op[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

    for (size_t i = 0; i < to_set; i++, where++)
        bit_table[where / 8] |= op[where % 8];
}

void set_bit_unused(size_t where, size_t to_set, char *bit_table)
{
    unsigned char op[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

    for (size_t i = 0; i < to_set; i++, where++)
        bit_table[where / 8] ^= op[where % 8];
}

size_t get_bigger_space(char *bit_table, size_t bit_table_size,
size_t where, size_t last_bigger_space)
{
    size_t bigger_s = last_bigger_space;
    size_t curr_f_match = 0;
    unsigned char op[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};

    for (size_t i = where; i < bit_table_size; i++) {
        if ((bit_table[i / 8] & op[i % 8]) == 0)
            curr_f_match++;
        else {
            bigger_s = (bigger_s < curr_f_match) ? curr_f_match : bigger_s;
            curr_f_match = 0;
        }
    }
    bigger_s = (bigger_s < curr_f_match) ? curr_f_match : bigger_s;
    return (bigger_s * 8);
}

void set_bigger_space(rnb_node_t *to_alloc, size_t nbr_of_match, size_t where)
{
    char *bit_table = (char *) ((malloc_t *)(to_alloc)->data)->data;
    size_t bit_table_s = (((malloc_t *)(to_alloc)->data)->bit_table_size) * 8;

    ((malloc_t *) to_alloc->data)->bigger_space = get_bigger_space(bit_table,
    bit_table_s, where, nbr_of_match);
}
