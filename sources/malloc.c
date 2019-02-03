/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** malloc.c
*/

#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "malloc.h"
#include "rnb_trees.h"

int create_pages(size_t size, rnb_node_t **head)
{
    size_t bit_table = (getpagesize() - sizeof(malloc_t) - (8 * 8)) / (8 * 8);
    size_t min_nbr_pages_to_alloc = size / (bit_table * 8 * 8) + 1;
    size_t nbr_pages_to_al = get_true_size(min_nbr_pages_to_alloc, head);
    void *value = sbrk(nbr_pages_to_al * getpagesize());
    malloc_t *ptr = NULL;

    if (value == (void *) -1)
        return (1);
    ptr = value;
    ptr->bit_table_size = bit_table * nbr_pages_to_al;
    ptr->bigger_space = (nbr_pages_to_al * (bit_table * 8 * 8));
    ptr->data = value + sizeof(malloc_t);
    insert(head, (int) nbr_pages_to_al, value);
    return (0);
}

rnb_node_t *get_allocable_page(rnb_node_t **head, size_t size)
{
    size_t bit_table = (getpagesize() - sizeof(malloc_t) - (8 * 8)) / (8 * 8);
    size_t min_nbr_pages_to_alloc = size / (bit_table * 8 * 8) + 1;
    rnb_node_t *matchs = match_sup(*head, (int) min_nbr_pages_to_alloc,
    (int) size, &match_val);

    if (matchs == NULL) {
        if (create_pages(size, head) == 1)
            return (NULL);
        return (get_allocable_page(head, size));
    }
    return (matchs);
}

void *allocate_mem(size_t size, rnb_node_t *to_all)
{
    char *bit_table = (char *) ((malloc_t *)(to_all)->data)->data;
    size_t bit_table_s = (((malloc_t *)(to_all)->data)->bit_table_size) * 8;
    size_t b = (size / 8) + ((size % 8 == 0) ? 0 : 1);
    size_t nbr_of_ma = 0;
    unsigned char op[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    size_t i = 0;

    for (size_t c_f_match = 0 ; i < bit_table_s && c_f_match != b; i++) {
        if ((bit_table[i / 8] & op[i % 8]) == 0) {
            c_f_match++;
        } else {
            nbr_of_ma = (nbr_of_ma < c_f_match) ? c_f_match : nbr_of_ma;
            c_f_match = 0;
        }
    }
    set_bit_used(i - b, b, bit_table);
    set_bigger_space(to_all, nbr_of_ma, i);
    *(unsigned int *) (((void *) bit_table) + (bit_table_s / 8) +
    ((i - b) * 8)) = (unsigned int) b;
    return ((void *) bit_table) + (bit_table_s / 8) + ((i - b) * 8) + 4;
}

rnb_node_t **get_rnb_head(void)
{
    static rnb_node_t *head = 0x0;

    return (&head);
}

void *malloc(size_t size)
{
    rnb_node_t **head = get_rnb_head();
    rnb_node_t *allocable_mem = NULL;

    if (size == 0)
        return (NULL);
    pthread_mutex_lock(&global_malloc_lock);
    if (*head == 0x0) {
        if (create_pages(size + 4, head) == 1) {
            pthread_mutex_unlock(&global_malloc_lock);
            return (NULL);
        }
    }
    allocable_mem = get_allocable_page(head, size + 4);
    if (allocable_mem == NULL) {
        pthread_mutex_unlock(&global_malloc_lock);
        return (NULL);
    }
    void *tst = allocate_mem(size + 4, allocable_mem);
    pthread_mutex_unlock(&global_malloc_lock);
    return (tst);
}