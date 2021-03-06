#include "linked_list.h"

// Generic allocation macro
#define NEW(type) (malloc(sizeof (type)))

// Assign a node pointer to node_ptr and give it tail node attributes.
#define TAIL_NODE(node_ptr, tail_node) {\
                node_ptr = tail_node;\
                node_ptr->val = NULL;\
                node_ptr->tail = true;\
            }

/**
 *  Initialize a new linked_list object with a head node 
 *  If memory cannot be allocated, this will cause the program to exit.
 *
 *  @return linked_list *
 */
linked_list *ll_new() {
    linked_list *l = NEW(linked_list);
    node *new_node = NEW(node);

    if (!l || !new_node) {
        fprintf(stderr, "Critical error: Failed to allocate memory. Exiting program...");
    }
    TAIL_NODE(l->head, new_node);
    return l;
}

/**
 *  Append an integer value to a linked_list.
 *
 *  @param (list) Linked list
 *  @param (value) Value to append
 */
void ll_append(linked_list *list, char *val) {
    node *new_node = NEW(node);

    if (!new_node) {
        fprintf(stderr, "Critical error: Failed to allocate memory. Exiting program...");
        ll_free_list(list);
    }
    if (list->head->tail == true) {
        list->head->val = strdup(val);
        list->head->tail = false;
        
        TAIL_NODE(list->head->next, new_node);
    } else {
        node *n;
        for (n = list->head; n->tail == false; n = n->next)
            ; 

        n->val = strdup(val);
        n->tail = false;
      
        TAIL_NODE(n->next, new_node);
    }

}

/**
 *  Determine if a val exists in the linked list list.
 *  @param (list) Linked list
 *  @param (val) Value to search for
 *
 *  @return Boolean
 */
int ll_node_exists(linked_list *list, char *val) {
    node *n;
    int found = 0; // BOOL?

    for (n = list->head; n->tail == false && strcmp(n->val, val) ; n = n->next)
        ;

    if (n->tail == false && strcmp(n->val, val) == 0)
        found = 1;
    return found;
}

/**
 *  Attempt to remove a node from list. This will patch any reference gaps created by the delete.
 *
 *  @param (list) Linked List
 *  @param (delete_me) Pointer to node to be deleted
 */
void ll_delete_node(linked_list *list, node *delete_me) {
    node *n;
    node *prev;
    bool is_head_node;

    for (n = list->head, is_head_node = true; n->tail == false && n != delete_me ; prev = n, n = n->next, is_head_node = false)
        ; 

    if (n == delete_me) {
        if (is_head_node)
            return;

        // At this point, prev is a pointer to the value of n right before loop terminiation.
        // n is a pointer to our target node.
        // n->next is a pointer to the node after out target node. 
        // Instead of prev->next pointing to our target node, tell it to point to the node after it.
        prev->next = n->next;
        free(n);
    }
    return;
}

/**
 *  Print the nodes attached to a linked list.
 *
 *  @param (list) Linked List
 */
void ll_print_list(linked_list *list) {
    node *n;
    for (n = list->head; n->tail == false; n = n->next)
        printf("%s\n", n->val);
}

/**
 * Remove all the nodes of a linked list. 
 *
 * @param (list) Linked List
 */
static void ll_empty_list(linked_list *list) {
    node *n = list->head;
    node *temp;
    
    while (n->tail == false) {
        temp = n;
        n = n->next;
        free(temp->val);
        free(temp);
    }
    free(n);
}

/**
 *  Completey deallocate all memory used by a linked list. Call this when you are done using the list.
 *
 *  @param (list) Linked list
 */
void ll_free_list(linked_list *list) {
    linked_list *lp = list;
    ll_empty_list(list);
    free(list);
    lp = NULL;
}

#undef NEW
#undef TAIL_NODE
#undef false
#undef true
