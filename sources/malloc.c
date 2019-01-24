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


void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char *str)
{
    write(1, str, strlen(str));
}

int my_put_nbr(int nb)
{
    if (nb >= 0) {
        if (nb > 9)
            my_put_nbr(nb / 10);
        my_putchar((nb % 10) + '0');
    } else {
        my_putchar('-');
        if (nb < -9)
            my_put_nbr((nb / 10) * -1);
        my_putchar(((nb % 10) * -1) + '0');
    }
    return (0);
}

char hex_digit(int v) {
    if (v >= 0 && v < 10)
        return '0' + v;
    else
        return 'a' + v - 10;
}

void print_address_hex(void* p0) {
    int i;
    uintptr_t p = (uintptr_t) p0;

    my_putchar('0');
    my_putchar('x');
    for (i = (sizeof(p) << 3) - 4; i >= 0; i -= 4) {
        my_putchar(hex_digit((p >> i) & 0xf));
    }
}


int match_val(rnb_node_t *node, size_t *number)
{
    if (number != NULL) {
        if (((size_t) node->number) >= (*number))
            return (1);
    }
    return (0);
}

int match_ptr(rnb_node_t *node, void *ptr)
{
    void *start_ptr = ((malloc_t *) node->data)->data + ((malloc_t *) node->data)->bit_table_size;
    void *end_ptr = start_ptr + (((malloc_t *) node->data)->bit_table_size * 8 * 8);

    /*my_putstr("IN MATCHPTR\n");
    my_putstr("Start ptr: ");
    print_address_hex(start_ptr);
    my_putchar('\n');
    my_putstr("End ptr: ");
    print_address_hex(end_ptr);
    my_putchar('\n');*/
    if (ptr != NULL) {
        if (ptr >= start_ptr && ptr <= end_ptr)
            return (1);
    }
    return (0);
}

int create_pages(size_t size, rnb_node_t **head)
{
    size_t bit_table_size_per_pages = (getpagesize() - sizeof(malloc_t) - (8 * 8)) / (8 * 8);
    size_t nbr_pages_to_alloc = size / (bit_table_size_per_pages * 8 * 8) + 1;
    void *value = sbrk(nbr_pages_to_alloc * getpagesize());
    malloc_t *ptr = NULL;

    if (value == (void *) -1)
        return (1);
    ptr = value;
    ptr->bit_table_size = bit_table_size_per_pages * nbr_pages_to_alloc;
    ptr->data = value + sizeof(malloc_t);
    micro_insert(head, (int) (nbr_pages_to_alloc * (bit_table_size_per_pages * 8 * 8)), value);
    return (0);
}

rnb_node_t *get_allocable_page(rnb_node_t **head, size_t size)
{
    rnb_node_t *matchs = match_func_prefix(*head, &size, (int (*)(rnb_node_t *root, void *data)) &match);

    if (matchs == NULL) {
        if (create_pages(size, head) == 1)
            return (NULL);
        return (get_allocable_page(head, size));
    }
    return (matchs);
}

size_t get_good_byte(size_t where, char *bit_table)
{
    size_t ret = 0;
    switch (where % 8) {
        case 0:
            ret += (bit_table[where / 8] & 0x80) ? 1 : 0;
            break;
        case 1:
            ret += (bit_table[where / 8] & 0x40) ? 1 : 0;
            break;
        case 2:
            ret += (bit_table[where / 8] & 0x20) ? 1 : 0;
            break;
        case 3:
            ret += (bit_table[where / 8] & 0x10) ? 1 : 0;
            break;
        case 4:
            ret += (bit_table[where / 8] & 0x08) ? 1 : 0;
            break;
        case 5:
            ret += (bit_table[where / 8] & 0x04) ? 1 : 0;
            break;
        case 6:
            ret += (bit_table[where / 8] & 0x02) ? 1 : 0;
            break;
        case 7:
            ret += (bit_table[where / 8] & 0x01) ? 1 : 0;
            break;
        default:
            break;
    }
    return (ret);
}

void set_bit_used(size_t where, size_t to_set, char *bit_table)
{
    for (size_t i = 0; i < to_set; i++, where++) {
        switch (where % 8) {
            case 0:
                bit_table[where / 8] |= 0x80;
                break;
            case 1:
                bit_table[where / 8] |= 0x40;
                break;
            case 2:
                bit_table[where / 8] |= 0x20;
                break;
            case 3:
                bit_table[where / 8] |= 0x10;
                break;
            case 4:
                bit_table[where / 8] |= 0x08;
                break;
            case 5:
                bit_table[where / 8] |= 0x04;
                break;
            case 6:
                bit_table[where / 8] |= 0x02;
                break;
            case 7:
                bit_table[where / 8] |= 0x01;
                break;
            default:
                break;
        }
    }
}

void set_bit_unused(size_t where, size_t to_set, char *bit_table)
{
    for (size_t i = 0; i < to_set; i++, where++) {
        switch (where % 8) {
            case 0:
                bit_table[where / 8] ^= 0x80;
                break;
            case 1:
                bit_table[where / 8] ^= 0x40;
                break;
            case 2:
                bit_table[where / 8] ^= 0x20;
                break;
            case 3:
                bit_table[where / 8] ^= 0x10;
                break;
            case 4:
                bit_table[where / 8] ^= 0x08;
                break;
            case 5:
                bit_table[where / 8] ^= 0x04;
                break;
            case 6:
                bit_table[where / 8] ^= 0x02;
                break;
            case 7:
                bit_table[where / 8] ^= 0x01;
                break;
            default:
                break;
        }
    }
}

