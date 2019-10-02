#include <cxxtest/TestSuite.h>
#include "strbase.hpp"
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
    void testContains(void)
    {
        char * c = (char *)"aaa";
        TS_ASSERT_EQUALS(translator::contains(c, 'a'), 1);
        TS_ASSERT_EQUALS(translator::contains(c, 'b'), 0);
        TS_ASSERT_EQUALS(translator::contains(c, 0), 0);
    }

    void testCharAt(void)
    {
        char * c = (char *)"aaa";
        TS_ASSERT_EQUALS(translator::charAt(c, 'a'), 0);
        TS_ASSERT_EQUALS(translator::charAt(c, 'b'), translator::str_NAN);
        TS_ASSERT_EQUALS(translator::charAt(c, 0), translator::str_NAN);
    }

    void testLastCharAt(void)
    {
        char * c = (char *)"aaa";
        TS_ASSERT_EQUALS(translator::lastCharAt(c, 'a'), 2);
        TS_ASSERT_EQUALS(translator::lastCharAt(c, 'b'), translator::str_NAN);
        TS_ASSERT_EQUALS(translator::lastCharAt(c, 0), translator::str_NAN);
    }

    void testEquals(void)
    {
        char * c1 = (char *)"aaa";
        char * c2 = (char *)"bbb";
        char * c3 = (char *)"a";
        char * c4 = (char *)"aaa";

        TS_ASSERT_EQUALS(translator::equals(c1, c2), 0);
        TS_ASSERT_EQUALS(translator::equals(c1, c4), 1);
        TS_ASSERT_EQUALS(translator::equals(c1, c3), 0);
        TS_ASSERT_EQUALS(translator::equals(c2, c3), 0);
        TS_ASSERT_EQUALS(translator::equals(c3, c4), 0);
        TS_ASSERT_EQUALS(translator::equals(c3, c3), 1);
    }

    void testSubstr(void)
    {
        char * c1 = (char*)"0123456789";
        char * c2 = (char*)calloc(sizeof(char), 3);
        translator::substr(c1, c2, 1, 5);
        TS_ASSERT(translator::equals(c2, (const char*)"12345") == 1);

        translator::substr(c1, c2, 1, 3);
        TS_ASSERT(translator::equals(c2, (const char*)"123") == 1);

        translator::substr(c1, c2, 1, 4);
        TS_ASSERT(strlen(c2) == 4);

        free(c2);
    }

    void testSplit(void)
    {
        char * c = (char*)"|aaa|";
        char * tgt = (char*)calloc(sizeof(char*), 4);
        translator::split(c, tgt, '|');
        TS_ASSERT(translator::equals(tgt, (const char*)"aaa"));
        c = (char*)"||aaa||";
        translator::split(c, tgt, '|');
        TS_ASSERT(translator::equals(tgt, (const char*)"|aaa|"));
    }



    void testParseCmd(void)
    {
        const int len = 3;
        void (* funcArr [len])();
        funcArr[0] = (void(*)())(functest0);
        funcArr[1] = (void(*)())(functest1);
        char **names = (char**)calloc(sizeof(char*), len);
        names[0] = (char*)"aaa";
        names[1] = (char*)"abc";
        char *cmd0 = (char*)"|aaa|";
        translator::parseCmd(cmd0, names, funcArr);
        TS_ASSERT(called0);

        called0 = false;
        cmd0 = (char*)"|abc|";
        translator::parseCmd(cmd0, names, funcArr);
        TS_ASSERT(called1);
        TS_ASSERT(!called0);
    }
};
