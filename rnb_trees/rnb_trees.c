/*
** EPITECH PROJECT, 2019
** source
** File description:
** rnb_trees
*/

#include <stdio.h>
#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

rnb_node_t *micro_insert_recursivity(rnb_node_t *node, 
                            int number, void *data)
{
    rnb_node_t *chield = create_element(number, data);

    if (node == NULL) {
        return (NULL);
    }
    if (node->number <= number) {
        if (node->right == NULL)
            return append_chield(node, chield, 'R');
        else
            return (micro_insert_recursivity(node->right, number, data));
    } else {
        if (node->left == NULL)
            return append_chield(node, chield, 'L');
        else
            return (micro_insert_recursivity(node->left, number, data));
    }
}

rnb_node_t *micro_insert(rnb_node_t **root, int number, void *data)
{
    if ((*root) == NULL) {
        *root = create_element(number, data);
        (*root)->color = BLACK;
        return (*root);
    }
    return micro_insert_recursivity(*root, number, data);
}

rnb_node_t *insert(rnb_node_t **root, int number, void *data)
{
    rnb_node_t *tmp = micro_insert(root, number, data);
    fix_all_violations(root);
    return (tmp);
}