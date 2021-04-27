#!/bin/sh

for safeint in si8 si16 si32 si64 ui8 ui16 ui32 ui64
do

for func in min max lowest epsilon round_error infinity quiet_NaN signaling_NaN denorm_min
do
  echo "static_assert(std::numeric_limits<$safeint>::$func() == from_int(std::numeric_limits<std::underlying_type_t<$safeint>>::$func()) );"


done

for variable in is_specialized digits digits10 max_digits10 is_signed is_integer is_exact radix min_exponent min_exponent10 max_exponent max_exponent10 \
                has_infinity has_quiet_NaN has_signaling_NaN has_denorm has_denorm_loss is_iec559 is_bounded tinyness_before round_style
do
  echo "static_assert(std::numeric_limits<$safeint>::$variable == std::numeric_limits<std::underlying_type_t<$safeint>>::$variable);"

done

  echo "static_assert(not std::numeric_limits<$safeint>::traps);"
  echo "static_assert(std::numeric_limits<$safeint>::is_modulo);"

done
