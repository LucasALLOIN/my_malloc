/*
** EPITECH PROJECT, 2019
** source
** File description:
** violation
*/

#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

rnb_violation_type_t is_violation_root_red(rnb_node_t **root)
{
    if (root != NULL) {
        if (*root != NULL) {
            if ((*root)->color == RED)
                return (ROOT_RED);
        }
    }
    return (NO_ERROR);
}

rnb_violation_type_t get_violation_type_double_red(rnb_node_t **root, rnb_node_t *chield)
{
    rnb_node_t *grand = NULL;
    rnb_node_t *father = NULL;
    
    
    if (chield != NULL) {
        grand = get_grandfather(*root, chield);
        father = get_father(*root, chield);
        if (grand != NULL && father != NULL) {
            if ((grand->left == father && father->right == chield) || (grand->right == father && father->left == chield))

                return (FATHER_CHIELD_RED_STRUCT_TRIANGLE);
            else {
                return (FATHER_CHIELD_RED_STRUCT_LINE); 
            }
        }
    }
    return (NO_ERROR);
}

rnb_violation_type_t is_violation_double_red(rnb_node_t **root, rnb_node_t *node)
{
    rnb_node_t *father = get_father(*root, node);
    if (node == NULL)
        return (NO_ERROR);
    if (node->color == RED && father != NULL) {
        return ((father->color == RED) ? get_violation_type_double_red(root, node) : NO_ERROR);
    }
    return (NO_ERROR);
}

size_t get_number_of_black_nodes(rnb_node_t *root, size_t value)
{
    size_t num = 0;
    size_t num2 = 0;
    size_t val = 0;
    if (root == NULL)
        return (NULL);
    if (root->color)
        val = 1;

    if (root->left != NULL)
        num = get_number_of_black_nodes(root->left, value + val);
    if (root->right != NULL)
        num2 = get_number_of_black_nodes(root->right, value + val);
    return ((num2 == num) ? num : (size_t) -1);
}

rnb_violation_type_t get_violation(rnb_node_t **root, rnb_node_t *node)
{

}

void fixViolation(rnb_node_t **root, rnb_node_t *chield, rnb_violation_type_t type)
{

}