/*
** EPITECH PROJECT, 2019
** source
** File description:
** violation
*/

#include <unistd.h>
#include <stdio.h>
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

int get_number_of_blacks_node_split(rnb_node_t *root, int num, int num2,
rnb_node_t **err)
{
    int ret = 0;
    ret = ((num2 == num) ? num : -1);
    if (ret == -1 && num2 != -1 && num != -1) {
        *err = (num > num2) ? root->left : root->right;
    }
    return (ret);
}

int get_number_of_black_nodes(rnb_node_t *root, int value, rnb_node_t **err)
{
    int num = 0;
    int num2 = 0;
    int val = 0;

    if (root == NULL)
        return (-1);
    if (root->color == BLACK)
        val = 1;
    if (root->left == NULL && root->right == NULL)
        return (value + val);
    if (root->left != NULL)
        num = get_number_of_black_nodes(root->left, value + val, err);
    if (root->right != NULL)
        num2 = get_number_of_black_nodes(root->right, value + val, err);
    if (root->right == NULL && root->left != NULL)
        return (num);
    if (root->left == NULL && root->right != NULL)
        return (num2);
    return (get_number_of_blacks_node_split(root, num, num2, err));
}

void preset_error(rnb_node_t **root, rnb_violation_error_t *error,
rnb_node_t *chield)
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

void dump_violation_error(rnb_violation_error_t *error)
{
    if (error->_type == CONSECUTIVE_RED) {
        printf("CONSECUTIVE_RED\n");
        printf("SHAPE : %s\n",
        (get_shape(error->_root, error->_chield) == LINE) ? "LINE" : "TRIANGL");
        printf("chield :\n");
        dump_node(error->_chield);
        printf("father :\n");
        dump_node(error->_father);
        printf("grandfather :\n");
        dump_node(error->_grandfather);
        printf("uncle :\n");
        dump_node(error->_uncle);
    } else if (error->_type == TWO_MUCH_BLACK_NODE) {
        printf("TWO_MUCH_BLACK_NODE\n");
        printf("SHAPE : %s",
        (get_shape(error->_root, error->_chield) == LINE) ? "LINE" : "TRIANGL");
        printf(" :\n");
        dump_node(error->_chield);
    } else if (error->_type == ROOT_RED) {
        printf("ROOT RED\n");
    }
}