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
            if ((grand->left == father && father->right == chield) || grand->right == father && father->left == chield)
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

rnb_violation_error_t is_violation_path(rnb_node_t **root)
{
    
}

rnb_violation_type_t get_violation(rnb_node_t **root, rnb_node_t *node)
{

}

int isViolation()
{

}