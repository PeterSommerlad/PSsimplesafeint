#include "TestForZeroReturnAssertWithNDEBUG.h"
#include "psssafeint.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "CodeGenBenchmark.h"
#include <type_traits>
#include <cstddef>



using namespace psssint::literals;

static_assert(0x8000_ui16 == 32768_ui16);

namespace _testing {

namespace compile_checks {
using namespace psssint;
template<auto ...value>
using consume_value = void;



#define concat_line_impl(A, B) A##_##B
#define concat_line(A, B) concat_line_impl(A,B)

#define check_does_compile(NOT, FROM, oper) \
namespace concat_line(NOT##_test, __LINE__) { \
        template<typename T, typename=void>\
        constexpr bool\
        expression_compiles{false};\
template<typename T> \
constexpr bool \
expression_compiles<T, consume_value<(T{} oper T{})> > {true};\
static_assert(NOT expression_compiles<FROM>, "should " #NOT " compile: " #FROM "{}" #oper #FROM "{}");\
} // namespace tag


// need to be on separate lines for disambiguation
check_does_compile(not,  si8 , <<  )
check_does_compile(   ,  ui8 , << )
check_does_compile(not,  si8 , >>  )
check_does_compile(   ,  ui8 , >> )
check_does_compile(not,  ui8 , + (1_ui8 << 010_ui8) + ) // too wide shift
check_does_compile(   ,  ui8 , + (1_ui8 << 7_ui8) + ) // not too wide shift
check_does_compile(not,  ui8 , + (0x80_ui8 >> 010_ui8) + ) // too wide shift
check_does_compile(   ,  ui8 , + (0x80_ui8 >> 7_ui8) + ) // not too wide shift
check_does_compile(not,  si8 ,  % ) // modulo not working
check_does_compile(   ,  ui8 , +( 1_ui8  / 1_ui8)+ ) // div
check_does_compile(   ,  ui8 , +( 11_ui8  % 3_ui8)+ ) // mod
check_does_compile(not,  ui8 , + 1_si8 + ) // cannot mix types
check_does_compile(   ,  ui8 , + 255_ui8 + 1_ui8 + ) // should we detect compile-time overflow?

check_does_compile(   , si8  , - 2_si8 - 127_si8 -)
#ifndef NDEBUG
// these checks rely on constexpr failures that are inhibited with NDEBUG
check_does_compile(not,  ui8 , + (1_ui8 << 010_ui8) + ) // too wide shift
check_does_compile(not,  ui8 , + (0x80_ui8 >> 010_ui8) + ) // too wide shift
check_does_compile(not,  ui8 ,  % ) // modulo 0
check_does_compile(not,  si8 ,  / ) // div 0
check_does_compile(not,  ui8 ,  / ) // div 0
#endif

}
#undef check_does_compile
#undef concat_line_impl
#undef concat_line

template<typename FROM, typename=void>
constexpr bool
from_int_compiles=false;

template<typename FROM>
constexpr bool
from_int_compiles<FROM,std::void_t<decltype(psssint::from_int(FROM{}))>> = true;

static_assert(from_int_compiles<unsigned char>);
static_assert(from_int_compiles<signed char>);
static_assert(from_int_compiles<short>);
static_assert(from_int_compiles<unsigned short>);
static_assert(from_int_compiles<int>);
static_assert(from_int_compiles<unsigned>);
static_assert(from_int_compiles<long>);
static_assert(from_int_compiles<unsigned long>);
static_assert(from_int_compiles<long long>);
static_assert(from_int_compiles<unsigned long long>);
static_assert(from_int_compiles<std::uint8_t>);
static_assert(from_int_compiles<std::uint16_t>);
static_assert(from_int_compiles<std::uint32_t>);
static_assert(from_int_compiles<std::uint64_t>);
static_assert(from_int_compiles<std::int8_t>);
static_assert(from_int_compiles<std::int16_t>);
static_assert(from_int_compiles<std::int32_t>);
static_assert(from_int_compiles<std::int64_t>);


static_assert(! from_int_compiles<bool>);
static_assert(! from_int_compiles<char>);
#ifdef __cpp_char8_t
static_assert(! from_int_compiles<char8_t>);
#endif
static_assert(! from_int_compiles<wchar_t>);
static_assert(! from_int_compiles<char16_t>);
static_assert(! from_int_compiles<char32_t>);

using namespace psssint;

static_assert(sizeof(long) == sizeof(long long)); // on my mac...
static_assert(42_si64 == from_int(42L));
static_assert(42_si64 == from_int(42LL));
static_assert(42_si32 == from_int(42));
static_assert(42_ui64 == from_int(42uL));
static_assert(42_ui64 == from_int(42uLL));
static_assert(42_ui32 == from_int(42u));



static_assert(detail_::is_safeint_v<ui8>);
static_assert(detail_::is_safeint_v<ui16>);
static_assert(detail_::is_safeint_v<ui32>);
static_assert(detail_::is_safeint_v<ui64>);
static_assert(detail_::is_safeint_v<si8>);
static_assert(detail_::is_safeint_v<si16>);
static_assert(detail_::is_safeint_v<si32>);
static_assert(detail_::is_safeint_v<si64>);
enum class enum4test{};
static_assert(!detail_::is_safeint_v<enum4test>);
static_assert(!detail_::is_safeint_v<std::byte>);
static_assert(!detail_::is_safeint_v<int>);
static_assert(std::is_same_v<unsigned,decltype(promote_keep_signedness(1_ui8)+1)>);
static_assert(std::is_same_v<unsigned,decltype(promote_keep_signedness(2_ui16)+1)>);
static_assert(std::is_same_v<int,decltype(promote_keep_signedness(1_si8))>);
static_assert(std::is_same_v<int,decltype(promote_keep_signedness(2_si16))>);
static_assert(std::is_same_v<uint8_t,std::underlying_type_t<ui8>>);
static_assert(std::is_same_v<uint16_t,std::underlying_type_t<ui16>>);


static_assert(promote_keep_signedness(0xffff_ui16 * 0xffff_ui16) == 0x1u); // wraps
static_assert(0xff_ui8 * 0xff_ui8 == 1_ui8);

// the following does not compile due to signed integer overflow on 32bit int
//static_assert(static_cast<uint16_t>(0xffffu)* static_cast<uint16_t>(0xffffu));

static_assert(0x7fff'ffff_si32+2_si32 == -0x7fff'ffff_si32);
//static_assert(0x7fff'ffff + 2); // doesn't compile, integer overflow
static_assert(-0x7fff'ffff_si32 - 2_si32 == 0x7fff'ffff_si32);
//static_assert(-0x7fff'ffff - 2); // doesn't compile, integer overflow

static_assert(std::is_same_v<int,decltype(+to_underlying(42_ui8))>);
static_assert(std::is_same_v<uint8_t,decltype(to_underlying(42_ui8))>);

static_assert(1_ui8 == from_int(uint8_t(1)));
static_assert(42_si8 == from_int_to<si8>(42));
//static_assert(32_ui8 == from_int(' ')); // does not compile
//static_assert(32_ui8 == from_int(u' ')); // does not compile
//static_assert(32_ui8 == from_int(U' ')); // does not compile
//static_assert(32_ui8 == from_int(L' ')); // does not compile
//static_assert(1_ui8 == from_int_to<ui8>(true)); // does not compile


// Test case from Frank Buergel (extended):
// missing sign extension from 32 to 64bit
// discovered further bugs wrt signed division
namespace {
constexpr auto v1_64 {  1_si64 };
constexpr auto v1_32 {  1_si32 };
constexpr auto v1_16 {  1_si16 };
constexpr auto v1_8  {  1_si8 };
constexpr auto v2_64 {  2_si64 };
constexpr auto v2_32 {  2_si32 };
constexpr auto v2_16 {  2_si16 };
constexpr auto v2_8  {  2_si8 };
constexpr auto vminus1_64 { -1_si64 };
constexpr auto vminus1_32 { -1_si32 };
constexpr auto vminus1_16 { -1_si16 };
constexpr auto vminus1_8  { -1_si8 };

constexpr auto min_8  { std::numeric_limits<si8 >::min() };
constexpr auto min_16 { std::numeric_limits<si16>::min() };
constexpr auto min_32 { std::numeric_limits<si32>::min() };
constexpr auto min_64 { std::numeric_limits<si64>::min() };
constexpr auto max_8  { std::numeric_limits<si8 >::max() };
constexpr auto max_16 { std::numeric_limits<si16>::max() };
constexpr auto max_32 { std::numeric_limits<si32>::max() };
constexpr auto max_64 { std::numeric_limits<si64>::max() };

}

static_assert(v1_64 + vminus1_64 == 0_si64 );
static_assert(v1_64 + vminus1_32 == 0_si64 );
static_assert(v1_64 + vminus1_16 == 0_si64 );
static_assert(v1_64 + vminus1_8  == 0_si64 );
static_assert(v1_32 + vminus1_64 == 0_si64 );
static_assert(v1_32 + vminus1_32 == 0_si32 );
static_assert(v1_32 + vminus1_16 == 0_si32 );
static_assert(v1_32 + vminus1_8  == 0_si32 );
static_assert(v1_16 + vminus1_64 == 0_si64 );
static_assert(v1_16 + vminus1_32 == 0_si32 );
static_assert(v1_16 + vminus1_16 == 0_si16 );
static_assert(v1_16 + vminus1_8  == 0_si16 );
static_assert(v1_8  + vminus1_64 == 0_si64 );
static_assert(v1_8  + vminus1_32 == 0_si32 );
static_assert(v1_8  + vminus1_16 == 0_si16 );
static_assert(v1_8  + vminus1_8  == 0_si8 );

static_assert(vminus1_64 +  v1_64== 0_si64 );
static_assert(vminus1_32 +  v1_64== 0_si64 );
static_assert(vminus1_16 +  v1_64== 0_si64 );
static_assert(vminus1_8  +  v1_64== 0_si64 );
static_assert(vminus1_64 +  v1_32== 0_si64 );
static_assert(vminus1_32 +  v1_32== 0_si32 );
static_assert(vminus1_16 +  v1_32== 0_si32 );
static_assert(vminus1_8  +  v1_32== 0_si32 );
static_assert(vminus1_64 +  v1_16== 0_si64 );
static_assert(vminus1_32 +  v1_16== 0_si32 );
static_assert(vminus1_16 +  v1_16== 0_si16 );
static_assert(vminus1_8  +  v1_16== 0_si16 );
static_assert(vminus1_64 +  v1_8 == 0_si64 );
static_assert(vminus1_32 +  v1_8 == 0_si32 );
static_assert(vminus1_16 +  v1_8 == 0_si16 );
static_assert(vminus1_8  +  v1_8 == 0_si8 );


// demonstrate wrapping:
static_assert(max_64 + v1_64 == min_64 );
static_assert(max_64 + v1_32 == min_64 );
static_assert(max_64 + v1_16 == min_64 );
static_assert(max_64 + v1_8  == min_64 );
static_assert(max_32 + v1_64 == 0x8000'0000_si64 );
static_assert(max_32 + v1_32 == min_32 );
static_assert(max_32 + v1_16 == min_32 );
static_assert(max_32 + v1_8  == min_32 );
static_assert(max_16 + v1_64 == 0x8000_si64 );
static_assert(max_16 + v1_32 == 0x8000_si32 );
static_assert(max_16 + v1_16 == min_16 );
static_assert(max_16 + v1_8  == min_16 );
static_assert(max_8  + v1_64 == 128_si64 );
static_assert(max_8  + v1_32 == 128_si32 );
static_assert(max_8  + v1_16 == 128_si16 );
static_assert(max_8  + v1_8  == min_8 );


static_assert(v1_64 - vminus1_64 == 2_si64 );
static_assert(v1_64 - vminus1_32 == 2_si64 );
static_assert(v1_64 - vminus1_16 == 2_si64 );
static_assert(v1_64 - vminus1_8  == 2_si64 );
static_assert(v1_32 - vminus1_64 == 2_si64 );
static_assert(v1_32 - vminus1_32 == 2_si32 );
static_assert(v1_32 - vminus1_16 == 2_si32 );
static_assert(v1_32 - vminus1_8  == 2_si32 );
static_assert(v1_16 - vminus1_64 == 2_si64 );
static_assert(v1_16 - vminus1_32 == 2_si32 );
static_assert(v1_16 - vminus1_16 == 2_si16 );
static_assert(v1_16 - vminus1_8  == 2_si16 );
static_assert(v1_8  - vminus1_64 == 2_si64 );
static_assert(v1_8  - vminus1_32 == 2_si32 );
static_assert(v1_8  - vminus1_16 == 2_si16 );
static_assert(v1_8  - vminus1_8  == 2_si8 );


static_assert(vminus1_64 - v1_64  == -2_si64 );
static_assert(vminus1_32 - v1_64  == -2_si64 );
static_assert(vminus1_16 - v1_64  == -2_si64 );
static_assert(vminus1_8  - v1_64  == -2_si64 );
static_assert(vminus1_64 - v1_32  == -2_si64 );
static_assert(vminus1_32 - v1_32  == -2_si32 );
static_assert(vminus1_16 - v1_32  == -2_si32 );
static_assert(vminus1_8  - v1_32  == -2_si32 );
static_assert(vminus1_64 - v1_16  == -2_si64 );
static_assert(vminus1_32 - v1_16  == -2_si32 );
static_assert(vminus1_16 - v1_16  == -2_si16 );
static_assert(vminus1_8  - v1_16  == -2_si16 );
static_assert(vminus1_64 - v1_8   == -2_si64 );
static_assert(vminus1_32 - v1_8   == -2_si32 );
static_assert(vminus1_16 - v1_8   == -2_si16 );
static_assert(vminus1_8  - v1_8   == -2_si8 );

static_assert(v1_64 * vminus1_64 == -1_si64 );
static_assert(v1_64 * vminus1_32 == -1_si64 );
static_assert(v1_64 * vminus1_16 == -1_si64 );
static_assert(v1_64 * vminus1_8  == -1_si64 );
static_assert(v1_32 * vminus1_64 == -1_si64 );
static_assert(v1_32 * vminus1_32 == -1_si32 );
static_assert(v1_32 * vminus1_16 == -1_si32 );
static_assert(v1_32 * vminus1_8  == -1_si32 );
static_assert(v1_16 * vminus1_64 == -1_si64 );
static_assert(v1_16 * vminus1_32 == -1_si32 );
static_assert(v1_16 * vminus1_16 == -1_si16 );
static_assert(v1_16 * vminus1_8  == -1_si16 );
static_assert(v1_8  * vminus1_64 == -1_si64 );
static_assert(v1_8  * vminus1_32 == -1_si32 );
static_assert(v1_8  * vminus1_16 == -1_si16 );
static_assert(v1_8  * vminus1_8  == -1_si8 );

static_assert(vminus1_64 *  v1_64== -1_si64 );
static_assert(vminus1_32 *  v1_64== -1_si64 );
static_assert(vminus1_16 *  v1_64== -1_si64 );
static_assert(vminus1_8  *  v1_64== -1_si64 );
static_assert(vminus1_64 *  v1_32== -1_si64 );
static_assert(vminus1_32 *  v1_32== -1_si32 );
static_assert(vminus1_16 *  v1_32== -1_si32 );
static_assert(vminus1_8  *  v1_32== -1_si32 );
static_assert(vminus1_64 *  v1_16== -1_si64 );
static_assert(vminus1_32 *  v1_16== -1_si32 );
static_assert(vminus1_16 *  v1_16== -1_si16 );
static_assert(vminus1_8  *  v1_16== -1_si16 );
static_assert(vminus1_64 *  v1_8 == -1_si64 );
static_assert(vminus1_32 *  v1_8 == -1_si32 );
static_assert(vminus1_16 *  v1_8 == -1_si16 );
static_assert(vminus1_8  *  v1_8 == -1_si8 );

static_assert(vminus1_64 *  v2_64== -2_si64 );
static_assert(vminus1_32 *  v2_64== -2_si64 );
static_assert(vminus1_16 *  v2_64== -2_si64 );
static_assert(vminus1_8  *  v2_64== -2_si64 );
static_assert(vminus1_64 *  v2_32== -2_si64 );
static_assert(vminus1_32 *  v2_32== -2_si32 );
static_assert(vminus1_16 *  v2_32== -2_si32 );
static_assert(vminus1_8  *  v2_32== -2_si32 );
static_assert(vminus1_64 *  v2_16== -2_si64 );
static_assert(vminus1_32 *  v2_16== -2_si32 );
static_assert(vminus1_16 *  v2_16== -2_si16 );
static_assert(vminus1_8  *  v2_16== -2_si16 );
static_assert(vminus1_64 *  v2_8 == -2_si64 );
static_assert(vminus1_32 *  v2_8 == -2_si32 );
static_assert(vminus1_16 *  v2_8 == -2_si16 );
static_assert(vminus1_8  *  v2_8 == -2_si8 );

static_assert(vminus1_64 * -v2_64==  2_si64 );
static_assert(vminus1_32 * -v2_64==  2_si64 );
static_assert(vminus1_16 * -v2_64==  2_si64 );
static_assert(vminus1_8  * -v2_64==  2_si64 );
static_assert(vminus1_64 * -v2_32==  2_si64 );
static_assert(vminus1_32 * -v2_32==  2_si32 );
static_assert(vminus1_16 * -v2_32==  2_si32 );
static_assert(vminus1_8  * -v2_32==  2_si32 );
static_assert(vminus1_64 * -v2_16==  2_si64 );
static_assert(vminus1_32 * -v2_16==  2_si32 );
static_assert(vminus1_16 * -v2_16==  2_si16 );
static_assert(vminus1_8  * -v2_16==  2_si16 );
static_assert(vminus1_64 * -v2_8 ==  2_si64 );
static_assert(vminus1_32 * -v2_8 ==  2_si32 );
static_assert(vminus1_16 * -v2_8 ==  2_si16 );
static_assert(vminus1_8  * -v2_8 ==  2_si8 );

static_assert(v2_64 * -v2_64== -4_si64 );
static_assert(v2_32 * -v2_64== -4_si64 );
static_assert(v2_16 * -v2_64== -4_si64 );
static_assert(v2_8  * -v2_64== -4_si64 );
static_assert(v2_64 * -v2_32== -4_si64 );
static_assert(v2_32 * -v2_32== -4_si32 );
static_assert(v2_16 * -v2_32== -4_si32 );
static_assert(v2_8  * -v2_32== -4_si32 );
static_assert(v2_64 * -v2_16== -4_si64 );
static_assert(v2_32 * -v2_16== -4_si32 );
static_assert(v2_16 * -v2_16== -4_si16 );
static_assert(v2_8  * -v2_16== -4_si16 );
static_assert(v2_64 * -v2_8 == -4_si64 );
static_assert(v2_32 * -v2_8 == -4_si32 );
static_assert(v2_16 * -v2_8 == -4_si16 );
static_assert(v2_8  * -v2_8 == -4_si8 );

static_assert(-v2_64 * -v2_64== 4_si64 );
static_assert(-v2_32 * -v2_64== 4_si64 );
static_assert(-v2_16 * -v2_64== 4_si64 );
static_assert(-v2_8  * -v2_64== 4_si64 );
static_assert(-v2_64 * -v2_32== 4_si64 );
static_assert(-v2_32 * -v2_32== 4_si32 );
static_assert(-v2_16 * -v2_32== 4_si32 );
static_assert(-v2_8  * -v2_32== 4_si32 );
static_assert(-v2_64 * -v2_16== 4_si64 );
static_assert(-v2_32 * -v2_16== 4_si32 );
static_assert(-v2_16 * -v2_16== 4_si16 );
static_assert(-v2_8  * -v2_16== 4_si16 );
static_assert(-v2_64 * -v2_8 == 4_si64 );
static_assert(-v2_32 * -v2_8 == 4_si32 );
static_assert(-v2_16 * -v2_8 == 4_si16 );
static_assert(-v2_8  * -v2_8 == 4_si8 );

// demonstrate wrapping:
static_assert(min_64 * v2_64 == 0_si64 );
static_assert(min_64 * v2_32 == 0_si64  );
static_assert(min_64 * v2_16 == 0_si64  );
static_assert(min_64 * v2_8  == 0_si64 );
static_assert(min_32 * v2_64 == -0x1'0000'0000_si64 );
static_assert(min_32 * v2_32 == 0_si32 );
static_assert(min_32 * v2_16 == 0_si32 );
static_assert(min_32 * v2_8  == 0_si32 );
static_assert(min_16 * v2_64 == -0x1'0000_si64  );
static_assert(min_16 * v2_32 == -0x1'0000_si32 );
static_assert(min_16 * v2_16 == 0_si16 );
static_assert(min_16 * v2_8  == 0_si16 );
static_assert(min_8  * v2_64 == -256_si64 );
static_assert(min_8  * v2_32 == -256_si32 );
static_assert(min_8  * v2_16 == -256_si16 );
static_assert(min_8  * v2_8  == 0_si8 );


static_assert(v1_64 / vminus1_64 == -1_si64 );
static_assert(v1_64 / vminus1_32 == -1_si64 );
static_assert(v1_64 / vminus1_16 == -1_si64 );
static_assert(v1_64 / vminus1_8  == -1_si64 );
static_assert(v1_32 / vminus1_64 == -1_si64 );
static_assert(v1_32 / vminus1_32 == -1_si32 );
static_assert(v1_32 / vminus1_16 == -1_si32 );
static_assert(v1_32 / vminus1_8  == -1_si32 );
static_assert(v1_16 / vminus1_64 == -1_si64 );
static_assert(v1_16 / vminus1_32 == -1_si32 );
static_assert(v1_16 / vminus1_16 == -1_si16 );
static_assert(v1_16 / vminus1_8  == -1_si16 );
static_assert(v1_8  / vminus1_64 == -1_si64 );
static_assert(v1_8  / vminus1_32 == -1_si32 );
static_assert(v1_8  / vminus1_16 == -1_si16 );
static_assert(v1_8  / vminus1_8  == -1_si8 );

static_assert(vminus1_64 /  v1_64== -1_si64 );
static_assert(vminus1_32 /  v1_64== -1_si64 );
static_assert(vminus1_16 /  v1_64== -1_si64 );
static_assert(vminus1_8  /  v1_64== -1_si64 );
static_assert(vminus1_64 /  v1_32== -1_si64 );
static_assert(vminus1_32 /  v1_32== -1_si32 );
static_assert(vminus1_16 /  v1_32== -1_si32 );
static_assert(vminus1_8  /  v1_32== -1_si32 );
static_assert(vminus1_64 /  v1_16== -1_si64 );
static_assert(vminus1_32 /  v1_16== -1_si32 );
static_assert(vminus1_16 /  v1_16== -1_si16 );
static_assert(vminus1_8  /  v1_16== -1_si16 );
static_assert(vminus1_64 /  v1_8 == -1_si64 );
static_assert(vminus1_32 /  v1_8 == -1_si32 );
static_assert(vminus1_16 /  v1_8 == -1_si16 );
static_assert(vminus1_8  /  v1_8 == -1_si8 );


static_assert(v2_64 / vminus1_64 == -2_si64 );
static_assert(v2_64 / vminus1_32 == -2_si64 );
static_assert(v2_64 / vminus1_16 == -2_si64 );
static_assert(v2_64 / vminus1_8  == -2_si64 );
static_assert(v2_32 / vminus1_64 == -2_si64 );
static_assert(v2_32 / vminus1_32 == -2_si32 );
static_assert(v2_32 / vminus1_16 == -2_si32 );
static_assert(v2_32 / vminus1_8  == -2_si32 );
static_assert(v2_16 / vminus1_64 == -2_si64 );
static_assert(v2_16 / vminus1_32 == -2_si32 );
static_assert(v2_16 / vminus1_16 == -2_si16 );
static_assert(v2_16 / vminus1_8  == -2_si16 );
static_assert(v2_8  / vminus1_64 == -2_si64 );
static_assert(v2_8  / vminus1_32 == -2_si32 );
static_assert(v2_8  / vminus1_16 == -2_si16 );
static_assert(v2_8  / vminus1_8  == -2_si8 );

static_assert(vminus1_64 /  v2_64== 0_si64 );
static_assert(vminus1_32 /  v2_64== 0_si64 );
static_assert(vminus1_16 /  v2_64== 0_si64 );
static_assert(vminus1_8  /  v2_64== 0_si64 );
static_assert(vminus1_64 /  v2_32== 0_si64 );
static_assert(vminus1_32 /  v2_32== 0_si32 );
static_assert(vminus1_16 /  v2_32== 0_si32 );
static_assert(vminus1_8  /  v2_32== 0_si32 );
static_assert(vminus1_64 /  v2_16== 0_si64 );
static_assert(vminus1_32 /  v2_16== 0_si32 );
static_assert(vminus1_16 /  v2_16== 0_si16 );
static_assert(vminus1_8  /  v2_16== 0_si16 );
static_assert(vminus1_64 /  v2_8 == 0_si64 );
static_assert(vminus1_32 /  v2_8 == 0_si32 );
static_assert(vminus1_16 /  v2_8 == 0_si16 );
static_assert(vminus1_8  /  v2_8 == 0_si8 );

static_assert(min_64 /  min_64 ==  1_si64 );
static_assert(min_32 /  min_64 ==  0_si64 );
static_assert(min_16 /  min_64 ==  0_si64 );
static_assert(min_8  /  min_64 ==  0_si64 );
static_assert(min_64 /  min_32 ==  0x1'0000'0000_si64 );
static_assert(min_32 /  min_32 ==  1_si32 );
static_assert(min_16 /  min_32 ==  0_si32 );
static_assert(min_8  /  min_32 ==  0_si32 );
static_assert(min_64 /  min_16 ==  0x1'0000'0000'0000_si64 );
static_assert(min_32 /  min_16 ==  0x1'0000_si32 );
static_assert(min_16 /  min_16 ==  1_si16 );
static_assert(min_8  /  min_16 ==  0_si16 );
static_assert(min_64 /  min_8  ==  0x100'0000'0000'0000_si64 );
static_assert(min_32 /  min_8  ==  0x100'0000_si32 );
static_assert(min_16 /  min_8  ==  256_si16 );
static_assert(min_8  /  min_8  ==  1_si8 );

// demonstrate wrapping:
static_assert(min_64 / vminus1_64 == min_64 );
static_assert(min_64 / vminus1_32 == min_64 );
static_assert(min_64 / vminus1_16 == min_64 );
static_assert(min_64 / vminus1_8  == min_64 );
static_assert(min_32 / vminus1_64 == 0x8000'0000_si64 );
static_assert(min_32 / vminus1_32 == min_32 );
static_assert(min_32 / vminus1_16 == min_32 );
static_assert(min_32 / vminus1_8  == min_32 );
static_assert(min_16 / vminus1_64 == -static_cast<si64>(min_16)  );
static_assert(min_16 / vminus1_32 == 0x8000_si32 );
static_assert(min_16 / vminus1_16 == min_16 );
static_assert(min_16 / vminus1_8  == min_16 );
static_assert(min_8  / vminus1_64 == 128_si64 );
static_assert(min_8  / vminus1_32 == 128_si32 );
static_assert(min_8  / vminus1_16 == 128_si16 );
static_assert(min_8  / vminus1_8  == min_8 );

static_assert(min_64 / v1_64 == min_64 );
static_assert(min_64 / v1_32 == min_64 );
static_assert(min_64 / v1_16 == min_64 );
static_assert(min_64 / v1_8  == min_64 );
static_assert(min_32 / v1_64 == -0x8000'0000_si64 );
static_assert(min_32 / v1_32 == min_32 );
static_assert(min_32 / v1_16 == min_32 );
static_assert(min_32 / v1_8  == min_32 );
static_assert(min_16 / v1_64 == -0x8000_si64  );
static_assert(min_16 / v1_32 == -0x8000_si32 );
static_assert(min_16 / v1_16 == min_16 );
static_assert(min_16 / v1_8  == min_16 );
static_assert(min_8  / v1_64 == -128_si64 );
static_assert(min_8  / v1_32 == -128_si32 );
static_assert(min_8  / v1_16 == -128_si16 );
static_assert(min_8  / v1_8  == min_8 );

static_assert(min_64 / v2_64 == -0x4000'0000'0000'0000_si64 );
static_assert(min_64 / v2_32 == -0x4000'0000'0000'0000_si64  );
static_assert(min_64 / v2_16 == -0x4000'0000'0000'0000_si64  );
static_assert(min_64 / v2_8  == -0x4000'0000'0000'0000_si64 );
static_assert(min_32 / v2_64 == -0x4000'0000_si64 );
static_assert(min_32 / v2_32 == -0x4000'0000_si32 );
static_assert(min_32 / v2_16 == -0x4000'0000_si32 );
static_assert(min_32 / v2_8  == -0x4000'0000_si32 );
static_assert(min_16 / v2_64 == -0x4000_si64  );
static_assert(min_16 / v2_32 == -0x4000_si32 );
static_assert(min_16 / v2_16 == -0x4000_si16 );
static_assert(min_16 / v2_8  == -0x4000_si16 );
static_assert(min_8  / v2_64 == -64_si64 );
static_assert(min_8  / v2_32 == -64_si32 );
static_assert(min_8  / v2_16 == -64_si16 );
static_assert(min_8  / v2_8  == -64_si8 );


static_assert(-100_si32 / -9_si64 == 11_si64);
static_assert(100_si32 / 9_si64 == 11_si64);
static_assert(-100_si32 / 9_si64 == -11_si64);
static_assert(100_si32 / -9_si64 == -11_si64);

static_assert(std::numeric_limits<si32>::min() / 1_si32 == std::numeric_limits<si32>::min()); // wraps
static_assert(std::numeric_limits<si32>::min() / -1_si32 == std::numeric_limits<si32>::min()); // wraps

template<typename T, typename WHAT>
constexpr bool
isa = std::is_same_v<psssint::plain<T>,WHAT>;


template<typename T>
constexpr bool
is_unsigned = isa<T, unsigned char>
|| isa<T, unsigned short>
|| isa<T, unsigned >
|| isa<T, unsigned long>
|| isa<T, unsigned long long>;

template<typename T>
constexpr bool
is_signed = isa<T, signed char>
|| isa<T, short>
|| isa<T, int >
|| isa<T, long>
|| isa<T, long long>;


template<typename T>
constexpr bool
is_integer = is_unsigned<T>||is_signed<T>;

static_assert(is_integer<std::underlying_type_t<ui16>>);
static_assert(!is_integer<ui16>);
static_assert(is_integer<std::underlying_type_t<si16>>);
static_assert(!is_integer<si16>);


void signedIntegerBoundaryTestResultRecovery(){
    // temporary testcase for getting static_asserts above right
    ASSERT_EQUAL(0x8000'0000_si64, max_32 + v1_64  );
}


}

void ui16intExists() {
    using psssint::ui16;
    auto large=0xff00_ui16;
    //0x10000_ui16; // compile error
    //ui16{0xfffff}; // narrowing detection
    ASSERT_EQUAL(ui16{0xff00u},large);
}

void ui16NotEqualAutomaticInCpp20(){
    ASSERT(0xf_ui16 != 0_ui16);
}

void ui16canbeadded(){
    ASSERT_EQUAL(100_ui16,75_ui16+25_ui16);
}

void ui16canbeaddedto(){
    auto l = 42_ui16;
    l += 8_ui8;
    //l += 1_ui32; // compile error
    ASSERT_EQUAL(50_ui16,l);
}

void ui16canbesubtracted(){
    ASSERT_EQUAL(50_ui16,75_ui16-25_ui16);
}

void ui16canbesubtractedfrom(){
    auto l = 42_ui16;
    l -= 8_ui8;
    //l -= 1_ui32; // compile error
    ASSERT_EQUAL(34_ui16,l);
}

void ui16canbemultiplied(){
    ASSERT_EQUAL(1875_ui16,75_ui16*25_ui16);
}

void ui16canbemultipliedwith(){
    auto l = 42_ui16;
    l *= 8_ui8;
    //l -= 1_ui32; // compile error
    ASSERT_EQUAL(336_ui16,l);
}


void ui16canbedivided(){
    ASSERT_EQUAL(3_ui16,75_ui16/25_ui16);
}

void ui16canbedividedby(){
    auto l = 42_ui16;
    l /= 7_ui8;
    //l /= 1_ui32; // compile error
    ASSERT_EQUAL(6_ui16,l);
}

void ui16canbemoduloed(){
    ASSERT_EQUAL(10_ui16,75_ui16%13_ui16);
}

void ui16canbemoduloedby(){
    auto l = 42_ui16;
    l %= 13_ui8;
    //l %= 1_ui32; // compile error
    ASSERT_EQUAL(3_ui16,l);
}


void ui16canbeanded(){
    ASSERT_EQUAL(0X0AA0_ui16,0x0ff0_ui16 & 0xAAAA_ui16);
}

void ui16canbeandedwith(){
    auto l = 0xff00_ui16;
    l &= 0xABCD_ui16;
    //l &= 1_ui8; // compile error
    ASSERT_EQUAL(0xAB00_ui16,l);
}

void ui16canbeored(){
    ASSERT_EQUAL(0XAFFA_ui16,0x0ff0_ui16 | 0xAAAA_ui16);
}

void ui16canbeoredwith(){
    auto l = 0xff00_ui16;
    l |= 0xABCD_ui16;
    //l |= 1_ui8; // compile error
    ASSERT_EQUAL(0xFFCD_ui16,l);
}

void ui16canbexored(){
    ASSERT_EQUAL(0XA55A_ui16,0x0ff0_ui16 ^ 0xAAAA_ui16);
}

void ui16canbexoredwith(){
    auto l = 0xff00_ui16;
    l ^= 0xABCD_ui16;
    //l ^= 1_ui8; // compile error
    ASSERT_EQUAL(0x54CD_ui16,l);
}

void ui16canbenegated(){
    ASSERT_EQUAL(0XA55A_ui16, ~0x5AA5_ui16 );
}

void ui16canbeleftshifted(){
    //constexpr auto l = 0x1_ui16 << 16_ui8; // compile error
    ASSERT_EQUAL(0XFF00_ui16,0x0ff0_ui16 << 0x4_ui8);
}

void ui16canbeleftshiftedby(){
    auto l = 0x00ff_ui16;
    l <<= 4_ui16;
    ASSERT_EQUAL(0x0FF0_ui16,l);
}
void ui16canberightshifted(){
    //constexpr auto l = 0x1_ui16 << 16_ui8; // compile error
    ASSERT_EQUAL(0X00FF_ui16,0x0ff0_ui16 >> 0x4_ui8);
}

void ui16canberightshiftedby(){
    auto l = 0x00ff_ui16;
    l >>= 4_ui16;
    ASSERT_EQUAL(0x0F_ui16,l);
}
void ui16canbepreincremented(){
    auto l = 0x00ff_ui16;
    ASSERT_EQUAL(0x100_ui16,++l);
    ASSERT_EQUAL(0x100_ui16,l);
}
void ui16canbepostincremented(){
    auto l = 0x00ff_ui16;
    ASSERT_EQUAL(0x00ff_ui16,l++);
    ASSERT_EQUAL(0x100_ui16,l);
}
void ui16canbepredecremented(){
    auto l = 0x00ff_ui16;
    ASSERT_EQUAL(0x100_ui16,++l);
    ASSERT_EQUAL(0x100_ui16,l);
}
void ui16canbepostdecremented(){
    auto l = 0x00ff_ui16;
    ASSERT_EQUAL(0x00ff_ui16,l++);
    ASSERT_EQUAL(0x100_ui16,l);
}

void ui16canbecompared(){
    auto l = 0x00ff_ui16;
    auto s = 0x000f_ui16;

	ASSERTM("check comparison", l != s && s < l && l >= s && !(l < s) && ! (l <= s));
}

void ui16canNotbecomparedwithui8() {
    auto l = 0x00ff_ui16;
    auto s = 0x000f_ui8;


//    ASSERTM("check comparison", l != s && s < l && l >= s && !(l < s) && ! (l <= s));

    auto ss = s + 0_ui16;
    ASSERTM("check comparison", l != ss && ss < l && l >= ss && !(l < ss) && ! (l <= ss));
}

void ui32CanNotbeComparedwithlong(){
    auto l = 0x00ff_ui32;
    auto s = std::uint32_t{0x000fU};


//    ASSERTM("check comparison", l != s && s < l && l >= s && !(l < s) && ! (l <= s));

    auto ss = psssint::from_int(s);
    ASSERTM("check comparison", l != ss && ss < l && l >= ss && !(l < ss) && ! (l <= ss));

}


// signed test to check if result is correct (overflow wraps)

void si8canbeaddednormal(){
    ASSERT_EQUAL(42_si8, 21_si8 + 21_si8);
}

void si8Negation(){
    ASSERT_EQUAL(-1,promote_keep_signedness(-1_si8));
}

void si8negationminintidempotent(){
    auto x = promote_keep_signedness(-(1_si8+127_si8));
    static_assert(std::is_integral_v<decltype(x)>);
    ASSERT_EQUAL(-128,+x);
}

void si8overflowmakesitNegative(){
    ASSERT_EQUAL(-2_si8,127_si8+127_si8);
}

void si8subtraction(){
    ASSERT_EQUAL(-1_si8,2_si8-3_si8);
}

void si8subtractionwraps(){
    ASSERT_EQUAL(127_si8,-2_si8-127_si8);
}
void si8multiplication(){
    ASSERT_EQUAL(120_si8 , 3_si8 * 40_si8);
}
void si8division(){
    ASSERT_EQUAL(3_si8 , 120_si8 / 40_si8);
}

void si8OutputAsInteger(){
    std::ostringstream out{};
    out << 42_si8;
    ASSERT_EQUAL("42",out.str());
}

void ui8OutputAsInteger(){
    std::ostringstream out{};
    out << 42_ui8;
    ASSERT_EQUAL("42",out.str());
}

void checkedFromInt(){
    using namespace psssint;
#ifdef NDEBUG
    ASSERT_EQUAL(0_ui8,from_int_to<ui8>(2400u));
#else
  #ifdef PS_ASSERT_THROWS
    ASSERT_THROWS(from_int_to<ui8>(2400u), char const *);
  #else
    #ifdef PS_TEST_TRAP
    ASSERTM("cannot test trapping without NDEBUG set, change this to true to check for assert() behavior ",false);
    ASSERT_EQUAL(0,from_int_to<ui8>(2400u)); // assert()
    #endif
  #endif
#endif

}

namespace cppnowtalk{

void testUBforint() {
    std::ostringstream out{};
    out << 65535 * 32768 << '\n';
    // prints: 2147450880
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Woverflow"
    out << 65536 * 32768 << '\n';
    //../src/Test.cpp:421:18: error: integer overflow in expression of type 'int' results in '-2147483648' [-Werror=overflow]
#pragma GCC diagnostic pop
    // prints: ?
    out << std::boolalpha << std::numeric_limits<int>::is_modulo << '\n';
    ASSERT_EQUAL("2147450880\n-2147483648\nfalse\n",out.str());
}
void testNoUBforunsigned() {
    std::ostringstream out{};
    out << 65535u * 32768u << '\n';
    // prints: 2147450880
    out << 65536u * 32768u << '\n';
    // prints: 2147483648

    out << 65536u * 32768u * 2u << '\n';
    // prints: ?
    out << std::boolalpha << std::numeric_limits<unsigned>::is_modulo << '\n';
    ASSERT_EQUAL("2147450880\n2147483648\n0\ntrue\n",out.str());
}
}

bool runAllTests(int argc, char const *argv[]) {
    cute::suite TestForZeroReturnAssertWithNDEBUG = make_suite_TestForZeroReturnAssertWithNDEBUG();
    TestForZeroReturnAssertWithNDEBUG.push_back(CUTE(cppnowtalk::testUBforint));
    TestForZeroReturnAssertWithNDEBUG.push_back(CUTE(cppnowtalk::testNoUBforunsigned));

    cute::suite s { };

    s.push_back(CUTE(ui16intExists));
    s.push_back(CUTE(ui16NotEqualAutomaticInCpp20));
    s.push_back(CUTE(ui16canbeadded));
    s.push_back(CUTE(ui16canbeaddedto));
    s.push_back(CUTE(ui16canbesubtracted));
    s.push_back(CUTE(ui16canbesubtractedfrom));
    s.push_back(CUTE(ui16canbemultiplied));
    s.push_back(CUTE(ui16canbemultipliedwith));
    s.push_back(CUTE(ui16canbedivided));
    s.push_back(CUTE(ui16canbedividedby));
    s.push_back(CUTE(ui16canbemoduloed));
    s.push_back(CUTE(ui16canbemoduloedby));
    s.push_back(CUTE(ui16canbeandedwith));
    s.push_back(CUTE(ui16canbeanded));
    s.push_back(CUTE(ui16canbeored));
    s.push_back(CUTE(ui16canbeoredwith));
    s.push_back(CUTE(ui16canbexoredwith));
    s.push_back(CUTE(ui16canbexored));
    s.push_back(CUTE(ui16canbenegated));
    s.push_back(CUTE(ui16canbeleftshifted));
    s.push_back(CUTE(ui16canbeleftshiftedby));
    s.push_back(CUTE(ui16canberightshifted));
    s.push_back(CUTE(ui16canberightshiftedby));
    s.push_back(CUTE(si8canbeaddednormal));
    s.push_back(CUTE(si8Negation));
    s.push_back(CUTE(si8negationminintidempotent));
    s.push_back(CUTE(si8overflowmakesitNegative));
    s.push_back(CUTE(si8subtraction));
    s.push_back(CUTE(si8subtractionwraps));
    s.push_back(CUTE(si8multiplication));
    s.push_back(CUTE(si8division));
    s.push_back(CUTE(ui16canbepreincremented));
    s.push_back(CUTE(ui16canbepostincremented));
    s.push_back(CUTE(ui16canbepredecremented));
    s.push_back(CUTE(ui16canbepostdecremented));
	s.push_back(CUTE(checkedFromInt));
	s.push_back(CUTE(si8OutputAsInteger));
	s.push_back(CUTE(ui8OutputAsInteger));
	s.push_back(CUTE(ui16canbecompared));
	s.push_back(CUTE(ui16canNotbecomparedwithui8));
	s.push_back(CUTE(ui32CanNotbeComparedwithlong));
	s.push_back(CUTE(_testing::signedIntegerBoundaryTestResultRecovery));
	cute::xml_file_opener xmlfile(argc, argv);
    cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
    auto runner = cute::makeRunner(lis, argc, argv);
    bool success = runner(s, "AllTests");
    success = runner(make_suite_CodeGenBenchmark(),"CodeGenBenchmark") && success;
    success &= runner(TestForZeroReturnAssertWithNDEBUG, "TestForZeroReturnAssertWithNDEBUG");
    return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
