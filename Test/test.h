#include <cxxtest/TestSuite.h>
#include "strbase.hpp"

class translatorTest : public CxxTest::TestSuite
{
public:
    void testCharSearch( void )
    {
        char * c = (char *)"aaa";
        TS_ASSERT_EQUALS(translator::contains(c, 'a'), 1);
        TS_ASSERT_EQUALS(translator::contains(c, 'b'), 0);
        TS_ASSERT_EQUALS(translator::contains(c, 0), 0);
        TS_ASSERT_EQUALS(translator::charAt(c, 'a'), 0);
        TS_ASSERT_EQUALS(translator::lastCharAt(c, 'a'), 2);
    }
};
