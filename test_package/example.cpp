#include "psssafeint.h"
#include <type_traits>
#include <cstddef>


using namespace psssint;

static_assert(std::numeric_limits<si8>::min() == from_int(std::numeric_limits<std::underlying_type_t<si8>>::min()) );
static_assert(std::numeric_limits<si8>::max() == from_int(std::numeric_limits<std::underlying_type_t<si8>>::max()) );
static_assert(std::numeric_limits<si8>::lowest() == from_int(std::numeric_limits<std::underlying_type_t<si8>>::lowest()) );
static_assert(std::numeric_limits<si8>::epsilon() == from_int(std::numeric_limits<std::underlying_type_t<si8>>::epsilon()) );
static_assert(std::numeric_limits<si8>::round_error() == from_int(std::numeric_limits<std::underlying_type_t<si8>>::round_error()) );
static_assert(std::numeric_limits<si8>::infinity() == from_int(std::numeric_limits<std::underlying_type_t<si8>>::infinity()) );
static_assert(std::numeric_limits<si8>::quiet_NaN() == from_int(std::numeric_limits<std::underlying_type_t<si8>>::quiet_NaN()) );
static_assert(std::numeric_limits<si8>::signaling_NaN() == from_int(std::numeric_limits<std::underlying_type_t<si8>>::signaling_NaN()) );
static_assert(std::numeric_limits<si8>::denorm_min() == from_int(std::numeric_limits<std::underlying_type_t<si8>>::denorm_min()) );
static_assert(std::numeric_limits<si8>::is_specialized == std::numeric_limits<std::underlying_type_t<si8>>::is_specialized);
static_assert(std::numeric_limits<si8>::digits == std::numeric_limits<std::underlying_type_t<si8>>::digits);
static_assert(std::numeric_limits<si8>::digits10 == std::numeric_limits<std::underlying_type_t<si8>>::digits10);
static_assert(std::numeric_limits<si8>::max_digits10 == std::numeric_limits<std::underlying_type_t<si8>>::max_digits10);
static_assert(std::numeric_limits<si8>::is_signed == std::numeric_limits<std::underlying_type_t<si8>>::is_signed);
static_assert(std::numeric_limits<si8>::is_integer == std::numeric_limits<std::underlying_type_t<si8>>::is_integer);
static_assert(std::numeric_limits<si8>::is_exact == std::numeric_limits<std::underlying_type_t<si8>>::is_exact);
static_assert(std::numeric_limits<si8>::radix == std::numeric_limits<std::underlying_type_t<si8>>::radix);
static_assert(std::numeric_limits<si8>::min_exponent == std::numeric_limits<std::underlying_type_t<si8>>::min_exponent);
static_assert(std::numeric_limits<si8>::min_exponent10 == std::numeric_limits<std::underlying_type_t<si8>>::min_exponent10);
static_assert(std::numeric_limits<si8>::max_exponent == std::numeric_limits<std::underlying_type_t<si8>>::max_exponent);
static_assert(std::numeric_limits<si8>::max_exponent10 == std::numeric_limits<std::underlying_type_t<si8>>::max_exponent10);
static_assert(std::numeric_limits<si8>::has_infinity == std::numeric_limits<std::underlying_type_t<si8>>::has_infinity);
static_assert(std::numeric_limits<si8>::has_quiet_NaN == std::numeric_limits<std::underlying_type_t<si8>>::has_quiet_NaN);
static_assert(std::numeric_limits<si8>::has_signaling_NaN == std::numeric_limits<std::underlying_type_t<si8>>::has_signaling_NaN);
static_assert(std::numeric_limits<si8>::has_denorm == std::numeric_limits<std::underlying_type_t<si8>>::has_denorm);
static_assert(std::numeric_limits<si8>::has_denorm_loss == std::numeric_limits<std::underlying_type_t<si8>>::has_denorm_loss);
static_assert(std::numeric_limits<si8>::is_iec559 == std::numeric_limits<std::underlying_type_t<si8>>::is_iec559);
static_assert(std::numeric_limits<si8>::is_bounded == std::numeric_limits<std::underlying_type_t<si8>>::is_bounded);
static_assert(std::numeric_limits<si8>::tinyness_before == std::numeric_limits<std::underlying_type_t<si8>>::tinyness_before);
static_assert(std::numeric_limits<si8>::round_style == std::numeric_limits<std::underlying_type_t<si8>>::round_style);
static_assert(not std::numeric_limits<si8>::traps);
static_assert(std::numeric_limits<si8>::is_modulo);
static_assert(std::numeric_limits<si16>::min() == from_int(std::numeric_limits<std::underlying_type_t<si16>>::min()) );
static_assert(std::numeric_limits<si16>::max() == from_int(std::numeric_limits<std::underlying_type_t<si16>>::max()) );
static_assert(std::numeric_limits<si16>::lowest() == from_int(std::numeric_limits<std::underlying_type_t<si16>>::lowest()) );
static_assert(std::numeric_limits<si16>::epsilon() == from_int(std::numeric_limits<std::underlying_type_t<si16>>::epsilon()) );
static_assert(std::numeric_limits<si16>::round_error() == from_int(std::numeric_limits<std::underlying_type_t<si16>>::round_error()) );
static_assert(std::numeric_limits<si16>::infinity() == from_int(std::numeric_limits<std::underlying_type_t<si16>>::infinity()) );
static_assert(std::numeric_limits<si16>::quiet_NaN() == from_int(std::numeric_limits<std::underlying_type_t<si16>>::quiet_NaN()) );
static_assert(std::numeric_limits<si16>::signaling_NaN() == from_int(std::numeric_limits<std::underlying_type_t<si16>>::signaling_NaN()) );
static_assert(std::numeric_limits<si16>::denorm_min() == from_int(std::numeric_limits<std::underlying_type_t<si16>>::denorm_min()) );
static_assert(std::numeric_limits<si16>::is_specialized == std::numeric_limits<std::underlying_type_t<si16>>::is_specialized);
static_assert(std::numeric_limits<si16>::digits == std::numeric_limits<std::underlying_type_t<si16>>::digits);
static_assert(std::numeric_limits<si16>::digits10 == std::numeric_limits<std::underlying_type_t<si16>>::digits10);
static_assert(std::numeric_limits<si16>::max_digits10 == std::numeric_limits<std::underlying_type_t<si16>>::max_digits10);
static_assert(std::numeric_limits<si16>::is_signed == std::numeric_limits<std::underlying_type_t<si16>>::is_signed);
static_assert(std::numeric_limits<si16>::is_integer == std::numeric_limits<std::underlying_type_t<si16>>::is_integer);
static_assert(std::numeric_limits<si16>::is_exact == std::numeric_limits<std::underlying_type_t<si16>>::is_exact);
static_assert(std::numeric_limits<si16>::radix == std::numeric_limits<std::underlying_type_t<si16>>::radix);
static_assert(std::numeric_limits<si16>::min_exponent == std::numeric_limits<std::underlying_type_t<si16>>::min_exponent);
static_assert(std::numeric_limits<si16>::min_exponent10 == std::numeric_limits<std::underlying_type_t<si16>>::min_exponent10);
static_assert(std::numeric_limits<si16>::max_exponent == std::numeric_limits<std::underlying_type_t<si16>>::max_exponent);
static_assert(std::numeric_limits<si16>::max_exponent10 == std::numeric_limits<std::underlying_type_t<si16>>::max_exponent10);
static_assert(std::numeric_limits<si16>::has_infinity == std::numeric_limits<std::underlying_type_t<si16>>::has_infinity);
static_assert(std::numeric_limits<si16>::has_quiet_NaN == std::numeric_limits<std::underlying_type_t<si16>>::has_quiet_NaN);
static_assert(std::numeric_limits<si16>::has_signaling_NaN == std::numeric_limits<std::underlying_type_t<si16>>::has_signaling_NaN);
static_assert(std::numeric_limits<si16>::has_denorm == std::numeric_limits<std::underlying_type_t<si16>>::has_denorm);
static_assert(std::numeric_limits<si16>::has_denorm_loss == std::numeric_limits<std::underlying_type_t<si16>>::has_denorm_loss);
static_assert(std::numeric_limits<si16>::is_iec559 == std::numeric_limits<std::underlying_type_t<si16>>::is_iec559);
static_assert(std::numeric_limits<si16>::is_bounded == std::numeric_limits<std::underlying_type_t<si16>>::is_bounded);
static_assert(std::numeric_limits<si16>::tinyness_before == std::numeric_limits<std::underlying_type_t<si16>>::tinyness_before);
static_assert(std::numeric_limits<si16>::round_style == std::numeric_limits<std::underlying_type_t<si16>>::round_style);
static_assert(not std::numeric_limits<si16>::traps);
static_assert(std::numeric_limits<si16>::is_modulo);
static_assert(std::numeric_limits<si32>::min() == from_int(std::numeric_limits<std::underlying_type_t<si32>>::min()) );
static_assert(std::numeric_limits<si32>::max() == from_int(std::numeric_limits<std::underlying_type_t<si32>>::max()) );
static_assert(std::numeric_limits<si32>::lowest() == from_int(std::numeric_limits<std::underlying_type_t<si32>>::lowest()) );
static_assert(std::numeric_limits<si32>::epsilon() == from_int(std::numeric_limits<std::underlying_type_t<si32>>::epsilon()) );
static_assert(std::numeric_limits<si32>::round_error() == from_int(std::numeric_limits<std::underlying_type_t<si32>>::round_error()) );
static_assert(std::numeric_limits<si32>::infinity() == from_int(std::numeric_limits<std::underlying_type_t<si32>>::infinity()) );
static_assert(std::numeric_limits<si32>::quiet_NaN() == from_int(std::numeric_limits<std::underlying_type_t<si32>>::quiet_NaN()) );
static_assert(std::numeric_limits<si32>::signaling_NaN() == from_int(std::numeric_limits<std::underlying_type_t<si32>>::signaling_NaN()) );
static_assert(std::numeric_limits<si32>::denorm_min() == from_int(std::numeric_limits<std::underlying_type_t<si32>>::denorm_min()) );
static_assert(std::numeric_limits<si32>::is_specialized == std::numeric_limits<std::underlying_type_t<si32>>::is_specialized);
static_assert(std::numeric_limits<si32>::digits == std::numeric_limits<std::underlying_type_t<si32>>::digits);
static_assert(std::numeric_limits<si32>::digits10 == std::numeric_limits<std::underlying_type_t<si32>>::digits10);
static_assert(std::numeric_limits<si32>::max_digits10 == std::numeric_limits<std::underlying_type_t<si32>>::max_digits10);
static_assert(std::numeric_limits<si32>::is_signed == std::numeric_limits<std::underlying_type_t<si32>>::is_signed);
static_assert(std::numeric_limits<si32>::is_integer == std::numeric_limits<std::underlying_type_t<si32>>::is_integer);
static_assert(std::numeric_limits<si32>::is_exact == std::numeric_limits<std::underlying_type_t<si32>>::is_exact);
static_assert(std::numeric_limits<si32>::radix == std::numeric_limits<std::underlying_type_t<si32>>::radix);
static_assert(std::numeric_limits<si32>::min_exponent == std::numeric_limits<std::underlying_type_t<si32>>::min_exponent);
static_assert(std::numeric_limits<si32>::min_exponent10 == std::numeric_limits<std::underlying_type_t<si32>>::min_exponent10);
static_assert(std::numeric_limits<si32>::max_exponent == std::numeric_limits<std::underlying_type_t<si32>>::max_exponent);
static_assert(std::numeric_limits<si32>::max_exponent10 == std::numeric_limits<std::underlying_type_t<si32>>::max_exponent10);
static_assert(std::numeric_limits<si32>::has_infinity == std::numeric_limits<std::underlying_type_t<si32>>::has_infinity);
static_assert(std::numeric_limits<si32>::has_quiet_NaN == std::numeric_limits<std::underlying_type_t<si32>>::has_quiet_NaN);
static_assert(std::numeric_limits<si32>::has_signaling_NaN == std::numeric_limits<std::underlying_type_t<si32>>::has_signaling_NaN);
static_assert(std::numeric_limits<si32>::has_denorm == std::numeric_limits<std::underlying_type_t<si32>>::has_denorm);
static_assert(std::numeric_limits<si32>::has_denorm_loss == std::numeric_limits<std::underlying_type_t<si32>>::has_denorm_loss);
static_assert(std::numeric_limits<si32>::is_iec559 == std::numeric_limits<std::underlying_type_t<si32>>::is_iec559);
static_assert(std::numeric_limits<si32>::is_bounded == std::numeric_limits<std::underlying_type_t<si32>>::is_bounded);
static_assert(std::numeric_limits<si32>::tinyness_before == std::numeric_limits<std::underlying_type_t<si32>>::tinyness_before);
static_assert(std::numeric_limits<si32>::round_style == std::numeric_limits<std::underlying_type_t<si32>>::round_style);
static_assert(not std::numeric_limits<si32>::traps);
static_assert(std::numeric_limits<si32>::is_modulo);
static_assert(std::numeric_limits<si64>::min() == from_int(std::numeric_limits<std::underlying_type_t<si64>>::min()) );
static_assert(std::numeric_limits<si64>::max() == from_int(std::numeric_limits<std::underlying_type_t<si64>>::max()) );
static_assert(std::numeric_limits<si64>::lowest() == from_int(std::numeric_limits<std::underlying_type_t<si64>>::lowest()) );
static_assert(std::numeric_limits<si64>::epsilon() == from_int(std::numeric_limits<std::underlying_type_t<si64>>::epsilon()) );
static_assert(std::numeric_limits<si64>::round_error() == from_int(std::numeric_limits<std::underlying_type_t<si64>>::round_error()) );
static_assert(std::numeric_limits<si64>::infinity() == from_int(std::numeric_limits<std::underlying_type_t<si64>>::infinity()) );
static_assert(std::numeric_limits<si64>::quiet_NaN() == from_int(std::numeric_limits<std::underlying_type_t<si64>>::quiet_NaN()) );
static_assert(std::numeric_limits<si64>::signaling_NaN() == from_int(std::numeric_limits<std::underlying_type_t<si64>>::signaling_NaN()) );
static_assert(std::numeric_limits<si64>::denorm_min() == from_int(std::numeric_limits<std::underlying_type_t<si64>>::denorm_min()) );
static_assert(std::numeric_limits<si64>::is_specialized == std::numeric_limits<std::underlying_type_t<si64>>::is_specialized);
static_assert(std::numeric_limits<si64>::digits == std::numeric_limits<std::underlying_type_t<si64>>::digits);
static_assert(std::numeric_limits<si64>::digits10 == std::numeric_limits<std::underlying_type_t<si64>>::digits10);
static_assert(std::numeric_limits<si64>::max_digits10 == std::numeric_limits<std::underlying_type_t<si64>>::max_digits10);
static_assert(std::numeric_limits<si64>::is_signed == std::numeric_limits<std::underlying_type_t<si64>>::is_signed);
static_assert(std::numeric_limits<si64>::is_integer == std::numeric_limits<std::underlying_type_t<si64>>::is_integer);
static_assert(std::numeric_limits<si64>::is_exact == std::numeric_limits<std::underlying_type_t<si64>>::is_exact);
static_assert(std::numeric_limits<si64>::radix == std::numeric_limits<std::underlying_type_t<si64>>::radix);
static_assert(std::numeric_limits<si64>::min_exponent == std::numeric_limits<std::underlying_type_t<si64>>::min_exponent);
static_assert(std::numeric_limits<si64>::min_exponent10 == std::numeric_limits<std::underlying_type_t<si64>>::min_exponent10);
static_assert(std::numeric_limits<si64>::max_exponent == std::numeric_limits<std::underlying_type_t<si64>>::max_exponent);
static_assert(std::numeric_limits<si64>::max_exponent10 == std::numeric_limits<std::underlying_type_t<si64>>::max_exponent10);
static_assert(std::numeric_limits<si64>::has_infinity == std::numeric_limits<std::underlying_type_t<si64>>::has_infinity);
static_assert(std::numeric_limits<si64>::has_quiet_NaN == std::numeric_limits<std::underlying_type_t<si64>>::has_quiet_NaN);
static_assert(std::numeric_limits<si64>::has_signaling_NaN == std::numeric_limits<std::underlying_type_t<si64>>::has_signaling_NaN);
static_assert(std::numeric_limits<si64>::has_denorm == std::numeric_limits<std::underlying_type_t<si64>>::has_denorm);
static_assert(std::numeric_limits<si64>::has_denorm_loss == std::numeric_limits<std::underlying_type_t<si64>>::has_denorm_loss);
static_assert(std::numeric_limits<si64>::is_iec559 == std::numeric_limits<std::underlying_type_t<si64>>::is_iec559);
static_assert(std::numeric_limits<si64>::is_bounded == std::numeric_limits<std::underlying_type_t<si64>>::is_bounded);
static_assert(std::numeric_limits<si64>::tinyness_before == std::numeric_limits<std::underlying_type_t<si64>>::tinyness_before);
static_assert(std::numeric_limits<si64>::round_style == std::numeric_limits<std::underlying_type_t<si64>>::round_style);
static_assert(not std::numeric_limits<si64>::traps);
static_assert(std::numeric_limits<si64>::is_modulo);
static_assert(std::numeric_limits<ui8>::min() == from_int(std::numeric_limits<std::underlying_type_t<ui8>>::min()) );
static_assert(std::numeric_limits<ui8>::max() == from_int(std::numeric_limits<std::underlying_type_t<ui8>>::max()) );
static_assert(std::numeric_limits<ui8>::lowest() == from_int(std::numeric_limits<std::underlying_type_t<ui8>>::lowest()) );
static_assert(std::numeric_limits<ui8>::epsilon() == from_int(std::numeric_limits<std::underlying_type_t<ui8>>::epsilon()) );
static_assert(std::numeric_limits<ui8>::round_error() == from_int(std::numeric_limits<std::underlying_type_t<ui8>>::round_error()) );
static_assert(std::numeric_limits<ui8>::infinity() == from_int(std::numeric_limits<std::underlying_type_t<ui8>>::infinity()) );
static_assert(std::numeric_limits<ui8>::quiet_NaN() == from_int(std::numeric_limits<std::underlying_type_t<ui8>>::quiet_NaN()) );
static_assert(std::numeric_limits<ui8>::signaling_NaN() == from_int(std::numeric_limits<std::underlying_type_t<ui8>>::signaling_NaN()) );
static_assert(std::numeric_limits<ui8>::denorm_min() == from_int(std::numeric_limits<std::underlying_type_t<ui8>>::denorm_min()) );
static_assert(std::numeric_limits<ui8>::is_specialized == std::numeric_limits<std::underlying_type_t<ui8>>::is_specialized);
static_assert(std::numeric_limits<ui8>::digits == std::numeric_limits<std::underlying_type_t<ui8>>::digits);
static_assert(std::numeric_limits<ui8>::digits10 == std::numeric_limits<std::underlying_type_t<ui8>>::digits10);
static_assert(std::numeric_limits<ui8>::max_digits10 == std::numeric_limits<std::underlying_type_t<ui8>>::max_digits10);
static_assert(std::numeric_limits<ui8>::is_signed == std::numeric_limits<std::underlying_type_t<ui8>>::is_signed);
static_assert(std::numeric_limits<ui8>::is_integer == std::numeric_limits<std::underlying_type_t<ui8>>::is_integer);
static_assert(std::numeric_limits<ui8>::is_exact == std::numeric_limits<std::underlying_type_t<ui8>>::is_exact);
static_assert(std::numeric_limits<ui8>::radix == std::numeric_limits<std::underlying_type_t<ui8>>::radix);
static_assert(std::numeric_limits<ui8>::min_exponent == std::numeric_limits<std::underlying_type_t<ui8>>::min_exponent);
static_assert(std::numeric_limits<ui8>::min_exponent10 == std::numeric_limits<std::underlying_type_t<ui8>>::min_exponent10);
static_assert(std::numeric_limits<ui8>::max_exponent == std::numeric_limits<std::underlying_type_t<ui8>>::max_exponent);
static_assert(std::numeric_limits<ui8>::max_exponent10 == std::numeric_limits<std::underlying_type_t<ui8>>::max_exponent10);
static_assert(std::numeric_limits<ui8>::has_infinity == std::numeric_limits<std::underlying_type_t<ui8>>::has_infinity);
static_assert(std::numeric_limits<ui8>::has_quiet_NaN == std::numeric_limits<std::underlying_type_t<ui8>>::has_quiet_NaN);
static_assert(std::numeric_limits<ui8>::has_signaling_NaN == std::numeric_limits<std::underlying_type_t<ui8>>::has_signaling_NaN);
static_assert(std::numeric_limits<ui8>::has_denorm == std::numeric_limits<std::underlying_type_t<ui8>>::has_denorm);
static_assert(std::numeric_limits<ui8>::has_denorm_loss == std::numeric_limits<std::underlying_type_t<ui8>>::has_denorm_loss);
static_assert(std::numeric_limits<ui8>::is_iec559 == std::numeric_limits<std::underlying_type_t<ui8>>::is_iec559);
static_assert(std::numeric_limits<ui8>::is_bounded == std::numeric_limits<std::underlying_type_t<ui8>>::is_bounded);
static_assert(std::numeric_limits<ui8>::tinyness_before == std::numeric_limits<std::underlying_type_t<ui8>>::tinyness_before);
static_assert(std::numeric_limits<ui8>::round_style == std::numeric_limits<std::underlying_type_t<ui8>>::round_style);
static_assert(not std::numeric_limits<ui8>::traps);
static_assert(std::numeric_limits<ui8>::is_modulo);
static_assert(std::numeric_limits<ui16>::min() == from_int(std::numeric_limits<std::underlying_type_t<ui16>>::min()) );
static_assert(std::numeric_limits<ui16>::max() == from_int(std::numeric_limits<std::underlying_type_t<ui16>>::max()) );
static_assert(std::numeric_limits<ui16>::lowest() == from_int(std::numeric_limits<std::underlying_type_t<ui16>>::lowest()) );
static_assert(std::numeric_limits<ui16>::epsilon() == from_int(std::numeric_limits<std::underlying_type_t<ui16>>::epsilon()) );
static_assert(std::numeric_limits<ui16>::round_error() == from_int(std::numeric_limits<std::underlying_type_t<ui16>>::round_error()) );
static_assert(std::numeric_limits<ui16>::infinity() == from_int(std::numeric_limits<std::underlying_type_t<ui16>>::infinity()) );
static_assert(std::numeric_limits<ui16>::quiet_NaN() == from_int(std::numeric_limits<std::underlying_type_t<ui16>>::quiet_NaN()) );
static_assert(std::numeric_limits<ui16>::signaling_NaN() == from_int(std::numeric_limits<std::underlying_type_t<ui16>>::signaling_NaN()) );
static_assert(std::numeric_limits<ui16>::denorm_min() == from_int(std::numeric_limits<std::underlying_type_t<ui16>>::denorm_min()) );
static_assert(std::numeric_limits<ui16>::is_specialized == std::numeric_limits<std::underlying_type_t<ui16>>::is_specialized);
static_assert(std::numeric_limits<ui16>::digits == std::numeric_limits<std::underlying_type_t<ui16>>::digits);
static_assert(std::numeric_limits<ui16>::digits10 == std::numeric_limits<std::underlying_type_t<ui16>>::digits10);
static_assert(std::numeric_limits<ui16>::max_digits10 == std::numeric_limits<std::underlying_type_t<ui16>>::max_digits10);
static_assert(std::numeric_limits<ui16>::is_signed == std::numeric_limits<std::underlying_type_t<ui16>>::is_signed);
static_assert(std::numeric_limits<ui16>::is_integer == std::numeric_limits<std::underlying_type_t<ui16>>::is_integer);
static_assert(std::numeric_limits<ui16>::is_exact == std::numeric_limits<std::underlying_type_t<ui16>>::is_exact);
static_assert(std::numeric_limits<ui16>::radix == std::numeric_limits<std::underlying_type_t<ui16>>::radix);
static_assert(std::numeric_limits<ui16>::min_exponent == std::numeric_limits<std::underlying_type_t<ui16>>::min_exponent);
static_assert(std::numeric_limits<ui16>::min_exponent10 == std::numeric_limits<std::underlying_type_t<ui16>>::min_exponent10);
static_assert(std::numeric_limits<ui16>::max_exponent == std::numeric_limits<std::underlying_type_t<ui16>>::max_exponent);
static_assert(std::numeric_limits<ui16>::max_exponent10 == std::numeric_limits<std::underlying_type_t<ui16>>::max_exponent10);
static_assert(std::numeric_limits<ui16>::has_infinity == std::numeric_limits<std::underlying_type_t<ui16>>::has_infinity);
static_assert(std::numeric_limits<ui16>::has_quiet_NaN == std::numeric_limits<std::underlying_type_t<ui16>>::has_quiet_NaN);
static_assert(std::numeric_limits<ui16>::has_signaling_NaN == std::numeric_limits<std::underlying_type_t<ui16>>::has_signaling_NaN);
static_assert(std::numeric_limits<ui16>::has_denorm == std::numeric_limits<std::underlying_type_t<ui16>>::has_denorm);
static_assert(std::numeric_limits<ui16>::has_denorm_loss == std::numeric_limits<std::underlying_type_t<ui16>>::has_denorm_loss);
static_assert(std::numeric_limits<ui16>::is_iec559 == std::numeric_limits<std::underlying_type_t<ui16>>::is_iec559);
static_assert(std::numeric_limits<ui16>::is_bounded == std::numeric_limits<std::underlying_type_t<ui16>>::is_bounded);
static_assert(std::numeric_limits<ui16>::tinyness_before == std::numeric_limits<std::underlying_type_t<ui16>>::tinyness_before);
static_assert(std::numeric_limits<ui16>::round_style == std::numeric_limits<std::underlying_type_t<ui16>>::round_style);
static_assert(not std::numeric_limits<ui16>::traps);
static_assert(std::numeric_limits<ui16>::is_modulo);
static_assert(std::numeric_limits<ui32>::min() == from_int(std::numeric_limits<std::underlying_type_t<ui32>>::min()) );
static_assert(std::numeric_limits<ui32>::max() == from_int(std::numeric_limits<std::underlying_type_t<ui32>>::max()) );
static_assert(std::numeric_limits<ui32>::lowest() == from_int(std::numeric_limits<std::underlying_type_t<ui32>>::lowest()) );
static_assert(std::numeric_limits<ui32>::epsilon() == from_int(std::numeric_limits<std::underlying_type_t<ui32>>::epsilon()) );
static_assert(std::numeric_limits<ui32>::round_error() == from_int(std::numeric_limits<std::underlying_type_t<ui32>>::round_error()) );
static_assert(std::numeric_limits<ui32>::infinity() == from_int(std::numeric_limits<std::underlying_type_t<ui32>>::infinity()) );
static_assert(std::numeric_limits<ui32>::quiet_NaN() == from_int(std::numeric_limits<std::underlying_type_t<ui32>>::quiet_NaN()) );
static_assert(std::numeric_limits<ui32>::signaling_NaN() == from_int(std::numeric_limits<std::underlying_type_t<ui32>>::signaling_NaN()) );
static_assert(std::numeric_limits<ui32>::denorm_min() == from_int(std::numeric_limits<std::underlying_type_t<ui32>>::denorm_min()) );
static_assert(std::numeric_limits<ui32>::is_specialized == std::numeric_limits<std::underlying_type_t<ui32>>::is_specialized);
static_assert(std::numeric_limits<ui32>::digits == std::numeric_limits<std::underlying_type_t<ui32>>::digits);
static_assert(std::numeric_limits<ui32>::digits10 == std::numeric_limits<std::underlying_type_t<ui32>>::digits10);
static_assert(std::numeric_limits<ui32>::max_digits10 == std::numeric_limits<std::underlying_type_t<ui32>>::max_digits10);
static_assert(std::numeric_limits<ui32>::is_signed == std::numeric_limits<std::underlying_type_t<ui32>>::is_signed);
static_assert(std::numeric_limits<ui32>::is_integer == std::numeric_limits<std::underlying_type_t<ui32>>::is_integer);
static_assert(std::numeric_limits<ui32>::is_exact == std::numeric_limits<std::underlying_type_t<ui32>>::is_exact);
static_assert(std::numeric_limits<ui32>::radix == std::numeric_limits<std::underlying_type_t<ui32>>::radix);
static_assert(std::numeric_limits<ui32>::min_exponent == std::numeric_limits<std::underlying_type_t<ui32>>::min_exponent);
static_assert(std::numeric_limits<ui32>::min_exponent10 == std::numeric_limits<std::underlying_type_t<ui32>>::min_exponent10);
static_assert(std::numeric_limits<ui32>::max_exponent == std::numeric_limits<std::underlying_type_t<ui32>>::max_exponent);
static_assert(std::numeric_limits<ui32>::max_exponent10 == std::numeric_limits<std::underlying_type_t<ui32>>::max_exponent10);
static_assert(std::numeric_limits<ui32>::has_infinity == std::numeric_limits<std::underlying_type_t<ui32>>::has_infinity);
static_assert(std::numeric_limits<ui32>::has_quiet_NaN == std::numeric_limits<std::underlying_type_t<ui32>>::has_quiet_NaN);
static_assert(std::numeric_limits<ui32>::has_signaling_NaN == std::numeric_limits<std::underlying_type_t<ui32>>::has_signaling_NaN);
static_assert(std::numeric_limits<ui32>::has_denorm == std::numeric_limits<std::underlying_type_t<ui32>>::has_denorm);
static_assert(std::numeric_limits<ui32>::has_denorm_loss == std::numeric_limits<std::underlying_type_t<ui32>>::has_denorm_loss);
static_assert(std::numeric_limits<ui32>::is_iec559 == std::numeric_limits<std::underlying_type_t<ui32>>::is_iec559);
static_assert(std::numeric_limits<ui32>::is_bounded == std::numeric_limits<std::underlying_type_t<ui32>>::is_bounded);
static_assert(std::numeric_limits<ui32>::tinyness_before == std::numeric_limits<std::underlying_type_t<ui32>>::tinyness_before);
static_assert(std::numeric_limits<ui32>::round_style == std::numeric_limits<std::underlying_type_t<ui32>>::round_style);
static_assert(not std::numeric_limits<ui32>::traps);
static_assert(std::numeric_limits<ui32>::is_modulo);
static_assert(std::numeric_limits<ui64>::min() == from_int(std::numeric_limits<std::underlying_type_t<ui64>>::min()) );
static_assert(std::numeric_limits<ui64>::max() == from_int(std::numeric_limits<std::underlying_type_t<ui64>>::max()) );
static_assert(std::numeric_limits<ui64>::lowest() == from_int(std::numeric_limits<std::underlying_type_t<ui64>>::lowest()) );
static_assert(std::numeric_limits<ui64>::epsilon() == from_int(std::numeric_limits<std::underlying_type_t<ui64>>::epsilon()) );
static_assert(std::numeric_limits<ui64>::round_error() == from_int(std::numeric_limits<std::underlying_type_t<ui64>>::round_error()) );
static_assert(std::numeric_limits<ui64>::infinity() == from_int(std::numeric_limits<std::underlying_type_t<ui64>>::infinity()) );
static_assert(std::numeric_limits<ui64>::quiet_NaN() == from_int(std::numeric_limits<std::underlying_type_t<ui64>>::quiet_NaN()) );
static_assert(std::numeric_limits<ui64>::signaling_NaN() == from_int(std::numeric_limits<std::underlying_type_t<ui64>>::signaling_NaN()) );
static_assert(std::numeric_limits<ui64>::denorm_min() == from_int(std::numeric_limits<std::underlying_type_t<ui64>>::denorm_min()) );
static_assert(std::numeric_limits<ui64>::is_specialized == std::numeric_limits<std::underlying_type_t<ui64>>::is_specialized);
static_assert(std::numeric_limits<ui64>::digits == std::numeric_limits<std::underlying_type_t<ui64>>::digits);
static_assert(std::numeric_limits<ui64>::digits10 == std::numeric_limits<std::underlying_type_t<ui64>>::digits10);
static_assert(std::numeric_limits<ui64>::max_digits10 == std::numeric_limits<std::underlying_type_t<ui64>>::max_digits10);
static_assert(std::numeric_limits<ui64>::is_signed == std::numeric_limits<std::underlying_type_t<ui64>>::is_signed);
static_assert(std::numeric_limits<ui64>::is_integer == std::numeric_limits<std::underlying_type_t<ui64>>::is_integer);
static_assert(std::numeric_limits<ui64>::is_exact == std::numeric_limits<std::underlying_type_t<ui64>>::is_exact);
static_assert(std::numeric_limits<ui64>::radix == std::numeric_limits<std::underlying_type_t<ui64>>::radix);
static_assert(std::numeric_limits<ui64>::min_exponent == std::numeric_limits<std::underlying_type_t<ui64>>::min_exponent);
static_assert(std::numeric_limits<ui64>::min_exponent10 == std::numeric_limits<std::underlying_type_t<ui64>>::min_exponent10);
static_assert(std::numeric_limits<ui64>::max_exponent == std::numeric_limits<std::underlying_type_t<ui64>>::max_exponent);
static_assert(std::numeric_limits<ui64>::max_exponent10 == std::numeric_limits<std::underlying_type_t<ui64>>::max_exponent10);
static_assert(std::numeric_limits<ui64>::has_infinity == std::numeric_limits<std::underlying_type_t<ui64>>::has_infinity);
static_assert(std::numeric_limits<ui64>::has_quiet_NaN == std::numeric_limits<std::underlying_type_t<ui64>>::has_quiet_NaN);
static_assert(std::numeric_limits<ui64>::has_signaling_NaN == std::numeric_limits<std::underlying_type_t<ui64>>::has_signaling_NaN);
static_assert(std::numeric_limits<ui64>::has_denorm == std::numeric_limits<std::underlying_type_t<ui64>>::has_denorm);
static_assert(std::numeric_limits<ui64>::has_denorm_loss == std::numeric_limits<std::underlying_type_t<ui64>>::has_denorm_loss);
static_assert(std::numeric_limits<ui64>::is_iec559 == std::numeric_limits<std::underlying_type_t<ui64>>::is_iec559);
static_assert(std::numeric_limits<ui64>::is_bounded == std::numeric_limits<std::underlying_type_t<ui64>>::is_bounded);
static_assert(std::numeric_limits<ui64>::tinyness_before == std::numeric_limits<std::underlying_type_t<ui64>>::tinyness_before);
static_assert(std::numeric_limits<ui64>::round_style == std::numeric_limits<std::underlying_type_t<ui64>>::round_style);
static_assert(not std::numeric_limits<ui64>::traps);
static_assert(std::numeric_limits<ui64>::is_modulo);

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

template<typename T, typename WHAT>
constexpr bool
isa = std::is_same_v<std::remove_cvref_t<T>,WHAT>;


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


int main() {
  using namespace psssint::literals;



  
  auto i8 = 42_si8;
  auto ui8 = 42_ui8;
}
