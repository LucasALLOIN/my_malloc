/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** match_function.c
*/

#include "malloc.h"

int match_val(rnb_node_t *node, int number)
{
    if (((size_t) ((malloc_t *) node->data)->bigger_space) >=
    (long unsigned int) (number))
        return (1);
    return (0);
}

int match_size(rnb_node_t *node, size_t *number)
{
    if (number != NULL) {
        if (((size_t) node->number) > (*number))
            *number = ((size_t) node->number) + 1;
        else if (((size_t) node->number) == (*number))
            *number = *number + 1;
    }
    return (0);
}

int match_ptr(rnb_node_t *node, void *ptr)
{
    void *start_ptr = ((malloc_t *) node->data)->data +
    ((malloc_t *) node->data)->bit_table_size;
    void *end_ptr = start_ptr +
    (((malloc_t *) node->data)->bit_table_size * 8 * 8);

    if (ptr != NULL) {
        if (ptr >= start_ptr && ptr <= end_ptr)
            return (1);
    }
    return (0);
}

size_t get_true_size(size_t size, rnb_node_t **head)
{
    size_t dup = size;

    match_func_prefix(*head, &dup,
    (int (*)(rnb_node_t *root, void *data)) &match_size);
    return (dup);
}
