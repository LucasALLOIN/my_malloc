/*
** EPITECH PROJECT, 2019
** source
** File description:
** violation
*/

#ifndef VIOLATION_H_
#define VIOLATION_H_
#include "rnb_trees.h"

typedef enum rnb_violation_type
{
    ROOT_RED,
    UNCLE_RED,
    FATHER_CHIELD_RED_STRUCT_TRIANGLE,
    FATHER_CHIELD_RED_STRUCT_LINE,
    NO_ERROR
}rnb_violation_type_t;

typedef struct rnb_violation_error
{
    rnb_node_t **_root;
    rnb_node_t *_uncle;
    rnb_node_t *_grandFather;
    rnb_node_t *_father;
    rnb_node_t *_chield;
    rnb_violation_type_t _type;
}rnb_violation_error_t;

rnb_violation_type_t is_violation_root_red(rnb_node_t **root);
rnb_violation_type_t get_violation_type_double_red(rnb_node_t **root, rnb_node_t *chield);
rnb_violation_type_t is_violation_double_red(rnb_node_t **root, rnb_node_t *node);
int get_number_of_black_nodes(rnb_node_t *root, int value, rnb_node_t **err);

#endif /* !VIOLATION_H_ */
