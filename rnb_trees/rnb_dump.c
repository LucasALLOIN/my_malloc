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