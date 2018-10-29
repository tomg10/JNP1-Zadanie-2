#include "strsetconst.h"
#include "strset.h"
#include <stdio.h>

#include <assert.h>

int main(void) {
    unsigned long id_const, id1, id2, id3;

    id2 = 1000000;
    id3 = 10000001;

    id1 = strset_new();
    id_const = strset42();

    assert(strset_test(id_const, "42") == 1);
    assert(strset_test(id_const, "") == 0);
    assert(strset_test(id_const, NULL) == 0);

    assert(strset_comp(id_const, id1) == 1);

    assert(strset_test(id1, "a") == 0);

    assert(strset_size(id1) == 0);
    assert(strset_size(id2) == 0);
    assert(strset_size(id3) == 0);

    assert(strset_comp(id2, id3) == 0);

    strset_insert(id2, "aaaa");

    assert(strset_size(id2) == 0);
    strset_insert(id3, "bbb");

    assert(strset_size(id3) == 0);

    id2 = strset_new();
    id3 = strset_new();

    strset_insert(id2, "");
    strset_insert(id3, "");
    assert(strset_size(id2) == 1);
    assert(strset_size(id3) == 1);

    assert(id2 != id3);
    assert(id2 != id_const);

    assert(strset_comp(id2, id3) == 0);
    assert(strset_comp(id3, id2) == 0);

    assert(strset_size(id2) == 1);
    assert(strset_size(id3) == 1);
    assert(strset_test(id2, "") == 1);
    assert(strset_test(id3, "") == 1);

    strset_insert(id2, " ");
    assert(strset_size(id2) == 2);
    assert(strset_comp(id3, id2) == -1);

    strset_insert(id2, "");
    assert(strset_size(id2) == 2);

    strset_remove(id2, " ");
    assert(strset_size(id2) == 1);
    assert(strset_comp(id2, id3) == 0);

    strset_delete(id2);
    assert(strset_size(id2) == 0);
    assert(strset_comp(id2, id3) == -1);

    assert(strset_size(id2) == 0);
    assert(strset_test(id2, "") == 0);

    strset_insert(id2, "hello there");
    assert(strset_size(id2) == 0);
    assert(strset_test(id2, "hello there") == 0);

    char t[4] = "boo";

    strset_insert(id3, t);
    assert(strset_test(id3, "boo") == 1);

    t[0] = 'f';

    assert(strset_size(id3) == 2);
    assert(strset_test(id3, "boo") == 1);
    assert(strset_test(id3, "foo") == 0);

    strset_clear(id3);
    assert(strset_test(id3, "boo") == 0);
    assert(strset_size(id3) == 0);

    strset_clear(strset42());

    assert(strset_size(strset42()) == 1);
    assert(strset_test(strset42(), "42") == 1);

    unsigned long a = 10;
    unsigned long b = 11;

    assert(strset_comp(a, b) == 0);
    assert(strset_size(a) == 0);
    assert(strset_size(b) == 0);

    assert(strset_comp(b, a) == 0);
    assert(strset_size(a) == 0);
    assert(strset_size(b) == 0);

    strset_insert(a, "a");
    assert(strset_size(a) == 0);
    assert(strset_test(a, "a") == 0);
    strset_clear(a);
    assert(strset_size(a) == 0);
    strset_insert(a, "a");
    assert(strset_size(a) == 0);

    strset_delete(a);
    assert(strset_size(a) == 0);
    strset_insert(a, "a");
    assert(strset_size(a) == 0);
    assert(strset_test(a, "a") == 0);

    strset_remove(a, "a");
    assert(strset_test(a, "a") == 0);
    strset_insert(a, "a");
    assert(strset_test(a, "a") == 0);

    a = strset_new();

    assert(a != id_const);

    strset_insert(a, NULL);
    assert(strset_size(a) == 0);
    assert(strset_test(a, NULL) == 0);
    strset_remove(a, NULL);
    assert(strset_size(a) == 0);
    assert(strset_test(a, NULL) == 0);

    strset_delete(a);
    assert(strset_size(a) == 0);
    assert(strset_test(a, NULL) == 0);

    strset_remove(a, NULL);
    assert(strset_test(a, NULL) == 0);
    assert(strset_test(a, "a") == 0);

    a = strset_new();
    b = strset_new();

    assert(a != b);
    assert(strset_comp(a, b) == 0);

    assert(strset_size(a) == 0);
    assert(strset_size(b) == 0);

    return 0;
}
