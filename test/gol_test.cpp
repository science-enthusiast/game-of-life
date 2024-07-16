// Tests for Conway's Game of Life
// Implemented by Hariprasad Kannan
// July 2024
// Requires C++17 or later.

#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TestRunner.h>

#include "../src/game_of_life.h"
#include "../src/test_helper.h"

class GolTestOne : public CppUnit::TestCase {
  CPPUNIT_TEST_SUITE(GolTestOne);
  CPPUNIT_TEST(testCaseOne);
  CPPUNIT_TEST_SUITE_END();

 public:
  void testCaseOne() {
    CPPUNIT_ASSERT(gol::testOneIter("input/gol_input.txt", "test/gol_input_test.txt"));
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION(GolTestOne);

int main(int argc, char **argv) {
  CppUnit::TextUi::TestRunner runner;
  CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  
  runner.addTest(registry.makeTest());
  bool wasSuccessful = runner.run();

  return !wasSuccessful;
}

