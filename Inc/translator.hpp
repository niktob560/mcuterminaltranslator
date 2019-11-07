#include <iostream>
#include <string.h>
#include <stdint.h>

namespace translator
{
    extern const uint8_t SYS_LEN;
    #ifdef USE_MULTIDEVICE
        uint8_t getSenderId(uint8_t* p);
        #ifdef USE_DYNAMIC_ID
            extern uint8_t myId;

            void setMyId(uint8_t id);
            uint8_t getMyId(void);

        #else
            extern const uint8_t myId;
        #endif
    #endif

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

    //get len of payload
    uint8_t getLen(const uint8_t* package);

    //get type of package
    uint8_t getType(const uint8_t* package);

    //parse var from var package and write into toArr[id], return type of package
    uint8_t parseVar(uint8_t* package, uint8_t* toArr, uint8_t elsize);

    //parse array from array package and write into toArr[id], return type of package
    uint8_t parseArr(uint8_t* package, uint8_t** toArr);

    //parse cmd from package, call funcArr[cmd], return type of package, max num of funcs - 255, max len - 1
    uint8_t parseCmd(uint8_t* package, void (*funcArr [])());

    size_t parseCmd(uint8_t* package);


    bool equals(const uint8_t* p1, const uint8_t* p2);

    uint8_t getZeroByte(const uint8_t type, const uint8_t len);

    checksum_t getCheckSum(const uint8_t* package);

    //gets cmd num at 'cmd', returns final package into target pointer
    void generateCmd(const uint8_t cmd, uint8_t* tgt);

    //validate checksum, type, len
    bool validate(const uint8_t* package);

    //create var package
    void generateVar(const uint8_t id, const uint8_t varlen, const uint8_t* var, uint8_t *tgt);
    
    //create array package
    void generateArr(const uint8_t id, const uint8_t arrlen, const uint8_t elsize, const uint8_t* arr, uint8_t* tgt);
    
    //check for package is full
    bool isFull(uint8_t* package, const uint8_t len);

    bool isHeaderValid(uint8_t head);
}
