/*
    Make sure the ignore flags parser works.
*/
#include <stdio.h>
#include <string.h>
#include "../src/lists/linked_list.h"
#include "../src/util.h"


int main(int argc, char *argv[]) {
    linked_list *ll = ll_new();
    char *ext = ".c,.h,.js,.php,.cs";
   
    string_split_to_ll(ext, ll, ',');
    ll_print_list(ll);
    ll_free_list(ll);
    return 1;
}
