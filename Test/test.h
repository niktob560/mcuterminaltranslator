#include <cxxtest/TestSuite.h>
#include "translator.hpp"
#include <stdint.h>
#include <iostream>

bool called0 = false;
void functest0()
{
    called0 = 1;
}

bool called1 = false;
void functest1()
{
    called1 = 1;
}


class translatorTest : public CxxTest::TestSuite
{
public:

    void testCheckSum(void)
    {
        uint8_t* c = (uint8_t*)calloc(sizeof(uint8_t), 10);
        c[0] = 0;
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 0);
        c[0] = 1;
        c[1] = 0;
        c[2] = 0;
        c[3] = 1;
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 1);
        c[0] = 2;
        c[3] = 1;
        c[4] = 1;
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 257);
        c[3] = 2;
        c[4] = 1;
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 258);
        c[3] = 1;
        c[4] = 2;
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 513);
        c[0] = 3;
        c[3] = 1;
        c[4] = 2;
        c[5] = 10;
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 523);
        c[0] = 4;
        c[3] = 1;
        c[4] = 2;
        c[5] = 10;
        c[6] = 10;
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 1 | (2 << 8) | 10 | (10 << 8));

        free(c);
    }

    void testGetType(void)
    {
        uint8_t *c = (uint8_t*)calloc(sizeof(uint8_t), 10);
        c[0] = translator::TYPE_ARR << 6;
        TS_ASSERT_EQUALS(translator::getType(c), translator::TYPE_ARR);

        free(c);
    }

    void testEquals(void)
    {
        uint8_t *c0 =(uint8_t*)calloc(sizeof(uint8_t), 10),
                *c1 =(uint8_t*)calloc(sizeof(uint8_t), 10);
        for(int i = 0; i < 10; i++)
        {
            c0[i] = i;
            c1[i] = i;
        }
        c0[0] &= ~translator::LEN_MASK;
        c0[0] |= 7;
        c1[0] = c0[0];
        TS_ASSERT(translator::equals(c0, c1));

        for(int i = 0; i < 10; i++)
        {
            c1[i] = 10 - i;
        }
        TS_ASSERT(!translator::equals(c0, c1));
        c1[0] = c0[0];
        c1[1] = c0[1];
        c1[2] = c0[2];
        TS_ASSERT(!translator::equals(c0, c1));
    }

    // void testGetPayload(void)
    // {
    //     uint8_t *c = (uint8_t*)calloc(sizeof(uint8_t), 10);
    //     c[0] = 3;
    //     c[1] = 0;
    //     c[2] = 0;
    //     c[3] = 10;
    //     c[4] = 11;
    //     c[5] = 12;
    //     uint8_t *payload = (uint8_t*)calloc(sizeof(uint8_t), 10);
    //     translator::getPayload(c, payload);
    // }
};
