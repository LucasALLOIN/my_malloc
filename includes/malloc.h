/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** malloc.h
*/

#ifndef PSU_2018_MALLOC_MALLOC_H
#define PSU_2018_MALLOC_MALLOC_H

#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "rnb_trees.h"

typedef struct malloc_s {
    size_t bit_table_size;
    size_t bigger_space;
    void *data;
} malloc_t;

pthread_mutex_t global_malloc_lock;

int match_val(rnb_node_t *node, int number);
int match_size(rnb_node_t *node, size_t *number);
int match_ptr(rnb_node_t *node, void *ptr);
void set_bit_used(size_t where, size_t to_set, char *bit_table);
void set_bit_unused(size_t where, size_t to_set, char *bit_table);
size_t get_bigger_space(char *bit_table, size_t bit_table_size,
size_t where, size_t last_bigger_space);
void set_bigger_space(rnb_node_t *to_alloc, size_t nbr_of_match, size_t where);
void *malloc(size_t size);
rnb_node_t **get_rnb_head(void);
size_t get_true_size(size_t size, rnb_node_t **head);

#endif //PSU_2018_MALLOC_MALLOC_H