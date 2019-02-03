/*
** EPITECH PROJECT, 2019
** rnb_trees
** File description:
** rnb_family
*/

#include <stdio.h>
#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

rnb_node_t *get_grandfather(rnb_node_t *root, int number)
{
    rnb_node_t *father = NULL;
    rnb_node_t *chield = NULL;

    if (root != NULL) {
        father = (root->number <= number) ?
        get_chield_node(root, 'R') : get_chield_node(root, 'L');
    }
    if (father != NULL) {
        chield = (father->number <= number) ?
        get_chield_node(father, 'R') : get_chield_node(father, 'L');
    }
    if (chield != NULL) {
        if (chield->number == number)
            return (root);
        else
            return (get_grandfather(father, number));
    }
    return (NULL);
}

rnb_node_t *get_father(rnb_node_t *root, int number)
{
    rnb_node_t *chield = NULL;

    if (root != NULL) {
        chield = (root->number <= number) ?
        get_chield_node(root, 'R') : get_chield_node(root, 'L');
    }
    if (chield != NULL) {
        if (chield->number == number) {
            return (root);
        }
        else
            return (get_father(chield, number));
    }
    return (NULL);
}

rnb_node_t *get_uncle(rnb_node_t *root, int number)
{
    rnb_node_t *grand = get_grandfather(root, number);
    rnb_node_t *father = get_father(root, number);
    if (grand != NULL && father != NULL) {
        if (grand->right == father)
            return (grand->left);
        if (grand->left == father)
            return (grand->right);
    }
    return (NULL);
}

rnb_node_t *get_node(rnb_node_t *root, int number)
{
    rnb_node_t *tmp = NULL;
    if (root == NULL)
        return (NULL);
    if (root->number == number)
        return (root);
    if (root->left != NULL) {
        if ((tmp = get_node(root->left, number)) != NULL)
            return (tmp);
    }
    if (root->right != NULL) {
        if ((tmp = get_node(root->right, number)) != NULL)
            return (tmp);
    }
    return (NULL);
}