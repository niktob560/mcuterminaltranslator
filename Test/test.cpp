/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_translatorTest_init = false;
#include "/home/nikto_b/Documents/C++/mcuterminaltranslator/Test/test.h"

static translatorTest suite_translatorTest;

static CxxTest::List Tests_translatorTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_translatorTest( "Test/test.h", 4, "translatorTest", suite_translatorTest, Tests_translatorTest );

static class TestDescription_suite_translatorTest_testCharSearch : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testCharSearch() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 7, "testCharSearch" ) {}
 void runTest() { suite_translatorTest.testCharSearch(); }
} testDescription_suite_translatorTest_testCharSearch;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
