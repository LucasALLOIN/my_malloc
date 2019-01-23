/*
** EPITECH PROJECT, 2019
** source
** File description:
** violation
*/

#include <unistd.h>
#include "rnb_trees.h"
#include "violation.h"

rnb_violation_type_t isViolationRootRed(rnb_node_t **root)
{
    if (root != NULL) {
        if (*root != NULL) {
            if ((*root)->color == RED)
                return (ROOT_RED);
        }
    }
    return (NO_ERROR);
}

rnb_violation_type_t isViolationDoubleRed(rnb_node_t **root, rnb_node_t *grandfather)
{
    rnb_node_t *father = get_chield_node(grandfather, 'R');
    if (father == NULL) {
        
    }
}

rnb_violation_type_t getViolation(rnb_node_t **root, rnb_node_t *grandfather)
{

}

int isViolation()
{

}