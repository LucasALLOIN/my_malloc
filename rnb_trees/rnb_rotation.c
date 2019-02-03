/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_rotation
*/

#include <stdio.h>
#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

void fix_rotation(rnb_node_t *grand,
rnb_node_t *father, rnb_node_t *chield)
{
    if (grand != NULL) {
        if (grand->left == father)
            grand->left = chield;
        if (grand->right == father)
            grand->right = chield;
    }
}

int check_father_before_rotation(rnb_node_t *father, rnb_node_t *chield,
char side)
{
    if (father != NULL) {
        if (father->left == chield && side == 'L')
            return (1);
        if (father->right == chield && side == 'R')
            return (1);
    }
    return (0);
}

void rotate_right(rnb_node_t **root, int number)
{
    rnb_node_t *grand = NULL;
    rnb_node_t *father = NULL;
    rnb_node_t *node = NULL;
    rnb_node_t *tmp = NULL;

    if (root == NULL)
        return;
    node = get_node(*root, number);
    father = get_father(*root, number);
    grand = get_grandfather(*root, number);
    if (father == NULL || node == NULL ||
    !check_father_before_rotation(father, node, 'R'))
        return;
    tmp = node->left;
    node->left = father;
    father->right = tmp;
    fix_rotation(grand, father, node);
    if (*root == father)
        *root = node;
}

void rotate_left(rnb_node_t **root, int number)
{
    rnb_node_t *grand = NULL;
    rnb_node_t *father = NULL;
    rnb_node_t *node = NULL;
    rnb_node_t *tmp = NULL;

    if (root == NULL)
        return;
    node = get_node(*root, number);
    father = get_father(*root, number);
    grand = get_grandfather(*root, number);
    if (father == NULL || node == NULL ||
    !check_father_before_rotation(father, node, 'L'))
        return;
    tmp = node->right;
    node->right = father;
    father->left = tmp;
    fix_rotation(grand, father, node);
    if (*root == father)
        *root = node;
}

void rotate(rnb_node_t **root, int number)
{
    rnb_node_t *father = get_father(*root, number);
    rnb_node_t *chield = get_node(*root, number);
    if (father != NULL) {
        if (father->left == chield)
            rotate_left(root, number);
        else if (father->right == chield)
            rotate_right(root, number);
    }
}