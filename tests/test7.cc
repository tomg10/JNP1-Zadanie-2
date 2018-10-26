#include "strsetconst.h"
#include "strset.h"
#include <assert.h>

using namespace ::jnp1;

int main(void) {
    unsigned long id = strset_new();
    unsigned long id_const = strset42();

    assert(id != id_const);
    assert(strset_size(id) == 0);
    assert(strset_size(id_const) == 1);
    assert(strset_test(id_const, "42") == 1);
    assert(strset_test(id, NULL) == 0);
    assert(strset_test(id, "") == 0);

    strset_insert(id, "");
    assert(strset_test(id, "") == 1);
    assert(strset_size(id) == 1);
    assert(strset_comp(id, id_const) == -1);

    assert(strset_comp(id_const, id) == 1);

    strset_remove(id, NULL);
    assert(strset_size(id) == 1);
    strset_clear(id);
    assert(strset_size(id) == 0);
    assert(strset_test(id, "") == 0);
}

