# PSsimplesafeint

![tests](https://github.com/PeterSommerlad/PSsimplesafeint/actions/workflows/runtests.yml/badge.svg?branch=main)

<br/>

![conan check](https://github.com/PeterSommerlad/PSsimplesafeint/actions/workflows/runconantest.yml/badge.svg?branch=main)

## IMPORTANT UPDATE (as of 2021-09-08)

It turned out that signed integer division and sign extension is harder to get right than I naïvely thought. 
However, more test cases helped to figure out the corner cases either not covered, or causing UB.
If you are already using this library, please update!


## Introduction

A C++20 implementation of safe (wrap around) integers following MISRA C++ rules.

An `#ifdef`ed C++17 implementation is available in branch C++17.


It provides the following types in `namspace psssint` and corresponding UDL operators in `namespace psssint::literals`:

```C++
// unsigned
enum class ui8;   auto a = 1_ui8;
enum class ui16;  auto b = 2_ui16;
enum class ui32;  auto c = 3_ui32;
enum class ui64;  auto d = 4_ui64;
// signed
enum class si8;   auto e = 5_si8;
enum class si16;  auto f = 6_si16;
enum class si32;  auto g = 7_si32;
enum class si64;  auto h = 8_si64;
```

You can play around with it on compiler explorer starting [here](https://godbolt.org/z/TvnrrEzEK)


Some extra features:
* an output operator is defined and will output `ui8` and `si8` as integer values.
* The UDL operators check for range.
* not recommended features:
   * `to_int(val)` promotes the safe integer val to built-in integer keeping its signedness
   * `to_underlying(val)` allows access to the underlying-type's value, use with care in operations because of promotion. This is useful for existing function overloads.
   * `from_int(val)` converts one of the allowed integer type's value to corresponding safe integer type. This is useful for integration with not-yet adapted code. Prevents conversion from `char` and `bool`, Note that depending on the definition of the types in `<cstdint>` not all built-in integer types will convert, for example, if `std::int32_t` is defined as `int` and `std::int64_t` is defined as `long long`, you cannot convert a `42L`, because its conversion rank differs from both. 
   * `from_int_to<safeinttype>(val)` converts integer to safe integer type with range check (throws if mismatch).

The following MISRA C++ recommendations for integer usage are implemented:

* No mixing of signed and unsigned types or with any standard-defined arithmetic types
* Integral promotion (only when mixing types in operations) will keep signedness
* Operations using the same operand type result in said type (no implicit promotion)
* Operations using mixed types of the same signedness promote to the bigger type first
* All operations wrap safely (2's complement), even for signed operands and small unsigned operands
* Bitwise operations are only defined for unsigned types
* Negation is only defined for signed types
* Comparison is only available through operands of the same type, using built-in comparison (`<=>` in 20)

What else do you want?
