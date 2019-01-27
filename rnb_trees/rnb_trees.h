/*
** EPITECH PROJECT, 2019
** source
** File description:
** rnb_trees
*/

#ifndef  _RNB_TREES_H_
#define _RNB_TREES_H_

#define ALIGN(x) (((((x)) >> 3) << 3) + 8)

typedef struct __attribute__((packed)) rnb_class
{
    void *(*constructor)();
    void *(*destructor)();
}rnb_class_t;

typedef enum rnb_node_color
{
    RED,
    BLACK
}rnb_node_color_t;

typedef struct __attribute__((packed)) rnb_node
{
    int number;
    rnb_node_color_t color;
    void *data;
    struct rnb_node *right;
    struct rnb_node *left;
}rnb_node_t;

typedef struct __attribute__((packed)) rnb_tree 
{
    rnb_class_t func;
    rnb_node_t *root;

    int (*right_rotate)(int number);
    int (*left_rotate)(int *number);
    int (*insert)(int number, void *data);
    int (*remove)(int number);
    int (*modify)(int number, void *data);
    rnb_node_t *(*get_node)(rnb_node_t *root, int number);
}rnb_tree_t;

int right_rotate(int number);
int left_rotate(int *number);
rnb_node_t *insert(rnb_node_t **root, int number, void *data);
int modify(int number, void *data);
rnb_node_t *get_node(rnb_node_t *root, int number);


rnb_node_t *create_element(int number, void *data);
rnb_node_t *get_chield_node(rnb_node_t *node, char side);
rnb_node_t *get_little_chield_node(rnb_node_t *node, char side0, char side1);
rnb_node_t *append_chield(rnb_node_t *node, rnb_node_t *chield, char side);
rnb_node_t *micro_insert_recursivity(rnb_node_t *node, 
                            int number, void *data);
rnb_node_t *micro_insert(rnb_node_t **root, int number, void *data);

void default_print(rnb_node_t *node);
void apply_func_prefix(rnb_node_t *root, void (*func)(rnb_node_t *node));
void default_print_step(rnb_node_t *node, int step);
void apply_func_prefix_step(rnb_node_t *root, void (*func)(rnb_node_t *node, int step), int step);
int match(rnb_node_t *node, int *number);
rnb_node_t *match_func_prefix(rnb_node_t *root, void *data, int (*func)(rnb_node_t *node, void *data));
rnb_node_t *get_grandfather(rnb_node_t *root, int number);
rnb_node_t *get_uncle(rnb_node_t *root, int number);
rnb_node_t *get_father(rnb_node_t *root, int number);

void colorflip(rnb_node_t *parent);
void rotate_right(rnb_node_t **root, int number);
void rotate_left(rnb_node_t **root, int number);
void rotate(rnb_node_t **root, int number);

void dump_node(rnb_node_t *node);
rnb_node_t *micro_remove(rnb_node_t **root, int number);

rnb_node_t *get_max(rnb_node_t *root);
rnb_node_t *get_min(rnb_node_t *root);
void swap(rnb_node_t *swap, rnb_node_t *node);
rnb_node_t *rnb_remove(rnb_node_t **root, int number);
int asprintf(char **strp, const char *fmt, ...);
#endif /* !RNB_TREES_H_ */
