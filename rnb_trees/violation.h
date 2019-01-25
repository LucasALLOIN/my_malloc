/*
** EPITECH PROJECT, 2019
** source
** File description:
** violation
*/

#ifndef VIOLATION_H_
#define VIOLATION_H_
#include "rnb_trees.h"

typedef enum rnb_shape
{
    LINE,
    TRIANGLE,
    UNKNOWN
}rnb_shape_t;

typedef enum rnb_violation_type
{
    ROOT_RED,
    UNCLE_RED,
    CONSECUTIVE_RED,
    TWO_MUCH_BLACK_NODE,
    NO_ERROR
}rnb_violation_type_t;

typedef struct rnb_violation_error
{
    rnb_node_t **_root;
    rnb_node_t *_uncle;
    rnb_node_t *_grandfather;
    rnb_node_t *_father;
    rnb_node_t *_chield;
    rnb_violation_type_t _type;
}rnb_violation_error_t;

rnb_violation_type_t is_violation_root_red(rnb_node_t **root);
rnb_violation_type_t get_violation_type_double_red(rnb_node_t **root, rnb_node_t *chield);
rnb_violation_type_t is_violation_double_red(rnb_node_t **root, rnb_node_t *node);
int get_number_of_black_nodes(rnb_node_t *root, int value, rnb_node_t **err);


rnb_node_t *get_double_red_violation(rnb_node_t **root_real, rnb_node_t *root);
void preset_error(rnb_node_t **root, rnb_violation_error_t *error, rnb_node_t *chield);
int get_next_violation(rnb_node_t **root, rnb_violation_error_t *error);
rnb_shape_t get_shape(rnb_node_t **root, rnb_node_t *chield);

void fix_consecutive_red(rnb_node_t **root, rnb_violation_error_t *error);
void fix_violation(rnb_violation_error_t *error);

void dump_violation_error(rnb_violation_error_t *error);

#endif /* !VIOLATION_H_ */
