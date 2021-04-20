#include "CodeGenBenchmark.h"
#include "cute.h"
#include "psssafeint.h"

#include <initializer_list>

#include <vector>
#include <numeric>

using namespace psssint;

template<typename INT>
struct operations {
    operations(std::initializer_list<INT> seedvalues):values{seedvalues}{};
    std::vector<INT> values;

    auto sum() const {
        auto const initialvalue = INT{0}; // +INT{}; // triggers promotion
        return std::accumulate(begin(values),end(values),initialvalue);
    }
    auto product() const {
        auto const initialvalue = INT{1}; // +INT{}; // triggers promotion
        return std::accumulate(begin(values),end(values),initialvalue,[](auto l, auto r){return l*r;});
    }
    auto sumthirds() const {
        auto const initialvalue = INT{0}; // +INT{}; // triggers promotion
        return std::accumulate(begin(values),end(values),initialvalue,[](auto l, auto r){return l+(r/INT{3});});
    }
    auto sumnegative() const {
        auto const initialvalue = INT{}; // +INT{}; // triggers promotion
        return std::accumulate(begin(values),end(values),initialvalue,[](auto l, auto r){return l-r;});
    }
};

std::initializer_list<int8_t> i8_seed{1,1,2,3,5,8/*,13,21,34,55,89*/};
std::initializer_list<psssint::si8> si8_seed{1_si8,1_si8,2_si8,3_si8,5_si8,8_si8/*,13_si8,21_si8,34_si8,55_si8,89_si8*/};

auto sum(operations<int8_t> const &ops){
    return ops.sum();
}
auto product(operations<int8_t> const &ops){
    return ops.product();
}
auto sumthirds(operations<int8_t> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<int8_t> const &ops){
    return ops.sumnegative();
}

auto sum(operations<si8> const &ops){
    return ops.sum();
}
auto product(operations<si8> const &ops){
    return ops.product();
}
auto sumthirds(operations<si8> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<si8> const &ops){
    return ops.sumnegative();
}




void codegenAdditionTest() {
    auto resi8 = sum(operations<int8_t>{i8_seed});
    auto ressi8 =sum( operations<si8>{si8_seed});
    ASSERT_EQUAL(resi8,to_int(ressi8));
}

void codegenMultiplicationTest(){
    auto resi8 = product(operations<int8_t>{i8_seed});
    auto ressi8 = product( operations<si8>{si8_seed});
    ASSERT_EQUAL(resi8,to_int(ressi8));
    ASSERT_EQUAL(from_int(resi8),ressi8);
    ASSERTM("expect signed integer overflow not detected by ubsan",resi8 < 0);
    ASSERTM("expect signed integer overflow not detected by ubsan",ressi8 < 0_si8);
}
void codegenSumThirdsTest(){
    auto resi8 = sumthirds(operations<int8_t>{i8_seed});
    auto ressi8 = sumthirds( operations<si8>{si8_seed});
    ASSERT_EQUAL(resi8,to_int(ressi8));
}
void codegenSubtractionTest(){
    auto resi8 = sumnegative(operations<int8_t>{i8_seed});
    auto ressi8 = sumnegative( operations<si8>{si8_seed});
    ASSERT_EQUAL(resi8,to_int(ressi8));
}

