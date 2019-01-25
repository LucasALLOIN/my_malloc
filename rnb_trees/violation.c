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

rnb_violation_type_t is_violation_double_red(rnb_node_t **root, rnb_node_t *node)
{
    rnb_node_t *father = NULL;
    if (node == NULL)
        return (NO_ERROR);
    father = get_father(*root, node->number);
    if (node->color == RED && father != NULL) {
        return ((father->color == RED) ? CONSECUTIVE_RED : NO_ERROR);
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
    if (ret == -1 && num2 != -1 && num != -1) {
        *err = (num > num2) ? root->left : root->right;
    }
    return (ret);
}

rnb_node_t *get_double_red_violation(rnb_node_t **root_real, rnb_node_t *root)
{
    rnb_node_t *node = NULL;

    if (root == NULL)
        return (NULL);
    if (is_violation_double_red(root_real, root) != NO_ERROR)
        return (root);
    if (root->left != NULL)
        node = get_double_red_violation(root_real, root->left);
    if (root->right != NULL && node == NULL)
        node = get_double_red_violation(root_real, root->right);
    return (node);
}

void preset_error(rnb_node_t **root, rnb_violation_error_t *error, rnb_node_t *chield)
{
    if (chield != NULL) {
        error->_root = root;
        error->_type = NO_ERROR;
        error->_chield = chield;
        error->_father = get_father(*root, chield->number);
        error->_grandfather = get_grandfather(*root, chield->number);
        error->_uncle = get_uncle(*root, chield->number);
        return;
    } else {
        error->_root = root;
        error->_type = NO_ERROR;
        error->_chield = NULL;
        error->_father = NULL;
        error->_grandfather = NULL;
        error->_uncle = NULL;
    }
}

int get_next_violation(rnb_node_t **root, rnb_violation_error_t *error)
{
    rnb_node_t *node = NULL;
    if (is_violation_root_red(root) != NO_ERROR) {
        preset_error(root, error, NULL);
        error->_type = ROOT_RED;
        return (1);
    }
    if ((node = get_double_red_violation(root, *root)) != NULL) {
        preset_error(root, error, node);
        error->_type = is_violation_double_red(root, node);
        return (1);
    }
    if (get_number_of_black_nodes(*root, 0, &node) == -1) {
        preset_error(root, error, node);
        error->_type = TWO_MUCH_BLACK_NODE;
        return (1);
    }
    preset_error(root, error, NULL);
    return (0);
}

void fix_violation(rnb_node_t **root, rnb_violation_error_t *error)
{

}