#include "translator.hpp"

namespace translator
{

    using namespace std;

    //generate checksum for char array
    checksum_t genCheckSum(const uint8_t* c)
    {
        checksum_t ret = 0;
        uint8_t len = c[0] & LEN_MASK;
        // cout << "len: " << (int)len << endl;
        // for(int i = 0; i < len + 3; i++)
        // {
        //     cout << (int)c[i];
        // }
        // cout << endl;
        for(uint8_t i = 0; i < len; i++)
        {
            ret |= (c[3 + i]) << (8 * ((i % 2) == 1));
            // cout << "\nAdding: " << (int)c[3 + i] << endl;
        }
        return ret;
    }

    //get type of package
    uint8_t getType(uint8_t *package)
    {
        return ((package[0] & (~LEN_MASK)) >> 6);
    }


    //parse input package, get payload, return type of package
    uint8_t parsePacket(uint8_t *package, uint8_t *payloadto)
    {
        uint8_t type = package[0] & (~LEN_MASK);
        if(type != TYPE_ARR && type != TYPE_CMD && type != TYPE_VAR)
            return TYPE_BAD_TYPE;

        uint8_t len = package[0] & LEN_MASK;
        if(len == 0)
            return TYPE_BAD_LEN;

        checksum_t checksum = (package[1] << 8) | package[2];
        if(genCheckSum(package) != checksum)
            return TYPE_BAD_CHECKSUM;

        package += 3;
        while(len > 0)
        {
            *payloadto = *package;
            payloadto++;
            package++;
        }
        *payloadto = *package;
        return type;
    }


    //parse cmd from string |cmd| and call it from funcArr
    void parseCmd(uint8_t *from, char** names, void (*funcArr [])())
    {

    }
}
