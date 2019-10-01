#include "strbase.hpp"

namespace translator
{
    //checks if string c contains char cc
    bool contains(char *c, const char cc)
    {
        while(*c)
        {
            if(*c == cc)
                return true;
            c++;
        }
        return false;
    }

    //FIXME: bullshit because of native support
    // //returns len of string c
    // STR_LEN_DTYPE strlen(char *c)
    // {
    //     STR_LEN_DTYPE i = 0;
    //     while(c[i])
    //     {
    //         i++;
    //     }
    //     return i;
    // }

    //get first char, matching cc from string c
    STR_LEN_DTYPE charAt(char *c, const char cc)
    {
        STR_LEN_DTYPE i = 0;
        while(c[i])
        {
            if(c[i] == cc)
                return i;
            i++;
        }
        return str_NAN;
    }

    //get last char, matching cc from string c
    STR_LEN_DTYPE lastCharAt(char *c, const char cc)
    {
        STR_LEN_DTYPE i = strlen(c);
        while(i && i != str_NAN)
        {
            i--;
            if(c[i] == cc)
                return i;
        }
        return str_NAN;
    }
}
