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


    //check if c1 equals to c2
    bool equals(char *c1, char *c2)
    {
        if(c1 == c2)
            return true;
        STR_LEN_DTYPE i = 0;
        while (c1[i] && c2[i] && c1[i] == c2[i])
        {
            i++;
        }
        return (c1[i] == 0 && c2[i] == 0);
    }


    //get substr from 'start'
    void substr(char *from, char *to, STR_LEN_DTYPE start)
    {
        from += start;
        while(*from)
        {
            *to = *from;
            from++;
            to++;
        }
        *to = '\0';
    }

    //get substr between 'start' and 'end'
    void substr(char *from, char *to, STR_LEN_DTYPE start, STR_LEN_DTYPE end)
    {
        from += start;
        end -= start;
        end++;
        while(*from && end)
        {
            *to = *from;
            from++;
            to++;
            end--;
        }
        *to = '\0';
    }

    //get substring between chars 'sym'
    void split(char *from, char *to, char sym)
    {
        STR_LEN_DTYPE   start = charAt(from, sym),
                        end = lastCharAt(from, sym);
        if(start == end)
            return;
        start++;
        end--;

        substr(from, to, start, end);
    }
}
