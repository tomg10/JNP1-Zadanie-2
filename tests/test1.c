#include "strset.h"
#include "strsetconst.h"

#include <assert.h>
#include <stdbool.h>

int main() {
//checking whether new doesn't create two sets with same ID

    {
        size_t N = 100;
        bool defined[N];

        for (size_t i = 0; i < N; i++) {
            defined[i] = false;
        }

        unsigned long ids[N];

        for (size_t i = 0; i < N; i++) {
            unsigned long id = strset_new();

            assert(!defined[id]);
            ids[i] = id;
            defined[id] = true;
        }

	assert(ids[0] != ids[1]);
    }

//const set operations
    {
        unsigned long id = strset42();
        assert(strset_size(id) == 1);
        assert(strset_test(id, "42") == 1);

        unsigned long new_id = strset42();
        assert(new_id == id);

        strset_remove(id, "43");
        assert(strset_size(id) == 1);

        strset_remove(id, "42");
        assert(strset_size(id) == 1);
        assert(strset_test(id, "42") == 1);

        strset_delete(id);
        assert(strset_size(id) == 1);
        assert(strset_test(id, "42") == 1);

        strset_clear(id);
        assert(strset_size(id) == 1);
        assert(strset_test(id, "42") == 1);

        assert(strset_comp(id, new_id) == 0);
        assert(strset_size(id) == 1);
        assert(strset_size(new_id) == 1);
        assert(strset_test(id, "42") == 1);
        assert(strset_test(new_id, "42") == 1);
    }
	
//assert(1 == 2);
}
