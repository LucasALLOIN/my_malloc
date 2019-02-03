/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_shape
*/

#include <unistd.h>
#include <stdio.h>
#include "rnb_trees.h"
#include "violation.h"

rnb_shape_t get_shape(rnb_node_t **root, rnb_node_t *chield)
{
    rnb_node_t *grand = NULL;
    rnb_node_t *father = NULL;

    if (chield != NULL) {
        grand = get_grandfather(*root, chield->number);
        father = get_father(*root, chield->number);
        if (grand != NULL && father != NULL) {
            if ((grand->left == father && father->right == chield)
            || (grand->right == father && father->left == chield))
                return (TRIANGLE);
            else {
                return (LINE);
            }
        }
    }
    return (UNKNOWN);
}