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

static class TestDescription_suite_translatorTest_testContains : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testContains() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 22, "testContains" ) {}
 void runTest() { suite_translatorTest.testContains(); }
} testDescription_suite_translatorTest_testContains;

static class TestDescription_suite_translatorTest_testCharAt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testCharAt() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 30, "testCharAt" ) {}
 void runTest() { suite_translatorTest.testCharAt(); }
} testDescription_suite_translatorTest_testCharAt;

static class TestDescription_suite_translatorTest_testLastCharAt : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testLastCharAt() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 38, "testLastCharAt" ) {}
 void runTest() { suite_translatorTest.testLastCharAt(); }
} testDescription_suite_translatorTest_testLastCharAt;

static class TestDescription_suite_translatorTest_testEquals : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testEquals() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 46, "testEquals" ) {}
 void runTest() { suite_translatorTest.testEquals(); }
} testDescription_suite_translatorTest_testEquals;

static class TestDescription_suite_translatorTest_testSubstr : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testSubstr() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 61, "testSubstr" ) {}
 void runTest() { suite_translatorTest.testSubstr(); }
} testDescription_suite_translatorTest_testSubstr;

static class TestDescription_suite_translatorTest_testSplit : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testSplit() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 77, "testSplit" ) {}
 void runTest() { suite_translatorTest.testSplit(); }
} testDescription_suite_translatorTest_testSplit;

static class TestDescription_suite_translatorTest_testParseCmd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testParseCmd() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 90, "testParseCmd" ) {}
 void runTest() { suite_translatorTest.testParseCmd(); }
} testDescription_suite_translatorTest_testParseCmd;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
