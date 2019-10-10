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
 TestDescription_suite_translatorTest_testEquals() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 65, "testEquals" ) {}
 void runTest() { suite_translatorTest.testEquals(); }
} testDescription_suite_translatorTest_testEquals;

static class TestDescription_suite_translatorTest_testGetPayload : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGetPayload() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 90, "testGetPayload" ) {}
 void runTest() { suite_translatorTest.testGetPayload(); }
} testDescription_suite_translatorTest_testGetPayload;

static class TestDescription_suite_translatorTest_testGetLen : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGetLen() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 108, "testGetLen" ) {}
 void runTest() { suite_translatorTest.testGetLen(); }
} testDescription_suite_translatorTest_testGetLen;

static class TestDescription_suite_translatorTest_testParseCmd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testParseCmd() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 116, "testParseCmd" ) {}
 void runTest() { suite_translatorTest.testParseCmd(); }
} testDescription_suite_translatorTest_testParseCmd;

static class TestDescription_suite_translatorTest_testGetZeroByte : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGetZeroByte() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 137, "testGetZeroByte" ) {}
 void runTest() { suite_translatorTest.testGetZeroByte(); }
} testDescription_suite_translatorTest_testGetZeroByte;

static class TestDescription_suite_translatorTest_testGenerateCmd : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGenerateCmd() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 145, "testGenerateCmd" ) {}
 void runTest() { suite_translatorTest.testGenerateCmd(); }
} testDescription_suite_translatorTest_testGenerateCmd;

static class TestDescription_suite_translatorTest_testGetVarId : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGetVarId() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 157, "testGetVarId" ) {}
 void runTest() { suite_translatorTest.testGetVarId(); }
} testDescription_suite_translatorTest_testGetVarId;

static class TestDescription_suite_translatorTest_testValidate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testValidate() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 168, "testValidate" ) {}
 void runTest() { suite_translatorTest.testValidate(); }
} testDescription_suite_translatorTest_testValidate;

static class TestDescription_suite_translatorTest_testGenVar : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testGenVar() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 200, "testGenVar" ) {}
 void runTest() { suite_translatorTest.testGenVar(); }
} testDescription_suite_translatorTest_testGenVar;

static class TestDescription_suite_translatorTest_testParseVar : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_translatorTest_testParseVar() : CxxTest::RealTestDescription( Tests_translatorTest, suiteDescription_translatorTest, 227, "testParseVar" ) {}
 void runTest() { suite_translatorTest.testParseVar(); }
} testDescription_suite_translatorTest_testParseVar;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