size_t get_bigger_space(char *bit_table, size_t bit_table_size, size_t where, size_t last_bigger_space)
{
    size_t bigger_space = last_bigger_space;
    size_t current_free_match = 0;

    for (size_t i = where; i < bit_table_size; i++) {
        if (get_good_byte(i, bit_table) == 0)
            current_free_match++;
        else {
            bigger_space = (bigger_space < current_free_match)
                           ? current_free_match : bigger_space;
            current_free_match = 0;
        }
    }
    bigger_space = (bigger_space < current_free_match) ? current_free_match : bigger_space;
    return (bigger_space * 8);
}

void set_bigger_space(rnb_node_t *to_alloc, size_t nbr_of_match, size_t where)
{
    char *bit_table = (char *) ((malloc_t *)(to_alloc)->data)->data;
    size_t bit_table_size = (((malloc_t *)(to_alloc)->data)->bit_table_size) * 8;

    to_alloc->number = (int) get_bigger_space(bit_table, bit_table_size, where, nbr_of_match);
}

void *allocate_mem(size_t size, rnb_node_t *to_alloc)
{
    char *bit_table = (char *) ((malloc_t *)(to_alloc)->data)->data;
    size_t bit_table_size = (((malloc_t *)(to_alloc)->data)->bit_table_size) * 8;
    size_t bit_to_find = (size / 8) + ((size % 8 == 0) ? 0 : 1);
    size_t current_free_match = 0;
    size_t nbr_of_match = 0;
    size_t i = 0;

    for (; i < bit_table_size; i++) {
        if (get_good_byte(i, bit_table) == 0) {
            current_free_match++;
        } else {
            nbr_of_match = (nbr_of_match < current_free_match) ? current_free_match : nbr_of_match;
            current_free_match = 0;
        }
        if (current_free_match == bit_to_find) {
            i++;
            break;
        }
    }
    set_bit_used(i - bit_to_find, bit_to_find, bit_table);
    set_bigger_space(to_alloc, nbr_of_match, i);
    *(unsigned int *) (((void *) bit_table) + (bit_table_size / 8) + ((i - bit_to_find) * 8)) = (unsigned int) bit_to_find;
    return ((void *) bit_table) + (bit_table_size / 8) + ((i - bit_to_find) * 8) + 4;
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
    size += 4;
    if (*head == 0x0) {
        if (create_pages(size, head) == 1)
            return (NULL);
    }
    allocable_mem = get_allocable_page(head, size);

    if (allocable_mem == NULL)
        return (NULL);
    void *tst = allocate_mem(size, allocable_mem);
    /*print_address_hex(tst);
    my_putchar('\n');*/
    return (tst);
}


rnb_node_t *get_free_page(rnb_node_t **head, void *ptr)
{
    /*my_putstr("Head rnb: ");
    print_address_hex(*head);
    my_putchar('\n');
    my_putstr("Ptr to free: ");
    print_address_hex(ptr);
    my_putchar('\n');*/
    rnb_node_t *matchs = match_func_prefix(*head, ptr, (int (*)(rnb_node_t *root, void *data)) &match_ptr);
    /*my_putstr("Matchs: ");
    print_address_hex(matchs);
    my_putchar('\n');*/
    return (matchs);
}

unsigned int get_alloc_size(void *ptr)
{
    return (*(unsigned int *) (((void *) ptr) - 4));
}

void free(void *ptr)
{
    //write(1, "ccc", 3);
    rnb_node_t *container;
    unsigned int alloc_size = 0;
    void *true_ptr = NULL;
    void *bit_table_end_ptr = NULL;
    size_t where = 0;

    if (ptr == NULL)
        return;
    container = get_free_page(get_rnb_head(), ptr);
    //write(1, "kkk", 3);
    if (container == NULL)
        return;
    //write(1, "mmm", 3);
    alloc_size = get_alloc_size(ptr);
    true_ptr = ptr - 4;
    bit_table_end_ptr = ((malloc_t *) container->data)->data + ((malloc_t *) container->data)->bit_table_size;
    where = true_ptr - bit_table_end_ptr;
    set_bit_unused(where / 8, alloc_size, ((malloc_t *) container->data)->data);
    set_bigger_space(container, 0, 0);
    //write(1, "jjj", 3);
}

void *realloc(void *ptr, size_t size)
{
    //write(1, "mdr", 3);
    void *return_ptr;
    unsigned alloc_size = 0;

    //my_put_nbr((int) size);
    //write(1, "\n", 1);
    if (ptr == NULL) {
        return (malloc(size));
    }
    if (get_free_page(get_rnb_head(), ptr) == NULL)
        return (malloc(size));
    else if (size == 0) {
        free(ptr);
        return (NULL);
    }

    //write(1, "\n", 1);
    //write(1, "lol", 3);

    return_ptr = malloc(size);
    if (return_ptr == NULL)
        return NULL;
    //write(1, "ttt", 3);
    alloc_size = get_alloc_size(ptr) * 8;
    memcpy(return_ptr, ptr, (alloc_size > (get_alloc_size(return_ptr) * 8)) ? size : alloc_size);
    //write(1, "iii", 3);
    free(ptr);
    return (return_ptr);
}