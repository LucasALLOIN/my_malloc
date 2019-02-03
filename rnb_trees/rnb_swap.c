/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_swap
*/

#include <stdio.h>
#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

void swap(rnb_node_t *swap, rnb_node_t *node)
{
    swap->number = node->number;
    swap->data = node->data;
}