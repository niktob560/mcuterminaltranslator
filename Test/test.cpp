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
CxxTest::StaticSuiteDescription suiteDescription_translatorTest( "Test/test.h", 20, "translatorTest", suite_translatorTest, Tests_translatorTest );

static class TestDescription_suite_translatorTest_testCheckSum : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testCheckSum() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 24, "testCheckSum" ) {}
 void runTest() { suite_translatorTest.testCheckSum(); }
} testDescription_suite_translatorTest_testCheckSum;

static class TestDescription_suite_translatorTest_testGetType : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGetType() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 76, "testGetType" ) {}
 void runTest() { suite_translatorTest.testGetType(); }
} testDescription_suite_translatorTest_testGetType;

static class TestDescription_suite_translatorTest_testEquals : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testEquals() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 83, "testEquals" ) {}
 void runTest() { suite_translatorTest.testEquals(); }
} testDescription_suite_translatorTest_testEquals;

static class TestDescription_suite_translatorTest_testGetLen : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGetLen() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 109, "testGetLen" ) {}
 void runTest() { suite_translatorTest.testGetLen(); }
} testDescription_suite_translatorTest_testGetLen;

static class TestDescription_suite_translatorTest_testParseCmd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testParseCmd() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 117, "testParseCmd" ) {}
 void runTest() { suite_translatorTest.testParseCmd(); }
} testDescription_suite_translatorTest_testParseCmd;

static class TestDescription_suite_translatorTest_testGetZeroByte : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGetZeroByte() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 139, "testGetZeroByte" ) {}
 void runTest() { suite_translatorTest.testGetZeroByte(); }
} testDescription_suite_translatorTest_testGetZeroByte;

static class TestDescription_suite_translatorTest_testGenerateCmd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGenerateCmd() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 147, "testGenerateCmd" ) {}
 void runTest() { suite_translatorTest.testGenerateCmd(); }
} testDescription_suite_translatorTest_testGenerateCmd;

static class TestDescription_suite_translatorTest_testValidate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testValidate() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 164, "testValidate" ) {}
 void runTest() { suite_translatorTest.testValidate(); }
} testDescription_suite_translatorTest_testValidate;

static class TestDescription_suite_translatorTest_testGenVar : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGenVar() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 196, "testGenVar" ) {}
 void runTest() { suite_translatorTest.testGenVar(); }
} testDescription_suite_translatorTest_testGenVar;

static class TestDescription_suite_translatorTest_testParseVar : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testParseVar() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 243, "testParseVar" ) {}
 void runTest() { suite_translatorTest.testParseVar(); }
} testDescription_suite_translatorTest_testParseVar;

static class TestDescription_suite_translatorTest_testGenArr : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGenArr() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 266, "testGenArr" ) {}
 void runTest() { suite_translatorTest.testGenArr(); }
} testDescription_suite_translatorTest_testGenArr;

static class TestDescription_suite_translatorTest_testParseArr : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testParseArr() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 328, "testParseArr" ) {}
 void runTest() { suite_translatorTest.testParseArr(); }
} testDescription_suite_translatorTest_testParseArr;

static class TestDescription_suite_translatorTest_testCmd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testCmd() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 343, "testCmd" ) {}
 void runTest() { suite_translatorTest.testCmd(); }
} testDescription_suite_translatorTest_testCmd;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
