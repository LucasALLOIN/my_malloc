/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_match
*/

#include <stdio.h>
#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

int match(rnb_node_t *node, int *number)
{
    if (number != NULL) {
        if (node->number >= (*number))
            return (1);
    }
    return (0);
}

rnb_node_t *match_func_prefix(rnb_node_t *root, void *data, int (*func)(rnb_node_t *node, void *data))
{
    rnb_node_t *tmp = NULL;
    if (root == NULL)
        return (NULL);
    if (func(root, data)) {
        return (root);
    }
    if (root->right != NULL) {
        tmp = (match_func_prefix(root->right, data, func));
        if (tmp != NULL)
            return (tmp);
    }
    if (root->left != NULL) {
        tmp = (match_func_prefix(root->left, data, func));
        if (tmp != NULL)
            return (tmp);

    }
    return (NULL);
}