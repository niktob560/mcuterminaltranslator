#include "translator.hpp"

namespace translator
{
    #ifdef USE_MULTIDEVICE
        #pragma message "Using multidevice version"
        const uint8_t SYS_LEN = 4;

        #ifdef USE_DYNAMIC_ID
            uint8_t myId = 0;
        #else
            #ifndef DEVICE_ID
                #error "Device id is not set"
            #else
                #pragma message "Using static device id"
                const uint8_t myId = DEVICE_ID;
            #endif
        #endif
    #else
        #pragma message Using 1-1 device version
        const uint8_t SYS_LEN = 3;
    #endif



    //generate checksum for char array
    checksum_t genCheckSum(const uint8_t* c)
    {
        checksum_t ret = 0;
        uint8_t len = getLen(c);
        for(uint8_t i = 0; i < len + SYS_LEN; i++)
        {
            if(i != 1 && i != 2)
                ret = static_cast<checksum_t>(ret + ((c[i]) << (8 * ((i % 2) == 1))));
        }
        ret++;
        return ret;
    }


    //parse input package, get payload, return type of package
    uint8_t parsePacket(uint8_t* package, uint8_t* payloadto)
    {
        uint8_t type = getType(package);
        if(type != TYPE_ARR && type != TYPE_CMD && type != TYPE_VAR)
            return TYPE_BAD_TYPE;
        uint8_t len = getLen(package);
        if(len == 0)
            return TYPE_BAD_LEN;

        if(genCheckSum(package) != getCheckSum(package))
            return TYPE_BAD_CHECKSUM;


        for(uint8_t i = 0; i < len; i++)
        {
            payloadto[i] = package[i + SYS_LEN];
        }
        return type;
    }


    //parse cmd from package, call funcArr[cmd], return type of package, max num of funcs - 255
    uint8_t parseCmd(uint8_t* package, void (*funcArr [])())
    {
        uint8_t var = getType(package);
        if(var != TYPE_CMD)
            return TYPE_BAD_TYPE;

        var = getLen(package);
        if(var != 1)
            return TYPE_BAD_LEN;

        checksum_t check = genCheckSum(package);
        if(check != getCheckSum(package))   
            return TYPE_BAD_CHECKSUM;

        if(funcArr[package[SYS_LEN]] != NULL)
            funcArr[package[SYS_LEN]]();
            
        return TYPE_CMD;
    }

    size_t parseCmd(uint8_t* package)
    {
        uint8_t var = getType(package);
        if(var != TYPE_CMD)
            return TYPE_BAD_TYPE;

        var = getLen(package);
        if(var != 1)
            return TYPE_BAD_LEN;

        checksum_t check = genCheckSum(package);
        if(check != getCheckSum(package))
            return TYPE_BAD_CHECKSUM;
        return package[SYS_LEN];
    }


    bool equals(const uint8_t* p1, const uint8_t* p2)
    {
        if(p1[0] != p2[0])
            return false;

        uint8_t len = getLen(p1);
        for(uint8_t i = 0; i < len + SYS_LEN; i++)
        {
            if(p1[i] != p2[i])
                return false;
        }
        return true;
    }




    //gets cmd num at 'cmd', returns final package into target pointer
    void generateCmd(const uint8_t cmd, uint8_t* tgt)
    {
        tgt[0] = getZeroByte(TYPE_CMD, 1);
        #ifdef USE_MULTIDEVICE
            tgt[SYS_LEN - 1] = myId;
        #endif 
        tgt[SYS_LEN] = cmd;
        checksum_t check = genCheckSum(tgt);
        tgt[1] = static_cast<uint8_t>(check >> 8);
        tgt[2] = static_cast<uint8_t>(check & 0xFF);
    }


    //validate checksum, type, len
    bool validate(const uint8_t* package)
    {
        uint8_t type = getType(package);
        switch (type)
        {
            case TYPE_CMD:
            {
                if(getLen(package) != 1)
                    return false;
                break;
            }
            case TYPE_VAR:
            case TYPE_ARR:
            {
                if(getLen(package) <= 1)
                    return false;
                break;
            }
            default:
                return false;
        }
        return (getCheckSum(package) == genCheckSum(package));
    }

