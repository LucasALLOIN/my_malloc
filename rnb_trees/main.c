/*
** EPITECH PROJECT, 2019
** source
** File description:
** main
*/

#include <unistd.h>
#include "rnb_trees.h"

int main()
{
    rnb_node_t *rnb = NULL;
    int k = 43;
    int k2 = 15;
    micro_insert(&rnb, 1, &k);
    micro_insert(&rnb, 2, &k2);
    micro_insert(&rnb, 3, &k);
    micro_insert(&rnb, 0, &k);
    apply_func_prefix_step(rnb, &default_print_step, 0);
    rnb_node_t *grand = get_grandfather(rnb, 3);
    rnb_node_t *father = get_father(rnb, 3);
    printf("%s\n", (grand == rnb) ? "OK" : "ERROR");
    if (father != NULL)
        printf("%d\n", father->number);
    return (0);
}