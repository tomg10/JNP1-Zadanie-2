#ifndef JNP2_STRSET_H

#ifdef __cplusplus
#include <cstddef>
#include <iostream>
#else
#include <stddef.h>
#endif


#ifdef __cplusplus
namespace jnp1
{
    extern "C"
    {
#endif

        unsigned long strset_new();

        void strset_delete(unsigned long id);

        size_t strset_size(unsigned long id);

        void strset_insert(unsigned long id, const char* value);

        void strset_remove(unsigned long id, const char* value);

        int strset_test(unsigned long id, const char* value);

        void strset_clear(unsigned long id);

        int strset_comp(unsigned long id1, unsigned long id2);

#ifdef __cplusplus
    }
}
#endif

#define JNP2_STRSET_H
#endif //JNP2_STRSET_H
