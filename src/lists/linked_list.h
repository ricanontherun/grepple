#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef unsigned short bool;
#define false 0
#define true 1

struct node {
    char *val;
    bool tail;
    struct node *next;
};

typedef struct node node;

typedef struct {
    node *head;
} linked_list;

extern linked_list *ll_new();
extern void ll_append(linked_list *list, char *val);
extern int ll_node_exists(linked_list *list, char *val);
extern void ll_free_list(linked_list *list);
extern long ll_list_length(linked_list *list);

#endif
