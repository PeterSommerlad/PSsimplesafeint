#include "psssafeint.h"
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include <type_traits>
#include <cstddef>



using namespace psssint::literals;

namespace _testing {
using namespace psssint;
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
static_assert(std::is_same_v<unsigned,decltype(to_int(1_ui8)+1)>);
static_assert(std::is_same_v<unsigned,decltype(to_int(2_ui16)+1)>);
static_assert(std::is_same_v<int,decltype(to_int(1_si8))>);
static_assert(std::is_same_v<int,decltype(to_int(2_si16))>);
static_assert(std::is_same_v<uint8_t,std::underlying_type_t<ui8>>);
static_assert(std::is_same_v<uint16_t,std::underlying_type_t<ui16>>);


static_assert(to_int(0xffff_ui16 * 0xffff_ui16) == 0x1u); // wraps
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
//static_assert(1_ui8 == from_int_to<ui8>(true)); // does not compile

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
    ASSERT_EQUAL(-1,to_int(-1_si8));
}

void si8negationminintidempotent(){
    auto x = to_int(-(1_si8+127_si8));
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
    ASSERT_THROWS(from_int_to<ui8>(2400u), char const *);
}




bool runAllTests(int argc, char const *argv[]) {
    cute::suite s { };
    //TODO add your test here
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
	cute::xml_file_opener xmlfile(argc, argv);
    cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
    auto runner = cute::makeRunner(lis, argc, argv);
    bool success = runner(s, "AllTests");
    return success;
}

int main(int argc, char const *argv[]) {
    return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
