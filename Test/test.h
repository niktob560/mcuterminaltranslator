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
        uint8_t *c = (uint8_t*)alloca(sizeof(uint8_t)* 10);
        c[0] = translator::TYPE_ARR << 6;
        TS_ASSERT_EQUALS(translator::getType(c), translator::TYPE_ARR);
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

    void testGetPayload(void)
    {
        uint8_t *c = (uint8_t*)calloc(sizeof(uint8_t), 10),
                *payload_const = (uint8_t*)calloc(sizeof(uint8_t), 7);
        c[0] = 3;
        c[1] = 0;
        c[2] = 0;
        c[3] = 10;
        c[4] = 11;
        c[5] = 12;
        payload_const[0] = c[3];
        payload_const[1] = c[4];
        payload_const[2] = c[5];
        uint8_t *payload = (uint8_t*)calloc(sizeof(uint8_t), 10);
        translator::getPayload(c, payload);
        TS_ASSERT(translator::equals(payload, payload_const));
    }

    void testGetLen(void)
    {
        uint8_t c = 10;
        TS_ASSERT_EQUALS(translator::getLen(&c), 10);
        c = 10 | (translator::TYPE_ARR << 6);
        TS_ASSERT_EQUALS(translator::getLen(&c), 10);
    }

    void testParseCmd(void)
    {
        uint8_t *c = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        c[0] = translator::getZeroByte(translator::TYPE_CMD, 2);
        TS_ASSERT_EQUALS(translator::parseCmd(c, 0), translator::TYPE_BAD_LEN);

        c[0] = translator::getZeroByte(translator::TYPE_VAR, 1);
        TS_ASSERT_EQUALS(translator::parseCmd(c, 0), translator::TYPE_BAD_TYPE);

        c[0] = translator::getZeroByte(translator::TYPE_CMD, 1);
        TS_ASSERT_EQUALS(translator::parseCmd(c, 0), translator::TYPE_BAD_CHECKSUM);
        void (*funcArr[10])();
        funcArr[0] = functest0;
        called0 = false;
        c[3] = 0;
        c[1] = ((translator::genCheckSum(c) >> 8) & 0xFF);
        c[2] = (translator::genCheckSum(c) & 0xFF);
        TS_ASSERT_EQUALS(translator::parseCmd(c, funcArr), translator::TYPE_CMD);
        TS_ASSERT(called0);
    }

    void testGetZeroByte(void)
    {
        TS_ASSERT_EQUALS(translator::getZeroByte(1, 1), (1 << 6) | 1);
        TS_ASSERT_EQUALS(translator::getZeroByte(1, 2), (1 << 6) | 2);
        TS_ASSERT_EQUALS(translator::getZeroByte(1, 1), (1 << 6) | 1);
        TS_ASSERT_EQUALS(translator::getZeroByte(255, 2), (3 << 6) | 2);
    }

    void testGenerateCmd(void)
    {
        uint8_t *pack = (uint8_t*) alloca(sizeof(uint8_t) * 4),
                *ref  = (uint8_t*) alloca(sizeof(uint8_t) * 4);
        translator::generateCmd(1, pack);
        ref[0] = translator::getZeroByte(translator::TYPE_CMD, 1);
        ref[3] = 1;
        ref[1] = translator::genCheckSum(ref) >> 8;
        ref[2] = translator::genCheckSum(ref) & 0xFF;
        TS_ASSERT(translator::equals(pack, ref));
    }

    void testGetVarId(void)
    {
        uint8_t *pack = (uint8_t*)alloca(sizeof(uint8_t) * 4);
        pack[0] = translator::getZeroByte(translator::TYPE_VAR, 2);
        pack[3] = 1;
        pack[4] = 1;
        pack[1] = translator::genCheckSum(pack) >> 8;
        pack[2] = translator::genCheckSum(pack) & 0xFF;
        TS_ASSERT_EQUALS(translator::getVarId(pack), 1);
    }

    void testValidate(void)
    {
        uint8_t *p = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        p[0] = translator::getZeroByte(translator::TYPE_CMD, 1);
        p[3] = 0;
        p[1] = translator::genCheckSum(p) >> 8;
        p[2] = translator::genCheckSum(p) & 0xFF;
        TS_ASSERT(translator::validate(p));

        p[0] = translator::getZeroByte(translator::TYPE_CMD, 2);
        p[1] = translator::genCheckSum(p) >> 8;
        p[2] = translator::genCheckSum(p) & 0xFF;
        TS_ASSERT(!translator::validate(p));

        p[0] = translator::getZeroByte(translator::TYPE_VAR, 2);
        p[3] = 10;
        p[4] = 100;
        p[1] = translator::genCheckSum(p) >> 8;
        p[2] = translator::genCheckSum(p) & 0xFF;
        TS_ASSERT(translator::validate(p));

        p[0] = translator::getZeroByte(translator::TYPE_VAR, 1);
        p[1] = translator::genCheckSum(p) >> 8;
        p[2] = translator::genCheckSum(p) & 0xFF;
        TS_ASSERT(!translator::validate(p));

        p[0] = translator::getZeroByte(translator::TYPE_ARR, 1);
        p[1] = translator::genCheckSum(p) >> 8;
        p[2] = translator::genCheckSum(p) & 0xFF;
        TS_ASSERT(!translator::validate(p));
    }

    void testGenVar(void)
    {
        uint8_t *p = (uint8_t*)alloca(sizeof(uint8_t) * 10),
                *ref = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        ref[0] = translator::getZeroByte(translator::TYPE_VAR, 2);
        ref[3] = 1;
        ref[4] = 1;
        ref[1] = translator::genCheckSum(ref) >> 8;
        ref[2] = translator::genCheckSum(ref) & 0xFF;
        uint8_t *i = (uint8_t*)alloca(sizeof(uint8_t));
        *i = 1;
        translator::generateVar(1, 1, i, p);

        TS_ASSERT(translator::equals(p, ref));
    }

    void testParseVar(void)
    {
        uint8_t* array  = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        uint8_t* p      = (uint8_t*)alloca(sizeof(uint8_t) * 10);

        array[0] = 0;
        array[1] = 0;
        array[2] = 22;

        translator::generateVar(1, 1, &array[2], p);
        TS_ASSERT_EQUALS(translator::parseVar(p, array, 1), translator::TYPE_VAR);
        TS_ASSERT_EQUALS(array[1], array[2]);
    }
};
