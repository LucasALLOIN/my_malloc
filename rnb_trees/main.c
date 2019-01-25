/*
** EPITECH PROJECT, 2019
** source
** File description:
** main
*/

#include <unistd.h>
#include <stdio.h>
#include "rnb_trees.h"
#include "violation.h"

int main()
{
    rnb_node_t *rnb = NULL;
    int k = 43;
    int k2 = 15;
/*    micro_insert(&rnb, 1, &k);
    micro_insert(&rnb, 2, &k2);
    micro_insert(&rnb, 3, &k);
    micro_insert(&rnb, 0, &k);
    apply_func_prefix_step(rnb, &default_print_step, 0);
    rnb_node_t *grand = get_grandfather(rnb, 3);
    rnb_node_t *father = get_father(rnb, 3);
    rnb_node_t *uncle = get_uncle(rnb, 3);
    rnb_node_t *node = get_node(rnb, 3);
    printf("%s\n", (grand == rnb) ? "OK" : "ERROR");
    if (father != NULL)
        printf("%d\n", father->number);
    if (uncle != NULL)
        printf("%d\n", uncle->number);
    if (node != NULL)
        printf("%d\n", node->number);

        rnb_node_t *rnb2 = NULL;
        micro_insert(&rnb2, 4, NULL);
        micro_insert(&rnb2, 6, NULL);
        micro_insert(&rnb2, 8, NULL);
        apply_func_prefix_step(rnb2, &default_print_step, 0);
        rotate_left(&rnb2, 6);
        apply_func_prefix_step(rnb2, &default_print_step, 0);
        rotate_right(&rnb2, 6);
        apply_func_prefix_step(rnb2, &default_print_step, 0);
*/
/*       rnb_node_t *rnb3 = NULL;
        micro_insert(&rnb3, 10, NULL);
        micro_insert(&rnb3, 5, NULL);
        micro_insert(&rnb3, 2, NULL);
        micro_insert(&rnb3, 8, NULL);
        micro_insert(&rnb3, 9, NULL);
        micro_insert(&rnb3, 6, NULL);
        micro_insert(&rnb3, 12, NULL);
        //rotate_right(&rnb3, 5);
        //colorflip(rnb3);
        apply_func_prefix_step(rnb3, &default_print_step, 0);
        int z = 8;
        rnb_node_t *err = NULL;
        rnb_node_t *matchs = match_func_prefix(rnb3, &z, (int (*)(rnb_node_t *root, void *data)) &match);
        if (matchs != NULL)
            printf("match = %d\n", matchs->number);
        printf("nb black nodes = %d\n", get_number_of_black_nodes(rnb3, 0, &err));
        get_node(rnb3, 12)->color = BLACK;
        printf("nb black nodes = %d\n", get_number_of_black_nodes(rnb3, 0, &err));
        if (err != NULL)
            printf("err parent = %d\n", err->number);
        get_node(rnb3, 5)->color = BLACK;
        printf("nb black nodes = %d\n", get_number_of_black_nodes(rnb3, 0, &err));
        get_node(rnb3, 9)->color = BLACK;
        printf("nb black nodes = %d\n", get_number_of_black_nodes(rnb3, 0, &err));
        if (err != NULL)
            printf("err parent = %d\n", err->number);

        printf("+++++++++++++++++++++++++++++++=\n");
        apply_func_prefix_step(rnb3, &default_print_step, 0);
        rnb_violation_type_t type = NO_ERROR;
    
        get_node(rnb3, 9)->color = RED;
        get_node(rnb3, 10)->color = RED;
        type = is_violation_root_red(&rnb3);
        printf("%s\n", (type == ROOT_RED) ? "OK" : "ERROR");
        get_node(rnb3, 10)->color = BLACK;
        type = is_violation_double_red(&rnb3, get_node(rnb3, 9));
        if (type != NO_ERROR) {
            printf("%s\n", (type == FATHER_CHIELD_RED_STRUCT_LINE) ? "RED LINE" : "RED TRIANGLE");
        }
        type = is_violation_double_red(&rnb3, get_node(rnb3, 6));
        if (type != NO_ERROR) {
            printf("%s\n", (type == FATHER_CHIELD_RED_STRUCT_LINE) ? "RED LINE" : "RED TRIANGLE");
        } */
        rnb_node_t *rnb4 = NULL;
        micro_insert(&rnb4, 3, NULL);
        micro_insert(&rnb4, 1, NULL);
        micro_insert(&rnb4, 5, NULL);
        micro_insert(&rnb4, 7, NULL);
        //micro_insert(&rnb4, 6, NULL);
        //apply_func_prefix_step(rnb4, &default_print_step, 0);
        //rotate_right(&rnb4, 5);
        //rotate_left(&rnb4, 3);
        //rotate(&rnb4, 6);
        //rotate(&rnb4, 6);

        apply_func_prefix_step(rnb4, &default_print_step, 0);
        rnb_violation_error_t error;
        printf("%d\n", get_next_violation(&rnb4, &error));
        fix_violation(&error);
        apply_func_prefix_step(rnb4, &default_print_step, 0);
        dump_violation_error(&error);
    return (0);
}