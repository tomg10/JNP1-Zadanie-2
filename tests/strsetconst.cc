#include "strsetconst.h"
#include "strset.h"

#ifdef NDEBUG
const bool debug = false;
#else
const bool debug = true;
#endif

using std::cerr;

namespace {

}

namespace jnp1 {
    unsigned long strset42() {

        static bool wasSetCreated = false;
        static unsigned long id;

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