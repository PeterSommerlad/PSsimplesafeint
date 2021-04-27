#include "psssafeint.h"

// this file content is generated
// it tests all numeric limits members of all integer replacement types against their corresponding underlying types

/* File: ../generatenumericlmitstests.sh
#!/bin/sh

for safeint in si8 si16 si32 si64 ui8 ui16 ui32 ui64
do

for func in min max lowest epsilon round_error infinity quiet_NaN signaling_NaN denorm_min
do
  echo "static_assert(std::numeric_limits<$safeint>::$func() == from_int(std::numeric_limits<std::underlying_type_t<$safeint>>::$func()) );"


done

for variable in is_specialized digits digits10 max_digits10 is_signed is_integer is_exact radix min_exponent min_exponent10 max_exponent max_exponent10 \
                has_infinity has_quiet_NaN has_signaling_NaN has_denorm has_denorm_loss is_iec559 is_bounded traps tinyness_before round_style
do
  echo "static_assert(std::numeric_limits<$safeint>::$variable == std::numeric_limits<std::underlying_type_t<$safeint>>::$variable);"

done

  echo "static_assert(std::numeric_limits<$safeint>::is_modulo);"

done

// plus ensure that is_modulo is actually true


*/
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
static_assert(not std::numeric_limits<si8>::traps);
static_assert(std::numeric_limits<si8>::tinyness_before == std::numeric_limits<std::underlying_type_t<si8>>::tinyness_before);
static_assert(std::numeric_limits<si8>::round_style == std::numeric_limits<std::underlying_type_t<si8>>::round_style);
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
static_assert(not std::numeric_limits<si16>::traps);
static_assert(std::numeric_limits<si16>::tinyness_before == std::numeric_limits<std::underlying_type_t<si16>>::tinyness_before);
static_assert(std::numeric_limits<si16>::round_style == std::numeric_limits<std::underlying_type_t<si16>>::round_style);
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
static_assert(not std::numeric_limits<si32>::traps );
static_assert(std::numeric_limits<si32>::tinyness_before == std::numeric_limits<std::underlying_type_t<si32>>::tinyness_before);
static_assert(std::numeric_limits<si32>::round_style == std::numeric_limits<std::underlying_type_t<si32>>::round_style);
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
static_assert(not std::numeric_limits<si64>::traps);
static_assert(std::numeric_limits<si64>::tinyness_before == std::numeric_limits<std::underlying_type_t<si64>>::tinyness_before);
static_assert(std::numeric_limits<si64>::round_style == std::numeric_limits<std::underlying_type_t<si64>>::round_style);
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
static_assert(not std::numeric_limits<ui8>::traps );
static_assert(std::numeric_limits<ui8>::tinyness_before == std::numeric_limits<std::underlying_type_t<ui8>>::tinyness_before);
static_assert(std::numeric_limits<ui8>::round_style == std::numeric_limits<std::underlying_type_t<ui8>>::round_style);
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
static_assert(not std::numeric_limits<ui16>::traps );
static_assert(std::numeric_limits<ui16>::tinyness_before == std::numeric_limits<std::underlying_type_t<ui16>>::tinyness_before);
static_assert(std::numeric_limits<ui16>::round_style == std::numeric_limits<std::underlying_type_t<ui16>>::round_style);
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
static_assert(not std::numeric_limits<ui32>::traps );
static_assert(std::numeric_limits<ui32>::tinyness_before == std::numeric_limits<std::underlying_type_t<ui32>>::tinyness_before);
static_assert(std::numeric_limits<ui32>::round_style == std::numeric_limits<std::underlying_type_t<ui32>>::round_style);
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
static_assert(not std::numeric_limits<ui64>::traps );
static_assert(std::numeric_limits<ui64>::tinyness_before == std::numeric_limits<std::underlying_type_t<ui64>>::tinyness_before);
static_assert(std::numeric_limits<ui64>::round_style == std::numeric_limits<std::underlying_type_t<ui64>>::round_style);
static_assert(std::numeric_limits<ui64>::is_modulo);
