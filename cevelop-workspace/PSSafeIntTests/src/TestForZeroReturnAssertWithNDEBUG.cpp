#include "TestForZeroReturnAssertWithNDEBUG.h"
#include "cute.h"

// cannot #define NDEBUG here, because of ODR, must use consistently on all configs
#include "psssafeint.h"
    using namespace psssint;

void thisIsATestForZeroReturnAssertWithNDEBUGTest() {
    constexpr auto divisor = 0_si8;
    auto divident = 1_si8;

#ifdef NDEBUG
    ASSERT_EQUAL(0_si8,divident/divisor);
    ASSERT_EQUAL(0_si8,divident /= divisor );
#else
  #ifdef PS_ASSERT_THROWS
    ASSERT_THROWS(divident/divisor, char const *);
  #else
    #ifdef PS_TEST_TRAP
    ASSERTM("cannot test trapping without NDEBUG set, change this to true to check for assert() behavior ",false);
    divident/divisor; // Assertion failed: (r != F{} && " division by zero"), function operator/, file ../src/psssafeint.h, line 517.
    #endif
  #endif
#endif

    //constexpr auto should_not_compile = 1_si8 / divisor; in Test.cpp
}

//static_assert(1_si8 / 0_si8 == 0_si8, "this should not compile");

void ModuloTestForZeroReturnAssertWithNDEBUGTest() {
    constexpr auto divisor = 0_ui8;
    auto divident = 1_ui8;

#ifdef NDEBUG
    ASSERT_EQUAL(0_ui8,divident % divisor);
    ASSERT_EQUAL(0_ui8,divident %= divisor );
#else
  #ifdef PS_ASSERT_THROWS
    ASSERT_THROWS(divident % divisor, char const *);
  #else
    #ifdef PS_TEST_TRAP
    ASSERTM("cannot test trapping without NDEBUG set, change this to true to check for assert() behavior ",false);
    divident % divisor; // Assertion failed: (r != F{} && " division by zero"), function operator/, file ../src/psssafeint.h, line 517.
    #endif
  #endif
#endif

    //constexpr auto should_not_compile = 1_ui8 % divisor; in Test.cpp
}

void ShiftLeftTestForZeroReturnAssertWithNDEBUGTest() {
    constexpr auto shiftby = 8_ui8;
    auto toshift = 0xff_ui8;

#ifdef NDEBUG
    ASSERT_EQUAL(0_ui8,toshift << shiftby);
    ASSERT_EQUAL(0_ui8,toshift <<= shiftby );
#else
  #ifdef PS_ASSERT_THROWS
    ASSERT_THROWS(toshift << shiftby, char const *);
  #else
    #ifdef PS_TEST_TRAP

    ASSERTM("cannot test trapping without NDEBUG set, change this to true to check for assert() behavior ",false);
    toshift << shiftby; // Assertion failed: (r != F{} && " division by zero"), function operator/, file ../src/psssafeint.h, line 517.
    #endif
  #endif
#endif

     //constexpr auto should_not_compile = 1_ui8 << shiftby; in Test.cpp
}
void ShiftRightTestForZeroReturnAssertWithNDEBUGTest() {
    constexpr auto shiftby = 8_ui8;
    auto toshift = 0xff_ui8;

#ifdef NDEBUG
    ASSERT_EQUAL(0_ui8,toshift >> shiftby);
    ASSERT_EQUAL(0_ui8,toshift >>= shiftby );
#else
#ifdef PS_ASSERT_THROWS
    ASSERT_THROWS(toshift >> shiftby, char const *);
#else
    #ifdef PS_TEST_TRAP

    ASSERTM("cannot test trapping without NDEBUG set, change this to true to check for assert() behavior ",false);
    toshift >> shiftby; // Assertion failed: (r != F{} && " division by zero"), function operator/, file ../src/psssafeint.h, line 517.
    #endif
  #endif
#endif
     //constexpr auto should_not_compile = 1_ui8 >> shiftby; in Test.cpp
}


cute::suite make_suite_TestForZeroReturnAssertWithNDEBUG() {
	cute::suite s { };
	s.push_back(CUTE(thisIsATestForZeroReturnAssertWithNDEBUGTest));
	s.push_back(CUTE(ModuloTestForZeroReturnAssertWithNDEBUGTest));
	s.push_back(CUTE(ShiftLeftTestForZeroReturnAssertWithNDEBUGTest));
	s.push_back(CUTE(ShiftRightTestForZeroReturnAssertWithNDEBUGTest));
	return s;
}
