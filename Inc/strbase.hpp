#include <string.h>
#include <stdint.h>

namespace translator
{
    typedef uint32_t STR_LEN_DTYPE;
    // #ifndef STR_LEN_DTYPE
    //     #define STR_LEN_DTYPE uint32_t
    // #endif

    const STR_LEN_DTYPE str_NAN = 0xFFFFFFFF;

    //checks if string c contains char cc
    bool contains(char *c, const char cc);

    //FIXME: bullshit because of native support
    // //returns len of string c
    // STR_LEN_DTYPE strlen(char *c);

    //get first char, matching cc from string c
    STR_LEN_DTYPE charAt(char *c, const char cc);

    //get last char, matching cc from string c
    STR_LEN_DTYPE lastCharAt(char *c, const char cc);

}
