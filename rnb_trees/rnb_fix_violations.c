/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_fix_violations
*/

#include <unistd.h>
#include <stdio.h>
#include "rnb_trees.h"
#include "violation.h"

int get_next_violation(rnb_node_t **root, rnb_violation_error_t *error)
{
    rnb_node_t *node = NULL;
    if (is_violation_root_red(root) != NO_ERROR) {
        preset_error(root, error, NULL);
        error->_type = ROOT_RED;
        return (1);
    }
    if ((node = get_double_red_violation(root, *root)) != NULL) {
        preset_error(root, error, node);
        error->_type = is_violation_double_red(root, node);
        return (1);
    }
    if (get_number_of_black_nodes(*root, 0, &node) == -1) {
        preset_error(root, error, node);
        error->_type = TWO_MUCH_BLACK_NODE;
        return (1);
    }
    preset_error(root, error, NULL);
    return (0);
}

void fix_violation(rnb_violation_error_t *error)
{
    rnb_node_t *node = *(error->_root);

    if (error->_type == NO_ERROR)
        return;
    if (error->_type == ROOT_RED)
        node->color = BLACK;
    if (error->_type == CONSECUTIVE_RED) {
        fix_consecutive_red(error->_root, error);
    }
    if (error->_type == TWO_MUCH_BLACK_NODE) {
        if (error->_chield != NULL)
            rotate(error->_root, error->_chield->number);
        printf("ERROR::_chield : %d\n", error->_chield->number);
        colorflip(error->_chield);
    }
}

void fix_all_violations(rnb_node_t **root)
{
    rnb_violation_error_t error;

    while (get_next_violation(root, &error))
        fix_violation(&error);
}