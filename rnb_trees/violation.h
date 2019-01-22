/*
** EPITECH PROJECT, 2019
** source
** File description:
** violation
*/

#ifndef VIOLATION_H__H_

#include "rnb_trees.h"

typedef enum rnb_violation_type
{
    ROOT_RED,
    UNCLE_RED,
    FATHER_CHIELD_RED_STRUCT_TRIANGLE,
    FATHER_CHIELD_RED_STRUCT_LINE
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


#endif /* !VIOLATION_H_ */
