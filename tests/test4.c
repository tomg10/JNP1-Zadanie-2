#include "strset.h"
#include "strsetconst.h"
#include <assert.h>
#include <stdlib.h>

//NULL values, changing values
int main(void) {
    char foo[4] = "yes";

    unsigned long id = strset_new();

    assert(id != strset42());

    strset_insert(id, foo);

    assert(strset_test(id, "yes") == 1);
    assert(strset_test(id, foo) == 1);
    assert(strset_size(id) == 1);

    foo[0] = 'x';

    assert(strset_test(id, "yes") == 1);
    assert(strset_test(id, "xes") == 0);


    assert(strset_test(id, "yes") == 1);
    assert(strset_test(id, "") == 0);

    strset_insert(id, NULL);

    assert(strset_size(id) == 1);
    assert(strset_test(id, NULL) == 0);

    unsigned long id2 = strset_new();

    assert(strset_comp(id, id2) == 1);

    for (size_t i = 0; i < 1000; i++) {
        strset_insert(id2, "a");
    }

    assert(strset_size(id2) == 1);
    assert(strset_test(id2, "a") == 1);

    strset_remove(id2, NULL);
    assert(strset_size(id2) == 1);

    assert(strset_comp(id, id2) == 1);

    strset_clear(id2);

    assert(strset_size(id2) == 0);
    assert(strset_comp(id2, id) == -1);

    strset_remove(100000, NULL);
    strset_insert(100000, NULL);
    assert(strset_test(100000, NULL) == 0);
}