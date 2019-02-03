/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_consecutive_red
*/

#include <unistd.h>
#include <stdio.h>
#include "rnb_trees.h"
#include "violation.h"

rnb_violation_type_t is_violation_double_red(rnb_node_t **root,
rnb_node_t *node)
{
    rnb_node_t *father = NULL;
    if (node == NULL)
        return (NO_ERROR);
    father = get_father(*root, node->number);
    if (node->color == RED && father != NULL) {
        return ((father->color == RED) ? CONSECUTIVE_RED : NO_ERROR);
    }
    return (NO_ERROR);
}

rnb_node_t *get_double_red_violation(rnb_node_t **root_real, rnb_node_t *root)
{
    rnb_node_t *node = NULL;

    if (root == NULL)
        return (NULL);
    if (is_violation_double_red(root_real, root) != NO_ERROR)
        return (root);
    if (root->left != NULL)
        node = get_double_red_violation(root_real, root->left);
    if (root->right != NULL && node == NULL)
        node = get_double_red_violation(root_real, root->right);
    return (node);
}

rnb_node_color_t get_uncle_color(rnb_node_t *uncle)
{
    if (uncle == NULL)
        return (BLACK);
    return (uncle->color);
}

void fix_consecutive_red(rnb_node_t **root, rnb_violation_error_t *error)
{
    rnb_shape_t shape = get_shape(error->_root, error->_chield);
    rnb_node_color_t uncle_color = get_uncle_color(error->_uncle);
    if (uncle_color == BLACK) {
        if (shape == LINE && error->_father != NULL) {
            rotate(root, error->_father->number);
            colorflip(error->_father);
        }
        if (shape == TRIANGLE && error->_chield != NULL) {
            rotate(root, error->_chield->number);
        }
    } else if (uncle_color == RED) {
        colorflip(error->_grandfather);
    }
}