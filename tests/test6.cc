#include "strsetconst.h"
#include "strset.h"
#include <assert.h>

int main(void) {
    unsigned long id_const = ::jnp1::strset42();
    unsigned long id2 = ::jnp1::strset_new();

    assert(id_const != id2);

    ::jnp1::strset_insert(id_const, "a");
    assert(::jnp1::strset_test(id_const, "a") == 0);
    assert(::jnp1::strset_size(id_const) == 1);

    ::jnp1::strset_insert(id2, "a");
    ::jnp1::strset_insert(id2, "b");

    assert(::jnp1::strset_size(id2) == 2);
    assert(::jnp1::strset_comp(id_const, id2) == -1);
    assert(::jnp1::strset_comp(id2, id_const) == 1);

    ::jnp1::strset_remove(1000000, "");
    assert(::jnp1::strset_test(id2, "") == 0);
    assert(::jnp1::strset_test(id2, NULL) == 0);

    ::jnp1::strset_remove(id2, "a");
    assert(::jnp1::strset_size(id2) == 1);
    assert(::jnp1::strset_test(id2, "a") == 0);
    assert(::jnp1::strset_test(id2, "b") == 1);

    ::jnp1::strset_delete(id2);
    assert(::jnp1::strset_size(id2) == 0);
    assert(::jnp1::strset_comp(id2, id_const) == -1);
    assert(::jnp1::strset_test(id2, "b") == 0);

    assert(::jnp1::strset_test(id_const, "42") == 1);
    ::jnp1::strset_remove(id_const, "42");
    assert(::jnp1::strset_test(id_const, "42") == 1);
    assert(::jnp1::strset_size(id_const) == 1);

    assert(::jnp1::strset42() == id_const);
    assert(::jnp1::strset_comp(id_const, 10000) == 1);
}