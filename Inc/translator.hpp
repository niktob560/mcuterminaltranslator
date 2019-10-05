#include <iostream>
#include <string.h>
#include <stdint.h>

namespace translator
{
    typedef uint32_t STR_LEN_DTYPE;
    typedef uint16_t checksum_t;

    const STR_LEN_DTYPE str_NAN = 0xFFFFFFFF;
    const uint8_t       TYPE_CMD = 0b01,
                        TYPE_VAR = 0b10,
                        TYPE_ARR = 0b11,
                        TYPE_BAD_LEN = 100,
                        TYPE_BAD_TYPE = 101,
                        TYPE_BAD_CHECKSUM = 102,
                        LEN_MASK = 0b00111111;

    //generate checksum for char array
    checksum_t genCheckSum(const uint8_t* c);

    //parse var from var package and write into toArr[id]
    void parseVar(uint8_t *package, void **toArr);

    //parse array from array package and write into toArr[id]
    void parseArr(uint8_t *package, void **toArr);

    //parse cmd from package, call funcArr[cmd]
    void parseCmd(uint8_t *package, void (*funcArr [])());

    //parse input package, get payload, return type of package
    uint8_t parsePacket(uint8_t *package, uint8_t *payloadto);

    //get payload from package to addr
    void getPayload(const uint8_t *package, uint8_t *to);

    //get type of package
    uint8_t getType(uint8_t *package);

    bool equals(const uint8_t* p1, const uint8_t* p2);
}
