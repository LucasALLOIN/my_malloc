/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_dump
*/

#include <stdio.h>
#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

void dump_node(rnb_node_t *node)
{
    char *str = NULL;

    if (node == NULL) {
        printf("NULL\n");
        return;
    }
    printf("Node : %d\n", node->number);
    printf("Color : %s\n", (node->color == RED) ? "RED" : "BLACK");
    asprintf(&str, "%p", node->left);
    printf("Left : %s\n", (node->left == NULL) ? "NULL" : str);
    str = NULL;
    asprintf(&str, "%p", node->right);
    printf("Right : %s\n\n", (node->right == NULL) ? "NULL" : str);
}

void default_print(rnb_node_t *node)
{
    if (node == NULL)
        return;
    printf("-----------------------\n");
    printf("| node->number = %d |\n", node->number);
    printf("| node->color = %s |\n", (node->color == RED ? "RED" : "BLACK"));
    printf("-----------------------\n");
}

void apply_func_prefix(rnb_node_t *root, void (*func)(rnb_node_t *node))
{
    if (root == NULL)
        return;
    func(root);
    if (root->right != NULL) {
        (apply_func_prefix(root->right, func));
    }
    if (root->left != NULL) {
        (apply_func_prefix(root->left, func));
    }
    return;
}

void default_print_step(rnb_node_t *node, int step)
{
    if (node == NULL)
        return;
    printf("-------- Step : %d --------\n", step);
    printf("| node->number = %d |\n", node->number);
    printf("| node->color = %s |\n", (node->color == RED ? "RED" : "BLACK"));
    printf("-----------------------\n");
}

void apply_func_prefix_step(rnb_node_t *root, void (*func)
(rnb_node_t *node, int step), int step)
{
    if (root == NULL)
        return;
    func(root, step);
    if (root->right != NULL) {
        (apply_func_prefix_step(root->right, func, step + 1));
    }
    if (root->left != NULL) {
        (apply_func_prefix_step(root->left, func, step + 1));
    }
    return;
}

void dump_violation_error(rnb_violation_error_t *error)
{
    if (error->_type == CONSECUTIVE_RED) {
        printf("CONSECUTIVE_RED\n");
        printf("SHAPE : %s\n",
        (get_shape(error->_root, error->_chield) == LINE) ? "LINE" : "TRIANGL");
        printf("chield :\n");
        dump_node(error->_chield);
        printf("father :\n");
        dump_node(error->_father);
        printf("grandfather :\n");
        dump_node(error->_grandfather);
        printf("uncle :\n");
        dump_node(error->_uncle);
    } else if (error->_type == TWO_MUCH_BLACK_NODE) {
        printf("TWO_MUCH_BLACK_NODE\n");
        printf("SHAPE : %s",
        (get_shape(error->_root, error->_chield) == LINE) ? "LINE" : "TRIANGL");
        printf(" :\n");
        dump_node(error->_chield);
    } else if (error->_type == ROOT_RED) {
        printf("ROOT RED\n");
    }
}