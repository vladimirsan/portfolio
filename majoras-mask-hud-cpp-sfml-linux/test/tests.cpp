/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "test/ClockTests.h"

static ClockTests suite_ClockTests;

static CxxTest::List Tests_ClockTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_ClockTests( "test/ClockTests.h", 8, "ClockTests", suite_ClockTests, Tests_ClockTests );

static class TestDescription_ClockTests_testAccelerationGetter : public CxxTest::RealTestDescription {
public:
 TestDescription_ClockTests_testAccelerationGetter() : CxxTest::RealTestDescription( Tests_ClockTests, suiteDescription_ClockTests, 23, "testAccelerationGetter" ) {}
 void runTest() { suite_ClockTests.testAccelerationGetter(); }
} testDescription_ClockTests_testAccelerationGetter;

static class TestDescription_ClockTests_testAdditionUpdate : public CxxTest::RealTestDescription {
public:
 TestDescription_ClockTests_testAdditionUpdate() : CxxTest::RealTestDescription( Tests_ClockTests, suiteDescription_ClockTests, 31, "testAdditionUpdate" ) {}
 void runTest() { suite_ClockTests.testAdditionUpdate(); }
} testDescription_ClockTests_testAdditionUpdate;

static class TestDescription_ClockTests_testMinuteChange : public CxxTest::RealTestDescription {
public:
 TestDescription_ClockTests_testMinuteChange() : CxxTest::RealTestDescription( Tests_ClockTests, suiteDescription_ClockTests, 39, "testMinuteChange" ) {}
 void runTest() { suite_ClockTests.testMinuteChange(); }
} testDescription_ClockTests_testMinuteChange;

static class TestDescription_ClockTests_testHourChange : public CxxTest::RealTestDescription {
public:
 TestDescription_ClockTests_testHourChange() : CxxTest::RealTestDescription( Tests_ClockTests, suiteDescription_ClockTests, 58, "testHourChange" ) {}
 void runTest() { suite_ClockTests.testHourChange(); }
} testDescription_ClockTests_testHourChange;

static class TestDescription_ClockTests_testNormalSecondsConverter : public CxxTest::RealTestDescription {
public:
 TestDescription_ClockTests_testNormalSecondsConverter() : CxxTest::RealTestDescription( Tests_ClockTests, suiteDescription_ClockTests, 73, "testNormalSecondsConverter" ) {}
 void runTest() { suite_ClockTests.testNormalSecondsConverter(); }
} testDescription_ClockTests_testNormalSecondsConverter;

static class TestDescription_ClockTests_testSlowSecondsConverter : public CxxTest::RealTestDescription {
public:
 TestDescription_ClockTests_testSlowSecondsConverter() : CxxTest::RealTestDescription( Tests_ClockTests, suiteDescription_ClockTests, 80, "testSlowSecondsConverter" ) {}
 void runTest() { suite_ClockTests.testSlowSecondsConverter(); }
} testDescription_ClockTests_testSlowSecondsConverter;

static class TestDescription_ClockTests_testDayToNight : public CxxTest::RealTestDescription {
public:
 TestDescription_ClockTests_testDayToNight() : CxxTest::RealTestDescription( Tests_ClockTests, suiteDescription_ClockTests, 87, "testDayToNight" ) {}
 void runTest() { suite_ClockTests.testDayToNight(); }
} testDescription_ClockTests_testDayToNight;

static class TestDescription_ClockTests_testNewDay : public CxxTest::RealTestDescription {
public:
 TestDescription_ClockTests_testNewDay() : CxxTest::RealTestDescription( Tests_ClockTests, suiteDescription_ClockTests, 107, "testNewDay" ) {}
 void runTest() { suite_ClockTests.testNewDay(); }
} testDescription_ClockTests_testNewDay;

#include <cxxtest/Root.cpp>
