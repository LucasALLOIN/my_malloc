/*
** EPITECH PROJECT, 2019
** source
** File description:
** rnb_trees
*/

#include <stdio.h>
#include <unistd.h>
#include "rnb_trees.h"

rnb_node_t *create_element(int number, void *data)
{
    rnb_node_t *node = sbrk(ALIGN(sizeof(rnb_node_t)));
    node->number = number;
    node->color = RED;
    node->data = data;
    node->right = NULL;
    node->left = NULL;
    return (node);
}

rnb_node_t *get_chield_node(rnb_node_t *node, char side)
{
    if (node == NULL)
        return (NULL);
    if (side == 'R')
        return (node->right);
    if (side == 'L')
        return (node->left);
    return (NULL);
}

rnb_node_t *get_little_chield_node(rnb_node_t *node, char side0, char side1)
{
    rnb_node_t *chield = get_chield_node(node, side0);
    return (get_chield_node(chield, side1));
}

rnb_node_t *append_chield(rnb_node_t *node, rnb_node_t *chield, char side)
{
    if (node == NULL)
        return (NULL);
    if (side == 'R')
        node->right = chield;
    if (side == 'L') {
        node->left = chield;
    }
    return (chield);
}

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
    /*if (root == NULL);
        return (NULL);*/
    if ((*root) == NULL) {
        *root = create_element(number, data);
        (*root)->color = BLACK;
        return (*root);
    }
    return micro_insert_recursivity(*root, number, data);
}

void default_print(rnb_node_t *node)
{
    if (node == NULL)
        return;
    printf("-----------------------\n");
    printf("| node->number = %d |\n", node->number);
    printf("| node->color = %s |\n", (node->color == RED ? "RED" : "BLACK"));
    printf("-----------------------\n");
}

void apply_func_prefix(rnb_node_t *root, void (*func)(rnb_node_t *node))
{
    if (root == NULL)
        return;
    func(root);
    if (root->right != NULL) {
        (apply_func_prefix(root->right, func));
    }
    if (root->left != NULL) {
        (apply_func_prefix(root->left, func));
    }
    return;
}

int match(rnb_node_t *node, int *number)
{
    if (number != NULL) {
        if (node->number >= (*number))
            return (1);
    }
    return (0);
}

rnb_node_t *match_func_prefix(rnb_node_t *root, void *data, int (*func)(rnb_node_t *node, void *data))
{
    rnb_node_t *tmp = NULL;
    if (root == NULL)
        return (NULL);
    if (func(root, data)) {
        return (root);
    }
    if (root->right != NULL) {
        tmp = (match_func_prefix(root->right, data, func));
        if (tmp != NULL)
            return (tmp);
    }
    if (root->left != NULL) {
        tmp = (match_func_prefix(root->left, data, func));
        if (tmp != NULL)
            return (tmp);

    }
    return (NULL);
}

void default_print_step(rnb_node_t *node, int step)
{
    if (node == NULL)
        return;
    printf("-------- Step : %d --------\n", step);
    printf("| node->number = %d |\n", node->number);
    printf("| node->color = %s |\n", (node->color == RED ? "RED" : "BLACK"));
    printf("-----------------------\n");
}

void apply_func_prefix_step(rnb_node_t *root, 
    void (*func)(rnb_node_t *node, int step), int step)
{
    if (root == NULL)
        return;
    func(root, step);
    if (root->right != NULL) {
        (apply_func_prefix_step(root->right, func, step + 1));
    }
    if (root->left != NULL) {
        (apply_func_prefix_step(root->left, func, step + 1));
    }
    return;
}

rnb_node_t *get_grandfather(rnb_node_t *root, int number)
{
    rnb_node_t *father = NULL;
    rnb_node_t *chield = NULL;

    if (root != NULL) {
        father = (root->number <= number) ? get_chield_node(root, 'R') : get_chield_node(root, 'L');
    }
    if (father != NULL) {
        chield = (father->number <= number) ? get_chield_node(father, 'R') : get_chield_node(father, 'L');
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
        chield = (root->number <= number) ? get_chield_node(root, 'R') : get_chield_node(root, 'L');
    }
    if (chield != NULL) {
        if (chield->number == number)
            return (root);
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

int check_father_before_rotation(rnb_node_t *father, rnb_node_t *chield, char side)
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
    if (father == NULL || node == NULL || !check_father_before_rotation(father, node, 'R'))
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
    if (father == NULL || node == NULL || !check_father_before_rotation(father, node, 'L'))
        return;
    tmp = node->right;
    node->right = father;
    father->left = tmp;
    fix_rotation(grand, father, node);
    if (*root == father)
        *root = node;
}

void colorflip(rnb_node_t *parent)
{
    if (parent == NULL)
        return;
    parent->color = (parent->color == RED) ? BLACK : RED;
    if (parent->left != NULL)
        parent->left->color = (parent->color == RED) ? BLACK : RED;
    if (parent->right != NULL)
        parent->right->color = (parent->color == RED) ? BLACK : RED;
}