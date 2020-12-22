# PSsimplesafeint
A C++20 implementation of safe (wrap around) integers following MISRA C++ rules.

I might also work on a C++17 implementation, but this will look uglier due to SFINAE and DIY comparison.


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

Some extra features:
* an output operator is defined
* The UDL operators check for range.
* not recommended features:
   * `to_int(val)` promotes the safe integer val to built-in integer keeping its signedness
   * `to_underlying(val)` allows access to the underlying-type's value, use with care in operations.
   * `from_int(val)` converts allowed integer type's value to corresponding safe integer type.
   * `from_int_to<safeinttype>(val)` converts integer to safe integer type with range check (throws).

The following MISRA C++ recommendations for integer usage are implemented:

* No mixing of signed and unsigned types or with any standard-defined arithmetic types
* Integral promotion (only when mixing types in operations) will keep signedness
* Operations using the same operand type result in said type (no implicit promotion)
* Operations using mixed types of the same signedness promote to the bigger type first
* All operations wrap safely (2's complement), even for signed operands
* Bitwise operations are only defined for unsigned types
* Negation is only defined for signed types
* Comparison is only available through operands of the same type, using built-in `<=>`

What else do you want?
