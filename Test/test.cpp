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
CxxTest::StaticSuiteDescription suiteDescription_translatorTest( "Test/test.h", 19, "translatorTest", suite_translatorTest, Tests_translatorTest );

static class TestDescription_suite_translatorTest_testCheckSum : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testCheckSum() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 23, "testCheckSum" ) {}
 void runTest() { suite_translatorTest.testCheckSum(); }
} testDescription_suite_translatorTest_testCheckSum;

static class TestDescription_suite_translatorTest_testGetType : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGetType() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 58, "testGetType" ) {}
 void runTest() { suite_translatorTest.testGetType(); }
} testDescription_suite_translatorTest_testGetType;

static class TestDescription_suite_translatorTest_testEquals : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testEquals() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 67, "testEquals" ) {}
 void runTest() { suite_translatorTest.testEquals(); }
} testDescription_suite_translatorTest_testEquals;

static class TestDescription_suite_translatorTest_testGetPayload : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGetPayload() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 92, "testGetPayload" ) {}
 void runTest() { suite_translatorTest.testGetPayload(); }
} testDescription_suite_translatorTest_testGetPayload;

static class TestDescription_suite_translatorTest_testGetLen : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGetLen() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 110, "testGetLen" ) {}
 void runTest() { suite_translatorTest.testGetLen(); }
} testDescription_suite_translatorTest_testGetLen;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
