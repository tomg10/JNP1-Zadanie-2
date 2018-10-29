#include "strset.h"
#include "strsetconst.h"
#include <set>
#include <algorithm>
#include <assert.h>
#include <map>

using std::set;
using std::make_pair;
using std::string;
using std::cerr;
using std::string;

#ifdef NDEBUG
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

    bool doesSetContainElement(unsigned long id, const char* value) {
        return (strset_exists(id) && globalMap()[id].find(value) != globalMap()[id].end());
    }

}

namespace jnp1
{
extern "C"
{


unsigned long strset_new()
{
    static unsigned long firstFreeId = 0;

    if (debug) {
        cerr << "strset_new()\n";
        assert(!strset_exists(firstFreeId));
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
    if (debug) {
        string func = createFuncTemplate("strset_delete", id);
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
    if (debug) {
        string func = createFuncTemplate("strset_size", id);
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
    if (debug) {
        string func = createFuncTemplate("strset_insert", id, value);
        cerr << func << "\n";
    }

    if (value == nullptr) {
        if (debug) {
            cerr << "strset_insert(): illegal NULL value\n";
        }
        return;
    }

    string toInsert = string(value);

    if (id == strset42() && strset_size(id) == 0) {
        globalMap()[id].insert(toInsert);
    } else if (id == strset42() && strset_size(id) != 0) {
        if (debug) {
            cerr << "strset_insert: illegal call on const set\n";
        }
        return;
    }

    if (!strset_exists(id)) {
        if (debug) {
            cerr << "strset_insert: called on nonexistant set\n";
        }

        return;
    }
    if (doesSetContainElement(id, value)) {
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
    if (debug) {
        string func = createFuncTemplate("strset_remove", id, value);
        cerr << func << "\n";
    }

    if (value == nullptr) {
        if (debug) {
            cerr << "strset_remove : illegal NULL value\n";
        }
        return;
    }

    if (id == strset42()) {
        if (debug) {
            cerr << "strset_remove: illegal call on const set\n";
        }
        return;
    } else if (!strset_exists(id)) {
        if (debug) {
            cerr << "strset_remove: called on nonexistant set\n";
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
    if (debug) {
        string func = createFuncTemplate("strset_test", id, value);
        cerr << func << "\n";
    }

    if (value == nullptr) {
        if (debug) {
            cerr << "strset_test: illegal NULL value\n";
        }
        return 0;
    }

    bool answer = doesSetContainElement(id, value);

    if (debug) {
        std::string phrase = answer ? " contains " : " does not contain ";
        cerr << "strset_test: set " << id << phrase << " element " << value << "\n";
    }

    return answer ? 1 : 0;
}


void strset_clear(unsigned long id)
{

    if (debug) {
        string func = createFuncTemplate("strset_clear", id);
        cerr << func << "\n";
    }


    if (id == strset42()) {
        if (debug) {
            cerr << "strset_clear: illegal call on const set\n";
        }

        return;
    }

    if (!strset_exists(id)) {
        if (debug) {
            cerr << "strset_clear: called on nonexistant set\n";
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
    if (debug) {
        string func = createFuncTemplate("strset_comp", id1, id2);
        cerr << func << "\n";
    }

    set <string> first = globalMap()[id1];
    set <string> second = globalMap()[id2];

    bool comp1 = std::lexicographical_compare(first.begin(), first.end(),
                                              second.begin(), second.end());

    bool comp2 = std::lexicographical_compare(second.begin(), second.end(),
                                              first.begin(), first.end());

    int answer;
    string grammar;

    if (!comp1 and !comp2) {
        answer = 0;
        grammar = "equal to";
    } else if (!comp1) {
        answer = 1;
        grammar = "greater than";
    } else {
        answer = -1;
        grammar = "less than";
    }

    if (debug) {
        cerr << "strset_comp: set " << id1 << " is lexicographically " <<
            grammar << " set " << id2 << "\n";
    }

    return answer;
}

}
}
