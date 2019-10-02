#include <cxxtest/TestSuite.h>
#include "strbase.hpp"

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
    }
};
