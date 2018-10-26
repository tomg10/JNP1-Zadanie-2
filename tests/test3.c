#include "strset.h"
#include <assert.h>

//including only strset.h
int main(void) {
    unsigned long first = strset_new();
    unsigned long second = strset_new();

    strset_insert(first, "a");
    strset_insert(second, "b");

    assert(strset_size(first) == 1);
    assert(strset_size(second) == 1);

    assert(strset_comp(first, second) == -1);
    assert(strset_comp(second, first) == 1);

    assert(strset_test(first, "a") == 1);
    assert(strset_test(first, "b") == 0);
    assert(strset_test(second, "a") == 0);
    assert(strset_test(second, "b") == 1);

    strset_remove(first, "c");
    assert(strset_size(first) == 1);
    assert(strset_test(first, "a") == 1);

    strset_remove(first, "a");
    assert(strset_size(first) == 0);
    assert(strset_test(first, "a") == 0);

    strset_clear(first);
    assert(strset_size(first) == 0);

    strset_clear(second);
    assert(strset_size(second) == 0);

    assert(strset_comp(first, second) == 0);
    assert(strset_comp(second, first) == 0);

    strset_delete(first);
    strset_delete(second);

    assert(strset_size(first) == 0);
    assert(strset_size(second) == 0);

    assert(strset_comp(first, second) == 0);

    assert(strset_test(first, "a") == 0);
    assert(strset_test(second, "b") == 0);
}