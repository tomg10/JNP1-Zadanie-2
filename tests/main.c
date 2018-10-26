#include "strset.h"
#include "strsetconst.h"

#include <assert.h>
#include <stdio.h>

int main() {
    unsigned long s;
    char buf[4] = "foo";
    s = strset_new();
    strset_insert(s, buf);
    buf[0] = 'b';
    assert(strset_test(s, "foo"));
    assert(!strset_test(s, "boo"));

   //assert(1 == 2);

    return 0;
}
