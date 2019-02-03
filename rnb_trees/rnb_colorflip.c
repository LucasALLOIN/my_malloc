/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_colorflip
*/

#include <stdio.h>
#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

void colorflip(rnb_node_t *parent)
{
    if (parent == NULL)
        return;
    parent->color = (parent->color == RED) ? BLACK : RED;
    if (parent->left != NULL)
        parent->left->color = (parent->color == RED) ? BLACK : RED;
    if (parent->right != NULL)
        parent->right->color = (parent->color == RED) ? BLACK : RED;
}