namespace int16 {
std::initializer_list<int16_t> i16_seed{1,1,2,3,5,8,13,21,34,55};
std::initializer_list<psssint::si16> si16_seed{1_si16,1_si16,2_si16,3_si16,5_si16,8_si16,13_si16,21_si16,34_si16,55_si16};

auto sum(operations<int16_t> const &ops){
    return ops.sum();
}
auto product(operations<int16_t> const &ops){
    return ops.product();
}
auto sumthirds(operations<int16_t> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<int16_t> const &ops){
    return ops.sumnegative();
}

auto sum(operations<si16> const &ops){
    return ops.sum();
}
auto product(operations<si16> const &ops){
    return ops.product();
}
auto sumthirds(operations<si16> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<si16> const &ops){
    return ops.sumnegative();
}
void codegenAdditionTest() {
    auto resi16 = sum(operations<int16_t>{i16_seed});
    auto ressi16 =sum( operations<si16>{si16_seed});
    ASSERT_EQUAL(resi16,to_int(ressi16));
}

void codegenMultiplicationTest(){
    auto resi16 = product(operations<int16_t>{i16_seed});
    auto ressi16 = product( operations<si16>{si16_seed});
    ASSERT_EQUAL(resi16,to_int(ressi16));
    ASSERT_EQUAL(from_int(resi16),ressi16);
    ASSERTM("expect signed integer overflow not detected by ubsan",resi16 < 0);
    ASSERTM("expect signed integer overflow not detected by ubsan",ressi16 < 0_si16);
    // no detection of overflow by UBSAN

}
void codegenSumThirdsTest(){
    auto resi16 = sumthirds(operations<int16_t>{i16_seed});
    auto ressi16 = sumthirds( operations<si16>{si16_seed});
    ASSERT_EQUAL(resi16,to_int(ressi16));
}
void codegenSubtractionTest(){
    auto resi16 = sumnegative(operations<int16_t>{i16_seed});
    auto ressi16 = sumnegative( operations<si16>{si16_seed});
    ASSERT_EQUAL(resi16,to_int(ressi16));
}

}
namespace int32 {
std::initializer_list<int32_t> i32_seed{1,1,2,3,5,8,13,21,34,55,89};
std::initializer_list<psssint::si32> si32_seed{1_si32,1_si32,2_si32,3_si32,5_si32,8_si32,13_si32,21_si32,34_si32,55_si32,89_si32};

auto sum(operations<int32_t> const &ops){
    return ops.sum();
}
auto product(operations<int32_t> const &ops){
    return ops.product();
}
auto sumthirds(operations<int32_t> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<int32_t> const &ops){
    return ops.sumnegative();
}

auto sum(operations<si32> const &ops){
    return ops.sum();
}
auto product(operations<si32> const &ops){
    return ops.product();
}
auto sumthirds(operations<si32> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<si32> const &ops){
    return ops.sumnegative();
}
void codegenAdditionTest() {
    auto resi32 = sum(operations<int32_t>{i32_seed});
    auto ressi32 =sum( operations<si32>{si32_seed});
    ASSERT_EQUAL(resi32,to_int(ressi32));
}

void codegenMultiplicationTest(){
    auto resi32 = product(operations<int32_t>{i32_seed});
    auto ressi32 = product( operations<si32>{si32_seed});
    ASSERT_EQUAL(resi32,to_int(ressi32));
    ASSERT_EQUAL(from_int(resi32),ressi32);
    ASSERTM("expect signed integer overflow detected by ubsan",resi32 < 0);
    ASSERTM("expect signed integer overflow not detected by ubsan",ressi32 < 0_si32);
    // ../src/CodeGenBenchmark.cpp:23:99: runtime error: signed integer overflow: 122522400 * 89 cannot be represented in type 'int'

}
void codegenSumThirdsTest(){
    auto resi32 = sumthirds(operations<int32_t>{i32_seed});
    auto ressi32 = sumthirds( operations<si32>{si32_seed});
    ASSERT_EQUAL(resi32,to_int(ressi32));
}
void codegenSubtractionTest(){
    auto resi32 = sumnegative(operations<int32_t>{i32_seed});
    auto ressi32 = sumnegative( operations<si32>{si32_seed});
    ASSERT_EQUAL(resi32,to_int(ressi32));
}

}
namespace int64 {
constexpr std::initializer_list<int64_t> i64_seed{1,1,2,3,5,8,13,21,34,55,89,
                                        144,233,377,610};
constexpr std::initializer_list<psssint::si64> si64_seed{1_si64,1_si64,2_si64,3_si64,5_si64,8_si64,13_si64,21_si64,34_si64,55_si64,89_si64,
    144_si64,233_si64,377_si64,610_si64};

auto sum(operations<int64_t> const &ops){
    return ops.sum();
}
auto product(operations<int64_t> const &ops){
    return ops.product();
}
auto sumthirds(operations<int64_t> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<int64_t> const &ops){
    return ops.sumnegative();
}

auto sum(operations<si64> const &ops){
    return ops.sum();
}
auto product(operations<si64> const &ops){
    return ops.product();
}
auto sumthirds(operations<si64> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<si64> const &ops){
    return ops.sumnegative();
}
void codegenAdditionTest() {
    auto resi64 = sum(operations<int64_t>{i64_seed});
    auto ressi64 =sum( operations<si64>{si64_seed});
    ASSERT_EQUAL(resi64,to_int(ressi64));
}

void codegenMultiplicationTest(){
    auto resi64 = product(operations<int64_t>{i64_seed});
    auto ressi64 = product( operations<si64>{si64_seed});
    ASSERT_EQUAL(resi64,to_int(ressi64));
    ASSERT_EQUAL(from_int(resi64),ressi64);
    ASSERTM("expect signed integer overflow detected by ubsan",resi64 < 0);
    ASSERTM("expect signed integer overflow not detected by ubsan",ressi64 < 0_si64);
    // ../src/CodeGenBenchmark.cpp:23:99: runtime error: signed integer overflow: 137932073613734400 * 610 cannot be represented in type 'long long int'

}
void codegenSumThirdsTest(){
    auto resi64 = sumthirds(operations<int64_t>{i64_seed});
    auto ressi64 = sumthirds( operations<si64>{si64_seed});
    ASSERT_EQUAL(resi64,to_int(ressi64));
}
void codegenSubtractionTest(){
    auto resi64 = sumnegative(operations<int64_t>{i64_seed});
    auto ressi64 = sumnegative( operations<si64>{si64_seed});
    ASSERT_EQUAL(resi64,to_int(ressi64));
}

}
namespace uint32 {
std::initializer_list<uint32_t> ui32_seed{1,1,2,3,5,8,13,21,34,55,89};
std::initializer_list<psssint::ui32> uui32_seed{1_ui32,1_ui32,2_ui32,3_ui32,5_ui32,8_ui32,13_ui32,21_ui32,34_ui32,55_ui32,89_ui32};

auto sum(operations<uint32_t> const &ops){
    return ops.sum();
}
auto product(operations<uint32_t> const &ops){
    return ops.product();
}
auto sumthirds(operations<uint32_t> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<uint32_t> const &ops){
    return ops.sumnegative();
}

auto sum(operations<ui32> const &ops){
    return ops.sum();
}
auto product(operations<ui32> const &ops){
    return ops.product();
}
auto sumthirds(operations<ui32> const &&ops){
    return ops.sumthirds();
}
auto sumnegative(operations<ui32> const &ops){
    return ops.sumnegative();
}
void codegenAdditionTest() {
    auto reui32 = sum(operations<uint32_t>{ui32_seed});
    auto resui32 =sum( operations<ui32>{uui32_seed});
    ASSERT_EQUAL(reui32,to_int(resui32));
}

void codegenMultiplicationTest(){
    auto reui32 = product(operations<uint32_t>{ui32_seed});
    auto resui32 = product( operations<ui32>{uui32_seed});
    ASSERT_EQUAL(reui32,to_int(resui32));
}
void codegenSumThirdsTest(){
    auto reui32 = sumthirds(operations<uint32_t>{ui32_seed});
    auto resui32 = sumthirds( operations<ui32>{uui32_seed});
    ASSERT_EQUAL(reui32,to_int(resui32));
}
void codegenSubtractionTest(){
    auto reui32 = sumnegative(operations<uint32_t>{ui32_seed});
    auto resui32 = sumnegative( operations<ui32>{uui32_seed});
    ASSERT_EQUAL(reui32,to_int(resui32));
}

}


