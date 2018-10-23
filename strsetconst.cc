#include "strsetconst.h"
#include "strset.h"

#ifdef DNDEBUG
const bool debug = false;
#else
const bool debug = true;
#endif

using std::cerr;

namespace {
    bool wasSetCreated = false;
    unsigned long id;
}

namespace jnp1 {
    unsigned long strset42() {

        if (!wasSetCreated && debug) {
            cerr << "strsetconst init invoked\n";
        }


        if (!wasSetCreated) {
            wasSetCreated = true;
            id = strset_new();
            strset_insert(id, "42");

            if (debug) {
                cerr << "strsetconst init finished\n";
            }
        }

        return id;
    }


}