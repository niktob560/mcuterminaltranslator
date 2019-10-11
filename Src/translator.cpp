#include "translator.hpp"

namespace translator
{

    using namespace std;

    //generate checksum for char array
    checksum_t genCheckSum(const uint8_t* c)
    {
        checksum_t ret = 0;
        uint8_t len = getLen(c);
        for(uint8_t i = 0; i < len; i++)
        {
            ret |= (c[3 + i]) << (8 * ((i % 2) == 1));
        }
        return ret;
    }

    //get type of package
    uint8_t getType(const uint8_t* package)
    {
        return ((package[0] & (~LEN_MASK)) >> 6);
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
            payloadto[i] = package[i + 3];
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

        if(funcArr[package[3]] != NULL)
            funcArr[package[3]]();
        return TYPE_CMD;
    }


    //get payload from package to addr
    void getPayload(const uint8_t* package, uint8_t* to)
    {
        uint8_t len = getLen(package);
        for(uint8_t i = 0; i < len; i++)
        {
            to[i] = package[i + 3];
        }
    }

    //get len of payload
    uint8_t getLen(const uint8_t* package)
    {
        return package[0] & LEN_MASK;
    }

    bool equals(const uint8_t* p1, const uint8_t* p2)
    {
        if(p1[0] != p2[0])
            return false;

        uint8_t len = getLen(p1);
        for(uint8_t i = 0; i < len; i++)
        {
            if(p1[i] != p2[i])
                return false;
        }
        return true;
    }

    uint8_t getZeroByte(const uint8_t type, const uint8_t len)
    {
        return (uint8_t)(((type & 0b11) << 6) | (len & LEN_MASK));
    }


    checksum_t getCheckSum(const uint8_t* package)
    {
        return (package[1] << 8) | package[2];
    }


    //gets cmd num at 'cmd', returns final package into target pointer
    void generateCmd(const uint8_t cmd, uint8_t* tgt)
    {
        tgt[0] = getZeroByte(TYPE_CMD, 1);
        tgt[3] = cmd;
        checksum_t check = getCheckSum(tgt);
        tgt[1] = check >> 8;
        tgt[2] = check & 0xFF;
    }


    //get id of var in payload of package
    uint8_t getVarId(const uint8_t* pack)
    {
        if(!validate(pack))
            return 0xFF;

        return pack[3];
    }


    //validate checksum, type, len
    bool validate(const uint8_t* pack)
    {
        uint8_t type = getType(pack);
        switch (type)
        {
            case TYPE_CMD:
            {
                if(getLen(pack) != 1)
                    return false;
                break;
            }
            case TYPE_VAR:
            case TYPE_ARR:
            {
                if(getLen(pack) <= 1)
                    return false;
                break;
            }
            default:
                return false;
        }
        return (getCheckSum(pack) == genCheckSum(pack));
    }

    //create var package
    void generateVar(const uint8_t id, const uint8_t varlen, const uint8_t* var, uint8_t* tgt)
    {
        tgt[0] = getZeroByte(TYPE_VAR, varlen + 1);
        tgt[3] = id;
        for(uint8_t i = 0; i < varlen; i++)
        {
            tgt[4 + i] = var[varlen - i - 1];
            // std::cout << "from " << (int)(i) << " to " << (int)(i + 4) << " set 0x" << std::hex << (int)var[i] << std::endl;
        }
        checksum_t check = genCheckSum(tgt);
        tgt[1] = check >> 8;
        tgt[2] = check & 0xFF;
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

        uint8_t id = package[3];
        for(uint8_t i = 0; i < len - 1; i++)
        {
            toArr[(id + i) * elsize] = package[i + 4];
            // std::cout << "from " << (int)((id + i) * elsize) << " to " << (int)(i + 4) << std::endl;
        }
        return TYPE_VAR;
    }
    
    
    //create array package
    void generateArr(const uint8_t id, const uint8_t arrlen, const uint8_t elsize, const uint8_t* arr, uint8_t* tgt)
    {
        tgt[0] = getZeroByte(TYPE_ARR, (arrlen * elsize) + 1);
        tgt[3] = id;
        for(uint8_t i = 0; i < arrlen; i++)
        {
            for(uint8_t j = 0; j < elsize; j++)
            {
                tgt[4 + (i * elsize) + j] = arr[(i * elsize) + (elsize - j - 1)];
            }
            // tgt[4 + i] = arr[i];
        }
        checksum_t check = genCheckSum(tgt);
        tgt[1] = check >> 8;
        tgt[2] = check & 0xFF;
    }
}
