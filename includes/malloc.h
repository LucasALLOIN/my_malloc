/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** malloc.h
*/

#ifndef PSU_2018_MALLOC_MALLOC_H
#define PSU_2018_MALLOC_MALLOC_H

#include <unistd.h>
#include <pthread.h>
#include "rnb_trees.h"

typedef struct malloc_s {
    size_t bit_table_size;
    size_t bigger_space;
    void *data;
} malloc_t;

pthread_mutex_t global_malloc_lock;

#endif //PSU_2018_MALLOC_MALLOC_H