void testUBSanWithSignedOverflow(){
	unsigned short x=0xffffu;

	auto y = x * x; // UBSAN: ../src/CodeGenBenchmark.cpp:46:13: runtime error: signed integer overflow: 65535 * 65535 cannot be represented in type 'int'

	ASSERT_EQUAL(0xffffu*0xffffu,y);
}


void testNoSignedOverflow(){
    auto x=0xffff_ui16;

    auto y = x * x; // no UBSAN overflow message

    ASSERT_EQUAL(0xffff_ui16*0xffff_ui16,y);
}


cute::suite make_suite_CodeGenBenchmark() {
	cute::suite s { };
	s.push_back(CUTE(codegenAdditionTest));
	s.push_back(CUTE(testUBSanWithSignedOverflow));
	s.push_back(CUTE(testNoSignedOverflow));
	s.push_back(CUTE(codegenMultiplicationTest));
	s.push_back(CUTE(codegenSumThirdsTest));
	s.push_back(CUTE(codegenSubtractionTest));
	s.push_back(CUTE(int32::codegenAdditionTest));
	s.push_back(CUTE(int32::codegenMultiplicationTest));
	s.push_back(CUTE(int32::codegenSumThirdsTest));
	s.push_back(CUTE(int32::codegenSubtractionTest));
	s.push_back(CUTE(uint32::codegenAdditionTest));
	s.push_back(CUTE(uint32::codegenMultiplicationTest));
	s.push_back(CUTE(uint32::codegenSumThirdsTest));
	s.push_back(CUTE(uint32::codegenSubtractionTest));
	s.push_back(CUTE(int16::codegenAdditionTest));
	s.push_back(CUTE(int16::codegenMultiplicationTest));
	s.push_back(CUTE(int16::codegenSumThirdsTest));
	s.push_back(CUTE(int16::codegenSubtractionTest));
	s.push_back(CUTE(int64::codegenAdditionTest));
	s.push_back(CUTE(int64::codegenMultiplicationTest));
	s.push_back(CUTE(int64::codegenSumThirdsTest));
	s.push_back(CUTE(int64::codegenSubtractionTest));
	return s;
}
