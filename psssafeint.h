#ifndef SRC_PSSAFEINT_
#define SRC_PSSAFEINT_

#include <cstdint>
#include <type_traits>
#include <cassert>
#include <iosfwd>
#include <limits>
#include <climits>
#ifdef __cpp_concepts
#include <concepts> // std::integral
#endif

namespace psssint { // Peter Sommerlad's simple safe integers

// unsigned 
enum class ui8: std::uint8_t{ tag_to_prevent_mixing_other_enums };
enum class ui16: std::uint16_t{ tag_to_prevent_mixing_other_enums };
enum class ui32: std::uint32_t{ tag_to_prevent_mixing_other_enums };
enum class ui64: std::uint64_t{ tag_to_prevent_mixing_other_enums };

inline namespace literals {

#ifndef __cpp_consteval
#define consteval constexpr
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
enum class si8: std::int8_t{ tag_to_prevent_mixing_other_enums };
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

template<typename E>
using ULT=std::conditional_t<std::is_enum_v<plain<E>>,std::underlying_type_t<plain<E>>,plain<E>>;

template<typename E>
using promoted_t = // will promote keeping signedness
        std::conditional_t<(sizeof(ULT<E>) < sizeof(int))
            , std::conditional_t<std::is_unsigned_v<ULT<E>>
                , unsigned
                , int >
            , ULT<E>>;



}


#ifdef __cpp_concepts
template<typename E>
concept a_safeint = detail_::is_safeint_v<E>;
#endif

namespace detail_{

#ifdef __cpp_concepts
template<a_safeint E, a_safeint F>
#else
template<typename E, typename F>
#endif
constexpr bool
same_signedness_v = detail_::is_safeint_v<E> && detail_::is_safeint_v<F> && std::is_unsigned_v<ULT<E>> == std::is_unsigned_v<ULT<F>>;

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
  && std::is_signed_v<detail_::ULT<E>>
,bool> = true>
#endif
constexpr E
operator-(E l) noexcept
#ifdef __cpp_concepts
requires std::is_signed_v<detail_::ULT<E>>
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
operator++(E& l) noexcept {
    return l = static_cast<E>(1u + to_uint(l));
}

#ifdef __cpp_concepts
template<a_safeint E>
#else
template<typename E, std::enable_if_t<detail_::is_safeint_v<E>,bool> = true>
#endif
constexpr E
operator++(E& l, int) noexcept {
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
operator/(E l, F r) noexcept
#ifdef __cpp_concepts
requires same_signedness<E,F>
#endif
{
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    assert(r != F{});
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
    assert(r != F{} && "division by zero");
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
operator%(E l, F r) noexcept
#ifdef __cpp_concepts
requires same_signedness<E,F> && std::is_unsigned_v<detail_::ULT<E>>
#endif
{
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    assert(r != F{});
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
    assert(r != F{} && "division by zero");
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
operator<<(E l, F r) noexcept
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
    assert(static_cast<size_t>(to_int(r)) < sizeof(E)*CHAR_BIT && "trying to shift by too many bits");
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
    l = static_cast<E>(l<<r);
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
operator>>(E l, F r) noexcept
#ifdef __cpp_concepts
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>>
#endif
{
    assert(static_cast<size_t>(to_int(r)) < sizeof(E)*CHAR_BIT && "trying to shift by too many bits");
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
    l = static_cast<E>(l>>r);
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
