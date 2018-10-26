#include "strsetconst.h"
#include <assert.h>

int main(void) {
    unsigned long id1 = strset42();
    unsigned long id2 = strset42();

    assert(id1 == id2);
}
