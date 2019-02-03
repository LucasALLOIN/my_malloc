/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_chield
*/

#include <stdio.h>
#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

rnb_node_t *get_chield_node(rnb_node_t *node, char side)
{
    if (node == NULL)
        return (NULL);
    if (side == 'R')
        return (node->right);
    if (side == 'L')
        return (node->left);
    return (NULL);
}

rnb_node_t *get_little_chield_node(rnb_node_t *node, char side0, char side1)
{
    rnb_node_t *chield = get_chield_node(node, side0);
    return (get_chield_node(chield, side1));
}