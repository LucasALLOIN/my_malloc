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
        grand = get_grandfather(*root, chield->number);
        father = get_father(*root, chield->number);
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

rnb_violation_type_t get_struct(rnb_node_t **root, rnb_node_t *chield)
{
    rnb_node_t *grand = NULL;
    rnb_node_t *father = NULL;
    
    if (chield != NULL) {
        grand = get_grandfather(*root, chield->number);
        father = get_father(*root, chield->number);
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
    rnb_node_t *father = NULL;
    if (node == NULL)
        return (NO_ERROR);
    father = get_father(*root, node->number);
    if (node->color == RED && father != NULL) {
        return ((father->color == RED) ? get_violation_type_double_red(root, node) : NO_ERROR);
    }
    return (NO_ERROR);
}

int get_number_of_black_nodes(rnb_node_t *root, int value, rnb_node_t **err)
{
    int num = 0;
    int num2 = 0;
    int val = 0;
    int ret = 0;
    if (root == NULL)
        return (-1);
    if (root->color)
        val = 1;
    if (root->left == NULL && root->right == NULL)
        return (value + val);
    if (root->left != NULL)
        num = get_number_of_black_nodes(root->left, value + val, err);
    if (root->right != NULL)
        num2 = get_number_of_black_nodes(root->right, value + val, err);
    ret = ((num2 == num) ? num : -1);
    if (ret == -1 && num2 != -1 && num != -1)
        *err = root;
    return (ret);
}

rnb_violation_type_t get_violation(rnb_node_t **root, rnb_node_t *node)
{

}

void fixViolation(rnb_node_t **root, rnb_node_t *chield, rnb_violation_type_t type)
{

}