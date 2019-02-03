/*
** EPITECH PROJECT, 2019
** PSU_2018_malloc
** File description:
** free_realloc.c
*/

#include "malloc.h"

rnb_node_t *get_free_page(rnb_node_t **head, void *ptr)
{
    rnb_node_t *matchs = match_func_prefix(*head, ptr, &match_ptr);

    return (matchs);
}

unsigned int get_alloc_size(void *ptr)
{
    return (*(unsigned int *) (((void *) ptr) - 4));
}

void free(void *ptr)
{
    rnb_node_t *container = NULL;
    void *bit_table_end_ptr = NULL;
    size_t whe = 0;

    if (ptr == NULL)
        return;
    pthread_mutex_lock(&global_malloc_lock);
    container = get_free_page(get_rnb_head(), ptr);
    if (container == NULL) {
        pthread_mutex_unlock(&global_malloc_lock);
        return;
    }
    ptr = ptr - 4;
    bit_table_end_ptr = ((malloc_t *) container->data)->data
    + ((malloc_t *) container->data)->bit_table_size;
    whe = ptr - bit_table_end_ptr;
    set_bit_unused(whe / 8, get_alloc_size(ptr + 4),
    ((malloc_t *) container->data)->data);
    set_bigger_space(container, 0, 0);
    pthread_mutex_unlock(&global_malloc_lock);
}

void *realloc(void *ptr, size_t size)
{
    void *return_ptr;
    unsigned alloc_size = 0;

    if (ptr == NULL || get_free_page(get_rnb_head(), ptr) == NULL)
        return (malloc(size));
    else if (size == 0) {
        free(ptr);
        return (NULL);
    }
    return_ptr = malloc(size);
    if (return_ptr == NULL)
        return (NULL);
    alloc_size = get_alloc_size(ptr) * 8;
    pthread_mutex_lock(&global_malloc_lock);
    memcpy(return_ptr, ptr,
    (alloc_size > (get_alloc_size(return_ptr) * 8)) ? size : alloc_size);
    pthread_mutex_unlock(&global_malloc_lock);
    free(ptr);
    return (return_ptr);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    return (realloc(ptr, nmemb * size));
}