    //create var package
    void generateVar(const uint8_t id, const uint8_t varlen, const uint8_t* var, uint8_t* tgt)
    {
        tgt[0] = getZeroByte(TYPE_VAR, static_cast<uint8_t>(varlen + 1));
        tgt[SYS_LEN] = id;
        for(uint8_t i = 0; i < varlen; i++)
        {
            tgt[SYS_LEN + 1 + i] = var[varlen - i - 1];
        }

        #ifdef USE_MULTIDEVICE
            tgt[SYS_LEN - 1] = myId;
        #endif 

        checksum_t check = genCheckSum(tgt);
        tgt[1] = static_cast<uint8_t>(check >> 8);
        tgt[2] = static_cast<uint8_t>(check & 0xFF);

    }


    //parse var from var package and write into toArr[id], return type of package
    uint8_t parseVar(uint8_t* package, uint8_t* toArr, uint8_t elsize)
    {
        uint8_t type = getType(package);
        if(type != TYPE_VAR)
            return TYPE_BAD_TYPE;
        uint8_t len = getLen(package);
        if(len < 2)
            return TYPE_BAD_LEN;
        checksum_t  check = genCheckSum(package),
                    thischeck = getCheckSum(package);
        if(check != thischeck)
            return TYPE_BAD_CHECKSUM;

        uint8_t id = package[SYS_LEN];
        for(uint8_t i = 0; i < len - 1; i++)
        {
            toArr[(id + i) * elsize] = package[i + SYS_LEN + 1];
        }
        return TYPE_VAR;
    }
    
    
    //create array package
    void generateArr(const uint8_t id, const uint8_t arrlen, const uint8_t elsize, const uint8_t* arr, uint8_t* tgt)
    {
        tgt[0] = getZeroByte(TYPE_ARR, static_cast<uint8_t>((arrlen * elsize) + 1));
        tgt[SYS_LEN] = id;
        for(uint8_t i = 0; i < arrlen; i++)
        {
            for(uint8_t j = 0; j < elsize; j++)
            {
                tgt[SYS_LEN + 1 + (i * elsize) + j] = arr[(i * elsize) + (elsize - j - 1)];
            }
        }

        #ifdef USE_MULTIDEVICE
            tgt[SYS_LEN - 1] = myId;
        #endif 

        checksum_t check = genCheckSum(tgt);
        tgt[1] = static_cast<uint8_t>(check >> 8);
        tgt[2] = static_cast<uint8_t>(check & 0xFF);
    }
    
    //parse array from array package and write into toArr(ignoring id), return type of package
    uint8_t parseArrNoId(uint8_t* package, uint8_t* toArr)
    {
        uint8_t type = getType(package);
        if(type != TYPE_ARR)
            return TYPE_BAD_TYPE;
        uint8_t len = getLen(package);
        if(len < 2)
            return TYPE_BAD_LEN;
        checksum_t  check = genCheckSum(package),
                    thischeck = getCheckSum(package);
        if(check != thischeck)
            return TYPE_BAD_CHECKSUM;

        for(uint8_t i = 0; i < len - 1; i++)
        {
            toArr[i] = package[SYS_LEN + 1 + i];
        }
        return TYPE_ARR;
    }
    
    //parse array from array package and write into toArr[id], return type of package
    uint8_t parseArr(uint8_t* package, uint8_t** toArr)
    {
        uint8_t id = parseArrId(package);
        return parseArrNoId(package, toArr[id]);
    }
    
    
    //check for package is full
    bool isFull(uint8_t* package, const uint8_t len)
    {

        if(len < SYS_LEN)
            return false;
        if((getLen(package) + SYS_LEN) != len)
            return false;
        switch (getType(package))
        {
            case TYPE_CMD:
            {
                if(getLen(package) != 1)
                    return false;
                break;
            }
            case TYPE_VAR:
            case TYPE_ARR:
            {
                if(getLen(package) <= 1)
                    return false;
                break;
            }
            default:
                return false;
        }
        return true;
    }


    bool isHeaderValid(uint8_t head)
    {
        switch (getType(&head))
        {
            case TYPE_CMD:
            {
                if(getLen(&head) != 1)
                    return false;
                break;
            }
            case TYPE_VAR:
            case TYPE_ARR:
            {
                if(getLen(&head) <= 1)
                    return false;
                break;
            }
            default:
                return false;
        }
        return true;
    }
}
