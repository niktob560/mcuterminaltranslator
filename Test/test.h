#include <cxxtest/TestSuite.h>
#include "translator.hpp"
#include <stdint.h>
#include <iostream>
#include <bitset>

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
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 1);
        c[0] = 1;
        c[1] = 0;
        c[2] = 0;
        c[3] = 1;
        #ifdef USE_MULTIDEVICE
            c[4] = 0;
        #endif
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 258);
        c[0] = 2;
        c[3] = 1;
        c[4] = 1;
        #ifdef USE_MULTIDEVICE
            c[5] = 0;
        #endif
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 260);
        c[0] = 2;
        c[3] = 2;
        c[4] = 1;
        #ifdef USE_MULTIDEVICE
            c[5] = 0;
        #endif
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 516);
        c[0] = 2;
        c[3] = 1;
        c[4] = 2;
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 261);
        c[0] = 3;
        c[3] = 1;
        c[4] = 2;
        c[5] = 10;
        #ifdef USE_MULTIDEVICE
            c[6] = 0;
        #endif
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 2822);
        c[0] = 4;
        c[3] = 1;
        c[4] = 2;
        c[5] = 10;
        c[6] = 10;
        #ifdef USE_MULTIDEVICE
            c[7] = 0;
        #endif
        TS_ASSERT_EQUALS(translator::genCheckSum(c), 2833);

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
        // c0[0] &= ~translator::LEN_MASK;
        c0[0] = translator::getZeroByte(translator::TYPE_VAR, 1);
        // c0[0] |= 7;
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
        c[4] = 0;
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
        uint8_t *package = (uint8_t*) alloca(sizeof(uint8_t) * 4),
                *ref  = (uint8_t*) alloca(sizeof(uint8_t) * 4);
        translator::generateCmd(2, package);
        ref[0] = translator::getZeroByte(translator::TYPE_CMD, 1);
        #ifdef USE_MULTIDEVICE
            ref[3] = translator::myId;
            ref[4] = 2;
        #else
            ref[3] = 2;
        #endif
        ref[1] = translator::genCheckSum(ref) >> 8;
        ref[2] = translator::genCheckSum(ref) & 0xFF;
        TS_ASSERT(translator::equals(package, ref));
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
        uint8_t *p      = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        uint8_t *ref    = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        p[1] = 0;
        p[2] = 0;
        ref[1] = 0;
        ref[0] = translator::getZeroByte(translator::TYPE_VAR, 2);
        #ifdef USE_MULTIDEVICE
            ref[3] = translator::myId;
            ref[4] = 1;
            ref[5] = 1;
        #else
            ref[3] = 1;
            ref[4] = 1;
            ref[5] = 0;
        #endif
        translator::checksum_t check = translator::genCheckSum(ref);
        ref[1] = check >> 8;
        ref[2] = check & 0xFF;
        uint8_t *i = (uint8_t*)alloca(sizeof(uint8_t));
        *i = 1;
        // uint8_t i = 1;
        translator::generateVar(1, 1, i, p);//{10000010}{c}{c}{dev id}{1}{1}

        TS_ASSERT(translator::equals(p, ref));

        
        uint16_t* ii = (uint16_t*)alloca(sizeof(uint16_t));
        *ii = 0xFAFB;
        ref[0] = translator::getZeroByte(translator::TYPE_VAR, 3);
        #ifdef USE_MULTIDEVICE
            ref[3] = translator::myId;
            ref[4] = 2;
            ref[5] = 0xFA;
            ref[6] = 0xFB;
        #else
            ref[3] = 2;
            ref[4] = 0xFA;
            ref[5] = 0xFB;
        #endif
        ref[1] = translator::genCheckSum(ref) >> 8;
        ref[2] = translator::genCheckSum(ref) & 0xFF;
        translator::generateVar(2, 2, (uint8_t*)ii, p);
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
        
        uint16_t* ii = (uint16_t*)alloca(sizeof(uint16_t));
        *ii = 0xFAFB;
        
        translator::generateVar(0, 2, (uint8_t*)ii, p);
        
        TS_ASSERT_EQUALS(translator::parseVar(p, array, 1), translator::TYPE_VAR);
        TS_ASSERT_EQUALS(array[0], 0xFA);
        TS_ASSERT_EQUALS(array[1], 0xFB);
    }
    
    void testGenArr(void)
    {
        uint8_t* p = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        uint8_t* ref = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        uint8_t* arr0 = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        arr0[0] = 10;
        arr0[1] = 20;
        ref[0] = translator::getZeroByte(translator::TYPE_ARR, 3);
        #ifdef USE_MULTIDEVICE
            ref[3] = translator::myId;
            ref[4] = 1;
            ref[5] = arr0[0];
            ref[6] = arr0[1];
        #else
            ref[3] = 1;
            ref[4] = arr0[0];
            ref[5] = arr0[1];
        #endif
        ref[1] = translator::genCheckSum(ref) >> 8;
        ref[2] = translator::genCheckSum(ref) & 0xFF;
        
        
        translator::generateArr(1, 2, 1, arr0, p);
        // TS_ASSERT(translator::equals(p, ref));
        TS_ASSERT_EQUALS(p[0], ref[0]);
        TS_ASSERT_EQUALS(p[1], ref[1]);
        TS_ASSERT_EQUALS(p[2], ref[2]);
        TS_ASSERT_EQUALS(p[3], ref[3]);
        TS_ASSERT_EQUALS(p[4], ref[4]);
        TS_ASSERT_EQUALS(p[5], ref[5]);
        
        uint16_t* arr1 = (uint16_t*)alloca(sizeof(uint16_t) * 10);
        arr1[0] = 10;
        arr1[1] = 20;
        ref[0] = translator::getZeroByte(translator::TYPE_ARR, 5);
        #ifdef USE_MULTIDEVICE
            ref[3] = translator::myId;
            ref[4] = 1;
            ref[5] = arr1[0] >> 8;
            ref[6] = arr1[0] & 0xFF;
            ref[7] = arr1[1] >> 8;
            ref[8] = arr1[1] & 0xFF;
        #else
        ref[3] = 1;
        ref[4] = arr1[0] >> 8;
        ref[5] = arr1[0] & 0xFF;
        ref[6] = arr1[1] >> 8;
        ref[7] = arr1[1] & 0xFF;
        #endif
        ref[1] = translator::genCheckSum(ref) >> 8;
        ref[2] = translator::genCheckSum(ref) & 0xFF;
        
        translator::generateArr(1, 2, 2, (uint8_t*)arr1, p);
        
        TS_ASSERT_EQUALS(p[0], ref[0]);
        TS_ASSERT_EQUALS(p[1], ref[1]);
        TS_ASSERT_EQUALS(p[2], ref[2]);
        TS_ASSERT_EQUALS(p[3], ref[3]);
        TS_ASSERT_EQUALS(p[4], ref[4]);
        TS_ASSERT_EQUALS(p[5], ref[5]);
    }
    
    void testParseArr(void)
    {
        uint8_t* p = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        uint8_t* arr = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        memset(arr, 0, 10);
        for(int i = 0; i < 10; i++)
            arr[i] = i + 1;
        translator::generateArr(0, 2, 1, arr, p);
        uint8_t* tgt = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        translator::parseArr(p, &tgt);
        TS_ASSERT_EQUALS(arr[0], tgt[0]);
        TS_ASSERT_EQUALS(arr[1], tgt[1]);
    }


    void testCmd(void)
    {
        uint8_t* tgt = (uint8_t*)alloca(sizeof(uint8_t) * 10);
        translator::generateCmd(1, tgt);
        TS_ASSERT(translator::validate(tgt));
        TS_ASSERT_EQUALS(translator::parseCmd(tgt), 1);
    }
};
