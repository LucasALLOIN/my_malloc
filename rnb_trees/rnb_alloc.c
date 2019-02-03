/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_alloc
*/

#include <stdio.h>
#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

rnb_node_t *create_element(int number, void *data)
{
    rnb_node_t *node = sbrk(ALIGN(sizeof(rnb_node_t)));
    node->number = number;
    node->color = RED;
    node->data = data;
    node->right = NULL;
    node->left = NULL;
    return (node);
}

rnb_node_t *append_chield(rnb_node_t *node, rnb_node_t *chield, char side)
{
    if (node == NULL)
        return (NULL);
    if (side == 'R')
        node->right = chield;
    if (side == 'L') {
        node->left = chield;
    }
    return (chield);
}