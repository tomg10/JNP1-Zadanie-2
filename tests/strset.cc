#include "strset.h"
#include "strsetconst.h"
#include <set>

using std::set;
using std::make_pair;
using std::string;
using std::cerr;
using std::string;

#ifdef DNDEBUG
const bool debug = false;
#else
const bool debug = true;
#endif

namespace
{

    using std::map;
    using std::set;
    using std::string;

    using longToSetMap = map <unsigned long, set <string> >;

    longToSetMap& globalMap() {
        static longToSetMap* resultMap = new longToSetMap();
        return *resultMap;
    }


    //std::map<unsigned long, std::set<std::string>> idsToSets;
    unsigned long firstFreeId = 1;

    bool strset_exists(unsigned long id)
    {
        return globalMap().find(id) != globalMap().end();
    }

    string createFuncTemplate(const string& name, unsigned long id) {
        return name + "(" + std::to_string(id) + ")";
    }

    string createFuncTemplate(const string& name, unsigned long id, const char *value) {
        const char* arg = value == nullptr ? "NULL" : value;

        return name + "(" + std::to_string(id) + ", " + arg + ")";
    }

    string createFuncTemplate(const string& name, unsigned long id1, unsigned long id2) {
        return name + "(" + std::to_string(id1) + ", " + std::to_string(id2) + ")";
    }

}

namespace jnp1
{
extern "C"
{
unsigned long strset_new()
{
    if (debug) {
        cerr << "strset_new()\n";
    }

    globalMap().insert(std::make_pair(firstFreeId, set <string>()));
    firstFreeId++;

    if (debug) {
        cerr << "strset_new: set " << firstFreeId - 1 << " created\n";
    }

    return firstFreeId - 1;
}


void strset_delete(unsigned long id)
{
    string func = createFuncTemplate("strset_delete", id);

    if (debug) {
        cerr << func << "\n";
    }

    if (id == strset42()) {
        if (debug) {
            cerr << "strset_delete: tried to delete the const set\n";
        }
    } else if (!strset_exists(id)) {
        if (debug) {
            cerr << "strset_delete: tried to delete nonexistent set\n";
        }
    } else {
        globalMap().erase(globalMap().find(id));

        if (debug) {
            cerr << "strset_delete: set " << id << " removed\n";
        }
    }
}


size_t strset_size(unsigned long id)
{
    string func = createFuncTemplate("strset_size", id);

    if (debug) {
        cerr << func << "\n";
    }

    size_t result = strset_exists(id) ? globalMap()[id].size() : 0;

    if (debug) {
        cerr << "strset_size: set " << id << " contains " << result << " element(s)\n";
    }

    return result;
}


void strset_insert(unsigned long id, const char *value)
{
    string func = createFuncTemplate("strset_insert", id, value);

    if (value == nullptr) {
        if (debug) {
            cerr << func << " illegal NULL value\n";
        }

        return;
    }

    if (debug) {
        cerr << func << "\n";
    }

    string toInsert = string(value);

    if (id == strset42() && strset_size(id) == 0) {
        globalMap()[id].insert(toInsert);
    } else if (id == strset42() && strset_size(id) != 0) {
        if (debug) {
            cerr << func << " illegal call on const set\n";
        }
        return;
    }

    if (!strset_exists(id)) {
        if (debug) {
            cerr << func << " called on nonexistant set\n";
        }

        return;
    }
    if (strset_test(id, value) == 1) {
        if (debug) {
            cerr << "strset_insert: set " << id << " already contains element " << value << "\n";
        }
    } else {
        globalMap()[id].insert(toInsert);

        if (debug) {
            cerr << "strset_insert: set " << id << " element " << value << " inserted\n";
        }
    }
}


void strset_remove(unsigned long id, const char *value)
{
    string func = createFuncTemplate("strset_remove", id, value);

    if (value == nullptr) {
        if (debug) {
            cerr << func << " illegal NULL value\n";
        }
        return;
    }

    if (id == strset42()) {
        if (debug) {
            cerr << func << " illegal call on const set\n";
        }
        return;
    } else if (!strset_exists(id)) {
        if (debug) {
            cerr << func << " called on nonexistant set\n";
        }
        return;
    }

    globalMap()[id].erase(value);

    if (debug) {
        cerr << "strset_remove: element " << value << " removed from set " << id << "\n";
    }

}


int strset_test(unsigned long id, const char *value)
{
    string func = createFuncTemplate("strset_test", id, value);

    if (value == nullptr) {
        if (debug) {
            cerr << func << " illegal NULL value\n";
        }
        return 0;
    }

    if (debug) {
        cerr << func << "\n";
    }

    bool answer = (strset_exists(id) && globalMap()[id].find(value) != globalMap()[id].end());

    if (debug) {
        std::string phrase = answer ? " contains " : " does not contain ";

        cerr << "strset_test: set " << id << phrase << " element " << value << "\n";
    }

    return answer ? 1 : 0;
}


void strset_clear(unsigned long id)
{
    string func = createFuncTemplate("strset_clear", id);

    if (id == strset42()) {
        if (debug) {
            cerr << func << " illegal call on const set\n";
        }

        return;
    }

    if (!strset_exists(id)) {
        if (debug) {
            cerr << func << " called on nonexistant set\n";
        }

        return;
    }

    globalMap()[id].clear();

    if (debug) {
        cerr << "strset_clear: cleared set " << id << "\n";
    }
}


int strset_comp(unsigned long id1, unsigned long id2)
{
    string func = createFuncTemplate("strset_comp", id1, id2);

    if (debug) {
        cerr << func << "\n";
    }

    size_t size1 = strset_size(id1);
    size_t size2 = strset_size(id2);



    if (size1 == 0 && size2 == 0)
    {
        return 0;
    } else if (size1 == 0 || size2 == 0)
    {
        return size1 == 0 ? -1 : 1;
    }

    auto it1 = globalMap()[id1].begin();
    auto it2 = globalMap()[id2].begin();
    auto it1End = globalMap()[id1].end();
    auto it2End = globalMap()[id2].end();

    while (it1 != it1End && it2 != it2End) {
        auto compare = (*it1).compare(*it2);
        if (compare == 0) {
            it1++;
            it2++;
            continue;
        }


        return compare < 0 ? -1 : 1;
    }

    if (size1 == size2) {
        return 0;
    } else {
        return size1 < size2 ? -1 : 1;
    }

}

}
}
