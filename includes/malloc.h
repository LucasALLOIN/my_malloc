/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** malloc.h
*/

#ifndef PSU_2018_MALLOC_MALLOC_H
#define PSU_2018_MALLOC_MALLOC_H

#include <unistd.h>
#include "rnb_trees.h"

typedef struct malloc_s {
    size_t bit_table_size;
    void *data;
} malloc_t;

int match(rnb_node_t *node, size_t *number);

#endif //PSU_2018_MALLOC_MALLOC_H
