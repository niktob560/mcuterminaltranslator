#include <iostream>
#include <string.h>
#include <stdint.h>

namespace translator
{
    typedef uint32_t STR_LEN_DTYPE;
    typedef uint16_t checksum_t;

    const STR_LEN_DTYPE str_NAN = 0xFFFFFFFF;
    const uint8_t       TYPE_CMD = 0,
                        TYPE_VAR = 1,
                        TYPE_ARR = 2,
                        TYPE_BAD_LEN = 100,
                        TYPE_BAD_TYPE = 101,
                        TYPE_BAD_CHECKSUM = 102,
                        LEN_MASK = 0b00111111;

    //generate checksum for char array
    checksum_t genCheckSum(const char* c);

    //checks if string c contains char cc
    bool contains(char *c, const char cc);

    //get first char, matching cc from string c
    STR_LEN_DTYPE charAt(char *c, const char cc);

    //get last char, matching cc from string c
    STR_LEN_DTYPE lastCharAt(char *c, const char cc);

    //check if c1 equals to c2
    bool equals(char *c1, char *c2);

    //get substr from 'start'
    void substr(char *from, char *to, STR_LEN_DTYPE start);

    //get substr between 'start' and 'end'
    void substr(char *from, char *to, STR_LEN_DTYPE start, STR_LEN_DTYPE end);

    //get substring between chars 'sym'
    void split(char *from, char *to, char sym);

    //parse var from string |id:var| and write into toArr[id]
    void parseVar(char *from, void **toArr);

    //parse array from string |id:item0, item1,...,itemn| and write into toArr[id]
    void parseArr(char *from, void **toArr);

    //parse cmd from string |cmd|, find cmd in names and call it from funcArr
    void parseCmd(char *from, char** names, void (*funcArr [])());

    //parse input package, get payload, return type of package
    uint8_t parsePacket(char *from, char *payloadto);
}
