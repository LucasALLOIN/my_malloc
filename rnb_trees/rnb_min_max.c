/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_min_max
*/

#include <stdio.h>
#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

rnb_node_t *get_max(rnb_node_t *root)
{
    if (root == NULL)
        return (NULL);
    if (root->right == NULL)
        return (root);
    return (get_max(root->right));
}

rnb_node_t *get_min(rnb_node_t *root)
{
    if (root == NULL)
        return (NULL);
    if (root->left == NULL)
        return (root);
    return (get_min(root->left));
}