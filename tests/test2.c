#include "strsetconst.h"
#include "strset.h"
#include <assert.h>

int main(void) {
//operations on nonexistant sets
    {
        strset_delete(1);
        strset_delete(2);
        strset_delete(3);

        assert(strset_size(strset42()) == 1);

        assert(strset_size(5) == 0);
        assert(strset_size(2) == 0);

        strset_remove(1, "a");
        strset_remove(10123, "42");
        strset_remove(0, "......");

        assert(strset_test(7, "hello") == 0);
        assert(strset_test(9, "test") == 0);
        assert(strset_test(9, "") == 0);

        strset_clear(1);
        strset_clear(2);
        strset_clear(6);

        assert(strset_comp(123, 1295120) == 0);
        assert(strset_comp(1293, 192) == 0);
        assert(strset_comp(1230, strset42()) == -1);
    }

}