#ifndef SRC_PSSAFEINT_
#define SRC_PSSAFEINT_

#include <cstdint>
#include <type_traits>
#include <iosfwd>
#include <limits>
#include <climits>
#ifdef __cpp_concepts
#include <concepts> // std::integral
#endif



#ifdef NDEBUG
  #ifdef __cpp_lib_is_constant_evaluated
    #define ps_assert(default_value, cond) \
        if (std::is_constant_evaluated()) {\
           if (not (cond)) throw(#cond); /* compile error */\
        } else {\
           if (not (cond) ) return default_value;/* last resort avoid UB */\
        }
  # else /* C++17 */
    #define ps_assert(default_value, cond) \
        { if (not (cond) ) return default_value;/* last resort avoid UB */ }
  #endif
  #define NOEXCEPT_WITH_THROWING_ASSERTS noexcept
#else
  #ifdef PS_ASSERT_THROWS
    #define ps_assert(default_value, cond)  ((cond)?true: throw(#cond))
    #define NOEXCEPT_WITH_THROWING_ASSERTS noexcept(false)

  #else
    #include <cassert>
    #define ps_assert(default_value, cond) assert(cond)
    #define NOEXCEPT_WITH_THROWING_ASSERTS noexcept
  #endif
#endif




namespace psssint { // Peter Sommerlad's simple safe integers

// unsigned 
enum class ui8 : std::uint8_t { tag_to_prevent_mixing_other_enums };
enum class ui16: std::uint16_t{ tag_to_prevent_mixing_other_enums };
enum class ui32: std::uint32_t{ tag_to_prevent_mixing_other_enums };
enum class ui64: std::uint64_t{ tag_to_prevent_mixing_other_enums };

inline namespace literals {

#ifndef __cpp_consteval
    #ifdef __clang__
        #pragma clang diagnostic push
        #pragma clang diagnostic ignored "-Wkeyword-macro"
    #endif
#define consteval constexpr
    #ifdef __clang__
        #pragma clang diagnostic pop
    #endif
#endif

consteval
ui8 operator""_ui8(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<ui8>>::max()) {
        return ui8(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
ui16 operator""_ui16(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<ui16>>::max()) {
        return ui16(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
ui32 operator""_ui32(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<ui32>>::max()) {
        return ui32(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
ui64 operator""_ui64(unsigned long long val) {
    if constexpr (sizeof(ui64) < sizeof(val)){
        if (val > 0xffff'ffff'fffffffful) {
            throw "integral constant too large"; // trigger compile-time error
        }
    }
    return ui64(val);
}

}
// signed
enum class si8 : std::int8_t { tag_to_prevent_mixing_other_enums };
enum class si16: std::int16_t{tag_to_prevent_mixing_other_enums};
enum class si32: std::int32_t{tag_to_prevent_mixing_other_enums};
enum class si64: std::int64_t{tag_to_prevent_mixing_other_enums};

inline namespace literals {
consteval
si8 operator""_si8(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<si8>>::max()) {
        return si8(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
si16 operator""_si16(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<si16>>::max()) {
        return si16(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
si32 operator""_si32(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<si32>>::max()) {
        return si32(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}


consteval
si64 operator""_si64(unsigned long long val) {
    if (val <= std::numeric_limits<std::underlying_type_t<si64>>::max()) {
        return si64(val);
    } else {
        throw "integral constant too large"; // trigger compile-time error
    }
}
#ifndef __cpp_consteval
#undef consteval
#endif

}


template<typename T>
using plain = std::remove_reference_t<std::remove_cv_t<T>>;



#ifdef __cpp_concepts
template<typename T>
concept an_enum = std::is_enum_v<plain<T>>;
#endif

namespace detail_ {
// from C++23
#ifdef __cpp_concepts
template<an_enum T>
#else
template<typename T, auto = std::enable_if_t<std::is_enum_v<plain<T>>,void*>{nullptr}>
#endif
constexpr bool
is_scoped_enum_v = !std::is_convertible_v<T, std::underlying_type_t<T>>;

#ifdef __cpp_concepts
template<typename T>
concept a_scoped_enum = is_scoped_enum_v<T>;
#endif

// detection concept

template<typename T, typename = void>
constexpr bool
is_safeint_v = false;

template<typename E>
constexpr bool
is_safeint_v<E,std::void_t<decltype( E{} == E::tag_to_prevent_mixing_other_enums )>> = std::is_enum_v<E> ;


template<typename E, std::enable_if_t<std::is_enum_v<plain<E>>, bool> = true>
using ULT=std::underlying_type_t<plain<E>>;

template<typename E>
using promoted_t = // will promote keeping signedness
        std::conditional_t<(sizeof(ULT<E>) < sizeof(int))
            , std::conditional_t<std::is_unsigned_v<ULT<E>>
                , unsigned
                , int >
            , ULT<E>>;

template<typename type, std::enable_if_t<psssint::detail_::is_safeint_v<type>,bool> = true>
  struct numeric_limits
  {
    using ult = psssint::detail_::ULT<type>;
    static constexpr bool is_specialized = true;

    static constexpr type
    min() noexcept { return type{std::numeric_limits<ult>::min()}; }

    static constexpr type
    max() noexcept { return type{std::numeric_limits<ult>::max()}; }

    static constexpr type
    lowest() noexcept { return type{std::numeric_limits<ult>::lowest()}; }

    static constexpr int digits = std::numeric_limits<ult>::digits;
    static constexpr int digits10 = std::numeric_limits<ult>::digits10;
    static constexpr int max_digits10 = std::numeric_limits<ult>::max_digits10;
    static constexpr bool is_signed = std::numeric_limits<ult>::is_signed;
    static constexpr bool is_integer = std::numeric_limits<ult>::is_integer;
    static constexpr bool is_exact = std::numeric_limits<ult>::is_exact;
    static constexpr int radix = std::numeric_limits<ult>::radix;

    static constexpr type
    epsilon() noexcept {  return type{std::numeric_limits<ult>::epsilon()}; }

    static constexpr type
    round_error() noexcept {  return type{std::numeric_limits<ult>::round_error()}; }

    static constexpr int min_exponent = std::numeric_limits<ult>::min_exponent;
    static constexpr int min_exponent10 = std::numeric_limits<ult>::min_exponent10;
    static constexpr int max_exponent = std::numeric_limits<ult>::max_exponent;
    static constexpr int max_exponent10 = std::numeric_limits<ult>::max_exponent10;

    static constexpr bool has_infinity = std::numeric_limits<ult>::has_infinity;
    static constexpr bool has_quiet_NaN = std::numeric_limits<ult>::has_quiet_NaN;
    static constexpr bool has_signaling_NaN = std::numeric_limits<ult>::has_signaling_NaN;
    static constexpr std::float_denorm_style has_denorm
     = std::numeric_limits<ult>::has_denorm;
    static constexpr bool has_denorm_loss = std::numeric_limits<ult>::has_denorm_loss;

    static constexpr type
    infinity() noexcept { return type{std::numeric_limits<ult>::infinity()}; }

    static constexpr type
    quiet_NaN() noexcept { return type{std::numeric_limits<ult>::quiet_NaN()}; }

    static constexpr type
    signaling_NaN() noexcept
    { return type{std::numeric_limits<ult>::signaling_NaN()}; }

    static constexpr type
    denorm_min() noexcept
    { return type{std::numeric_limits<ult>::denorm_min()}; }


    static constexpr bool is_iec559 =  std::numeric_limits<ult>::is_iec559;
    static constexpr bool is_bounded =  std::numeric_limits<ult>::is_bounded;
    static constexpr bool is_modulo =  true;

    static constexpr bool traps = false;
    static constexpr bool tinyness_before =  std::numeric_limits<ult>::tinyness_before;
    static constexpr std::float_round_style round_style =  std::numeric_limits<ult>::round_style;
  };

}


#ifdef __cpp_concepts
template<typename E>
concept a_safeint = detail_::is_safeint_v<E>;
#endif

} // psssint


// provide std::numeric_limits
namespace std {

template<>
struct numeric_limits<psssint::si8>: psssint::detail_::numeric_limits<psssint::si8>{};
template<>
struct numeric_limits<psssint::si16>: psssint::detail_::numeric_limits<psssint::si16>{};
template<>
struct numeric_limits<psssint::si32>: psssint::detail_::numeric_limits<psssint::si32>{};
template<>
struct numeric_limits<psssint::si64>: psssint::detail_::numeric_limits<psssint::si64>{};
template<>
struct numeric_limits<psssint::ui8>: psssint::detail_::numeric_limits<psssint::ui8>{};
template<>
struct numeric_limits<psssint::ui16>: psssint::detail_::numeric_limits<psssint::ui16>{};
template<>
struct numeric_limits<psssint::ui32>: psssint::detail_::numeric_limits<psssint::ui32>{};
template<>
struct numeric_limits<psssint::ui64>: psssint::detail_::numeric_limits<psssint::ui64>{};



}

namespace psssint{

namespace detail_{

#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F>
#endif
constexpr bool
same_signedness_v = detail_::is_safeint_v<E> && detail_::is_safeint_v<F> && std::numeric_limits<E>::is_signed == std::numeric_limits<F>::is_signed;

template<typename CHAR>
constexpr bool
is_chartype_v =    std::is_same_v<char,CHAR>
                || std::is_same_v<wchar_t,CHAR>
#ifdef __cpp_char8_t
                || std::is_same_v<char8_t,CHAR>
#endif
                || std::is_same_v<char16_t,CHAR>
                || std::is_same_v<char32_t,CHAR> ;



template<typename INT, typename TESTED>
constexpr bool
is_compatible_integer_v = std::is_same_v<TESTED,INT> ||
   (   std::is_integral_v<TESTED>
   && !std::is_same_v<bool,TESTED>
   && !is_chartype_v<TESTED>
   && (std::is_unsigned_v<INT> == std::is_unsigned_v<TESTED>)
   && std::numeric_limits<TESTED>::max() == std::numeric_limits<INT>::max() );

template<typename INT, typename TESTED>
constexpr bool
is_similar_v=is_compatible_integer_v<INT,TESTED>;

template<typename TESTED>
constexpr bool
is_known_integer_v =    is_similar_v<std::uint8_t,  TESTED>
                     || is_similar_v<std::uint16_t, TESTED>
                     || is_similar_v<std::uint32_t, TESTED>
                     || is_similar_v<std::uint64_t, TESTED>
                     || is_similar_v<std::int8_t,  TESTED>
                     || is_similar_v<std::int16_t, TESTED>
                     || is_similar_v<std::int32_t, TESTED>
                     || is_similar_v<std::int64_t, TESTED>;

}



#ifdef __cpp_concepts
template<typename E, typename F>
concept same_signedness = detail_::same_signedness_v<E,F>;
#endif

#ifdef __cpp_concepts
template<a_safeint E>
#else
template <typename E>
#endif
constexpr auto
to_int(E val) noexcept
#ifndef __cpp_concepts
-> std::enable_if_t<detail_::is_safeint_v<E>,detail_::promoted_t<E>>
#endif
{ // promote keeping signedness
    return static_cast<detail_::promoted_t<E>>(val);
}
#ifdef __cpp_concepts
template<a_safeint E>
#else
template <typename E>
#endif
constexpr auto
to_underlying(E val) noexcept
#ifndef __cpp_concepts
-> std::enable_if_t<detail_::is_safeint_v<E>,std::underlying_type_t<E>>
#endif
{ // plain value with all bad properties
    return static_cast<std::underlying_type_t<E>>(val);
}

#ifdef __cpp_concepts
template<a_safeint E>
#else
template <typename E>
#endif
constexpr auto
to_uint(E val) noexcept
{ // promote to unsigned for wrap around arithmetic
    using u_result_t = std::make_unsigned_t<detail_::promoted_t<E>>;
    using s_result_t = std::make_signed_t<u_result_t>;
    return static_cast<u_result_t>(static_cast<s_result_t>(to_int(val)));
}


// deliberately not std::integral, because of bool!

#ifdef __cpp_concepts
template<typename T>
concept an_integer = detail_::is_known_integer_v<T>;
#endif

#ifdef __cpp_concepts
template<an_integer T>
#else
template<typename T, std::enable_if_t<detail_::is_known_integer_v<T>,bool> = false >
#endif
constexpr auto
from_int(T val) {
    using detail_::is_similar_v;
    using std::conditional_t;
    struct cannot_convert_integer{};
    using result_t =
            conditional_t<is_similar_v<std::uint8_t,T>, ui8,
             conditional_t<is_similar_v<std::uint16_t,T>, ui16,
              conditional_t<is_similar_v<std::uint32_t,T>, ui32,
               conditional_t<is_similar_v<std::uint64_t,T>, ui64,
                conditional_t<is_similar_v<std::int8_t,T>, si8,
                 conditional_t<is_similar_v<std::int16_t,T>, si16,
                  conditional_t<is_similar_v<std::int32_t,T>, si32,
                   conditional_t<is_similar_v<std::int64_t,T>, si64, cannot_convert_integer>>>>>>>>;
    return static_cast<result_t>(val);
}
#ifdef __cpp_concepts
template<a_safeint TO, an_integer FROM>
#else
template<typename TO, typename FROM,
std::enable_if_t<detail_::is_safeint_v<TO>,bool> = false
>
#endif
constexpr
auto
from_int_to(FROM val)
#ifdef __cpp_concepts
-> TO
#else
-> std::enable_if_t<detail_::is_known_integer_v<FROM>,TO>
#endif
{
    using result_t = TO;
    using ultr = std::underlying_type_t<result_t>;
    if constexpr(std::is_unsigned_v<ultr>){
        if (val <= std::numeric_limits<ultr>::max()) {
            return static_cast<result_t>(val);
        } else {
            throw "integral constant too large";
        }
    } else {
        if (val <= std::numeric_limits<ultr>::max() &&
            val >= std::numeric_limits<ultr>::min()) {
            return static_cast<result_t>(val);
        } else {
            throw "integral constant out of range";
        }
    }

}


// comparison
// not needed, we won't mix types in comparison.

//template<a_safeint E>
//constexpr auto
//operator<=>(E l, E r) noexcept
//{
//	return l <=> r;
//}


// negation for signed types only, two's complement

#ifdef __cpp_concepts
template<a_safeint E>
#else
template<typename E,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && std::numeric_limits<E>::is_signed
,bool> = true>
#endif
constexpr E
operator-(E l) noexcept
#ifdef __cpp_concepts
requires std::numeric_limits<E>::is_signed
#endif
{
    return static_cast<E>(1u + ~to_uint(l));
}

// increment/decrement

#ifdef __cpp_concepts
template<a_safeint E>
#else
template<typename E, std::enable_if_t<detail_::is_safeint_v<E>,bool> = true>
#endif
constexpr E&
operator++(E& l) noexcept
{
    return l = static_cast<E>(1u + to_uint(l));
}

#ifdef __cpp_concepts
template<a_safeint E>
#else
template<typename E, std::enable_if_t<detail_::is_safeint_v<E>,bool> = true>
#endif
constexpr E
operator++(E& l, int) noexcept
{
    auto result=l;
    ++l;
    return result;
}
#ifdef __cpp_concepts
template<a_safeint E>
#else
template<typename E, std::enable_if_t<detail_::is_safeint_v<E>,bool> = true>
#endif
constexpr E&
operator--(E& l) noexcept {
    return l = static_cast<E>(to_uint(l) - 1u);
}

#ifdef __cpp_concepts
template<a_safeint E>
#else
template<typename E, std::enable_if_t<detail_::is_safeint_v<E>,bool> = true>
#endif
constexpr E
operator--(E& l, int) noexcept {
    auto result=l;
    --l;
    return result;
}



// arithmetic



#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && detail_::same_signedness_v<E,F>
,bool> = true>
#endif
constexpr auto
operator+(E l, F r) noexcept
#if __cpp_concepts
requires same_signedness<E,F>
#endif
{
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(
            static_cast<detail_::ULT<result_t>>(
                    to_uint(l)
                    + // use unsigned op to prevent signed overflow, but wrap.
                    to_uint(r)
            )
    );
}


#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && detail_::same_signedness_v<E,F>
,bool> = true>
#endif
constexpr auto&
operator+=(E &l, F r) noexcept
#ifdef __cpp_concepts
requires same_signedness<E,F>
#endif
{
    static_assert(sizeof(E) >= sizeof(F),"adding too large integer type");
    l = static_cast<E>(l+r);
    return l;
}

#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && detail_::same_signedness_v<E,F>
,bool> = true>
#endif
constexpr auto
operator-(E l, F r) noexcept
#ifdef __cpp_concepts
requires same_signedness<E,F>
#endif
{
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(
            static_cast<detail_::ULT<result_t>>(
                    to_uint(l)
                    - // use unsigned op to prevent signed overflow, but wrap.
                    to_uint(r)
            )
    );
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && detail_::same_signedness_v<E,F>
,bool> = true>
#endif
constexpr auto&
operator-=(E &l, F r) noexcept
#ifdef __cpp_concepts
requires same_signedness<E,F>
#endif
{
    static_assert(sizeof(E) >= sizeof(F),"subtracting too large integer type");
    l = static_cast<E>(l-r);
    return l;
}


#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && detail_::same_signedness_v<E,F>
,bool> = true>
#endif
constexpr auto
operator*(E l, F r) noexcept
#ifdef __cpp_concepts
requires same_signedness<E,F>
#endif
{
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(
            static_cast<detail_::ULT<result_t>>(
                    to_uint(l)
                    * // use unsigned op to prevent signed overflow, but wrap.
                    to_uint(r)
            )
    );
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && detail_::same_signedness_v<E,F>
,bool> = true>
#endif
constexpr auto&
operator*=(E &l, F r) noexcept
#ifdef __cpp_concepts
requires same_signedness<E,F>
#endif
{
    static_assert(sizeof(E) >= sizeof(F),"multiplying too large integer type");
    l = static_cast<E>(l*r);
    return l;
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && detail_::same_signedness_v<E,F>
,bool> = true>
#endif
constexpr auto
operator/(E l, F r) NOEXCEPT_WITH_THROWING_ASSERTS
#ifdef __cpp_concepts
requires same_signedness<E,F>
#endif
{
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
#pragma GCC diagnostic push
#if defined(__GNUG__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wterminate"
#endif
    ps_assert(result_t{}, r != F{} && " division by zero");
#pragma GCC diagnostic pop
    return static_cast<result_t>(
            static_cast<detail_::ULT<result_t>>(
                    to_uint(l)
                    / // use unsigned op to prevent signed overflow, but wrap.
                    to_uint(r)
            )
    );
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && detail_::same_signedness_v<E,F>
,bool> = true>
#endif
constexpr auto&
operator/=(E &l, F r) noexcept
#ifdef __cpp_concepts
requires same_signedness<E,F>
#endif
{
    static_assert(sizeof(E) >= sizeof(F),"dividing by too large integer type");
    l = static_cast<E>(l/r);
    return l;
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && detail_::same_signedness_v<E,F>
  && std::is_unsigned_v<detail_::ULT<E>>
,bool> = true>
#endif
constexpr auto
operator%(E l, F r) NOEXCEPT_WITH_THROWING_ASSERTS
#ifdef __cpp_concepts
requires same_signedness<E,F> && std::is_unsigned_v<detail_::ULT<E>>
#endif
{
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
#pragma GCC diagnostic push
#if defined(__GNUG__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wterminate"
#endif
    ps_assert(result_t{}, r != F{} && " division by zero");
#pragma GCC diagnostic pop
    return static_cast<result_t>(
            static_cast<detail_::ULT<result_t>>(
                    to_uint(l)
                    % // use unsigned op to prevent signed overflow, but wrap.
                    to_uint(r)
            )
    );
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && detail_::same_signedness_v<E,F>
  && std::is_unsigned_v<detail_::ULT<E>>
,bool> = true>
#endif
constexpr auto&
operator%=(E &l, F r) noexcept
#ifdef __cpp_concepts
requires same_signedness<E,F> && std::is_unsigned_v<detail_::ULT<E>>
#endif
{
    static_assert(sizeof(E) >= sizeof(F),"dividing by too large integer type");
    l = static_cast<E>(l%r);
    return l;
}

// bitwise operators

#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && std::is_unsigned_v<detail_::ULT<E>>
  && std::is_unsigned_v<detail_::ULT<F>>
  ,bool> = true>
#endif
constexpr auto
operator&(E l, F r) noexcept
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(to_int(l)&to_int(r));
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && std::is_unsigned_v<detail_::ULT<E>>
  && std::is_unsigned_v<detail_::ULT<F>>
  ,bool> = true>
#endif
constexpr auto&
operator&=(E &l, F r) noexcept
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
    static_assert(sizeof(E) == sizeof(F),"bitand by different sized integer type");
    l = static_cast<E>(l&r);
    return l;
}

#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && std::is_unsigned_v<detail_::ULT<E>>
  && std::is_unsigned_v<detail_::ULT<F>>
  ,bool> = true>
#endif
constexpr auto
operator|(E l, F r) noexcept
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(to_int(l)|to_int(r));
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && std::is_unsigned_v<detail_::ULT<E>>
  && std::is_unsigned_v<detail_::ULT<F>>
  ,bool> = true>
#endif
constexpr auto&
operator|=(E &l, F r) noexcept
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
    static_assert(sizeof(E) == sizeof(F),"bitor by different sized integer type");
    l = static_cast<E>(l|r);
    return l;
}

#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && std::is_unsigned_v<detail_::ULT<E>>
  && std::is_unsigned_v<detail_::ULT<F>>
  ,bool> = true>
#endif
constexpr auto
operator^(E l, F r) noexcept
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(to_int(l)^to_int(r));
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && std::is_unsigned_v<detail_::ULT<E>>
  && std::is_unsigned_v<detail_::ULT<F>>
  ,bool> = true>
#endif
constexpr auto&
operator^=(E &l, F r) noexcept
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
    static_assert(sizeof(E) == sizeof(F),"xor by different sized integer type");
    l = static_cast<E>(l^r);
    return l;
}

#ifdef __cpp_concepts
template<a_safeint E>
#else
template<typename E,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && std::is_unsigned_v<detail_::ULT<E>>
,bool> = true>
#endif
constexpr E
operator~(E l) noexcept
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>>
#endif
{
    return static_cast<E>(~to_int(l));
}


#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && std::is_unsigned_v<detail_::ULT<E>>
  && std::is_unsigned_v<detail_::ULT<F>>
  ,bool> = true>
#endif
constexpr E
operator<<(E l, F r) NOEXCEPT_WITH_THROWING_ASSERTS
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
#pragma GCC diagnostic push
#if defined(__GNUG__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wterminate"
#endif
    ps_assert(E{},static_cast<size_t>(to_int(r)) < sizeof(E)*CHAR_BIT && "trying to shift by too many bits");
#pragma GCC diagnostic pop
    return static_cast<E>(to_int(l)<<to_int(r));
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && std::is_unsigned_v<detail_::ULT<E>>
  && std::is_unsigned_v<detail_::ULT<F>>
  ,bool> = true>
#endif
constexpr auto&
operator<<=(E &l, F r) noexcept
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
    l = (l<<r);
    return l;
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && std::is_unsigned_v<detail_::ULT<E>>
  && std::is_unsigned_v<detail_::ULT<F>>
  ,bool> = true>
#endif
constexpr E
operator>>(E l, F r) NOEXCEPT_WITH_THROWING_ASSERTS
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
#pragma GCC diagnostic push
#if defined(__GNUG__) && !defined(__clang__)
#pragma GCC diagnostic ignored "-Wterminate"
#endif
    ps_assert(E{},static_cast<size_t>(to_int(r)) < sizeof(E)*CHAR_BIT && "trying to shift by too many bits");
#pragma GCC diagnostic pop
    return static_cast<E>(to_int(l)>>to_int(r));
}
#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F,
std::enable_if_t<
  detail_::is_safeint_v<E>
  && detail_::is_safeint_v<F>
  && std::is_unsigned_v<detail_::ULT<E>>
  && std::is_unsigned_v<detail_::ULT<F>>
  ,bool> = true>
#endif
constexpr auto&
operator>>=(E &l, F r) noexcept
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
    l = (l>>r);
    return l;
}



#ifdef __cpp_concepts
template<a_safeint E>
#else
template<typename E,
std::enable_if_t<
  detail_::is_safeint_v<E>
,bool> = true>
#endif
std::ostream& operator<<(std::ostream &out, E value){
    out << to_int(value);
    return out;
}

}


#endif /* SRC_PSSSAFEINT_ */
