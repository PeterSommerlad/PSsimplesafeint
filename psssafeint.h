#ifndef SRC_PSSAFEINT_
#define SRC_PSSAFEINT_

#include <cstdint>
#include <type_traits>
#include <cassert>
#include <iosfwd>
#include <limits>
#include <climits>
#include <concepts> // std::integral

namespace psssint { // Peter Sommerlad's simple safe integers

// unsigned 
enum class ui8: std::uint8_t{ tag_to_prevent_mixing_other_enums };
enum class ui16: std::uint16_t{ tag_to_prevent_mixing_other_enums };
enum class ui32: std::uint32_t{ tag_to_prevent_mixing_other_enums };
enum class ui64: std::uint64_t{ tag_to_prevent_mixing_other_enums };

inline namespace literals {
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
}




template<typename T>
using plain = std::remove_cvref_t<T>;

template<typename T>
concept an_enum = std::is_enum_v<plain<T>>;


namespace detail_ {
// from C++23
template<an_enum T>
//template<typename T, auto = std::enable_if_t<std::is_enum_v<plain<T>>,void*>{nullptr}>
constexpr bool
is_scoped_enum_v = !std::is_convertible_v<T, std::underlying_type_t<T>>;

template<typename T>
concept a_scoped_enum = is_scoped_enum_v<T>;


// detection concept

template<typename T>
constexpr bool
is_safeint_v = false;

template<a_scoped_enum E>
constexpr bool
is_safeint_v<E> = requires { E{} == E::tag_to_prevent_mixing_other_enums; } ;

template<typename E>
using ULT=std::conditional_t<std::is_enum_v<plain<E>>,std::underlying_type_t<plain<E>>,plain<E>>;

template<typename E>
using promoted_t = // will promote keeping signedness
        std::conditional_t<(sizeof(ULT<E>) < sizeof(int))
            , std::conditional_t<std::is_unsigned_v<ULT<E>>
                , unsigned
                , int >
            , ULT<E>>;


template<std::integral T>
constexpr bool
is_known_integer_v =    std::is_same_v<uint8_t, T> ||
                        std::is_same_v<uint16_t, T> ||
                        std::is_same_v<uint32_t, T> ||
                        std::is_same_v<uint64_t, T> ||
                        std::is_same_v<int8_t, T> ||
                        std::is_same_v<int16_t, T> ||
                        std::is_same_v<int32_t, T> ||
                        std::is_same_v<int64_t, T>;


}


template<typename E>
concept a_safeint = detail_::is_safeint_v<E>;


namespace detail_{

template<a_safeint E, a_safeint F>
constexpr bool
same_sign_v = std::is_unsigned_v<ULT<E>> == std::is_unsigned_v<ULT<F>>;

}



template<typename E, typename F>
concept same_sign = detail_::same_sign_v<E,F>;

template<a_safeint E>
constexpr auto
to_int(E val) noexcept { // promote keeping signedness
    return static_cast<detail_::promoted_t<E>>(val);
}
template<a_safeint E>
constexpr auto
to_underlying(E val) noexcept { // plain value with all bad properties
    return static_cast<std::underlying_type_t<E>>(val);
}

template<a_safeint E>
constexpr auto
to_uint(E val) noexcept { // promote to unsigned for wrap around arithmetic
    using u_result_t = std::make_unsigned_t<detail_::promoted_t<E>>;
    using s_result_t = std::make_signed_t<u_result_t>;
    return static_cast<u_result_t>(static_cast<s_result_t>(to_int(val)));
}


// deliberately not std::integral, because of bool!

template<typename T>
concept an_integer = detail_::is_known_integer_v<T>;


template<an_integer T>
constexpr auto
from_int(T val) {
    using std::is_same_v;
    using std::conditional_t;
    struct cannot_convert_integer{};
    using result_t =
            conditional_t<is_same_v<uint8_t,T>, ui8,
             conditional_t<is_same_v<uint16_t,T>, ui16,
              conditional_t<is_same_v<uint32_t,T>, ui32,
               conditional_t<is_same_v<uint64_t,T>, ui64,
                conditional_t<is_same_v<int8_t,T>, si8,
                 conditional_t<is_same_v<int16_t,T>, si16,
                  conditional_t<is_same_v<int32_t,T>, si32,
                   conditional_t<is_same_v<int64_t,T>, si64, cannot_convert_integer>>>>>>>>;
    return static_cast<result_t>(val);
}
template<a_safeint TO, an_integer FROM>
constexpr TO
from_int_to(FROM val) {
    using std::is_same_v;
    using std::conditional_t;
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


template<a_safeint E>
constexpr E
operator-(E l) noexcept
requires std::is_signed_v<detail_::ULT<E>> {
    return static_cast<E>(1u + ~to_uint(l));
}

// increment/decrement

template<a_safeint E>
constexpr E&
operator++(E& l) noexcept {
    return l = static_cast<E>(1u + to_uint(l));
}

template<a_safeint E>
constexpr E
operator++(E& l, int) noexcept {
    auto result=l;
    ++l;
    return result;
}
template<a_safeint E>
constexpr E&
operator--(E& l) noexcept {
    return l = static_cast<E>(to_uint(l) - 1u);
}

template<a_safeint E>
constexpr E
operator--(E& l, int) noexcept {
    auto result=l;
    --l;
    return result;
}



// arithmetic



template<a_safeint E, a_safeint F>
constexpr auto
operator+(E l, F r) noexcept
requires same_sign<E,F> {
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(
            static_cast<detail_::ULT<result_t>>(
                    to_uint(l)
                    + // use unsigned op to prevent signed overflow, but wrap.
                    to_uint(r)
            )
    );
}


template<a_safeint E, a_safeint F>
constexpr auto&
operator+=(E &l, F r) noexcept
requires same_sign<E,F> {
    static_assert(sizeof(E) >= sizeof(F),"adding too large integer type");
    l = static_cast<E>(l+r);
    return l;
}

template<a_safeint E, a_safeint F>
constexpr auto
operator-(E l, F r) noexcept
requires same_sign<E,F> {
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(
            static_cast<detail_::ULT<result_t>>(
                    to_uint(l)
                    - // use unsigned op to prevent signed overflow, but wrap.
                    to_uint(r)
            )
    );
}
template<a_safeint E, a_safeint F>
constexpr auto&
operator-=(E &l, F r) noexcept
requires same_sign<E,F> {
    static_assert(sizeof(E) >= sizeof(F),"subtracting too large integer type");
    l = static_cast<E>(l-r);
    return l;
}


template<a_safeint E, a_safeint F>
constexpr auto
operator*(E l, F r) noexcept
requires same_sign<E,F> {
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(
            static_cast<detail_::ULT<result_t>>(
                    to_uint(l)
                    * // use unsigned op to prevent signed overflow, but wrap.
                    to_uint(r)
            )
    );
}
template<a_safeint E, a_safeint F>
constexpr auto&
operator*=(E &l, F r) noexcept
requires same_sign<E,F> {
    static_assert(sizeof(E) >= sizeof(F),"multiplying too large integer type");
    l = static_cast<E>(l*r);
    return l;
}
template<a_safeint E, a_safeint F>
constexpr auto
operator/(E l, F r) noexcept
requires same_sign<E,F> {
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
template<a_safeint E, a_safeint F>
constexpr auto&
operator/=(E &l, F r) noexcept
requires same_sign<E,F> {
    static_assert(sizeof(E) >= sizeof(F),"dividing by too large integer type");
    assert(r != F{} && "division by zero");
    l = static_cast<E>(l/r);
    return l;
}
template<a_safeint E, a_safeint F>
constexpr auto
operator%(E l, F r) noexcept
requires same_sign<E,F> && std::is_unsigned_v<detail_::ULT<E>> {
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
template<a_safeint E, a_safeint F>
constexpr auto&
operator%=(E &l, F r) noexcept
requires same_sign<E,F> && std::is_unsigned_v<detail_::ULT<E>> {
    static_assert(sizeof(E) >= sizeof(F),"dividing by too large integer type");
    assert(r != F{} && "division by zero");
    l = static_cast<E>(l%r);
    return l;
}

// bitwise operators

template<a_safeint E, a_safeint F>
constexpr auto
operator&(E l, F r) noexcept
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>> {
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(to_int(l)&to_int(r));
}
template<a_safeint E, a_safeint F>
constexpr auto&
operator&=(E &l, F r) noexcept
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>> {
    static_assert(sizeof(E) == sizeof(F),"bitand by different sized integer type");
    l = static_cast<E>(l&r);
    return l;
}

template<a_safeint E, a_safeint F>
constexpr auto
operator|(E l, F r) noexcept
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>> {
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(to_int(l)|to_int(r));
}
template<a_safeint E, a_safeint F>
constexpr auto&
operator|=(E &l, F r) noexcept
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>> {
    static_assert(sizeof(E) == sizeof(F),"bitor by different sized integer type");
    l = static_cast<E>(l|r);
    return l;
}

template<a_safeint E, a_safeint F>
constexpr auto
operator^(E l, F r) noexcept
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>> {
    using result_t=std::conditional_t<sizeof(E)>=sizeof(F),E,F>;
    return static_cast<result_t>(to_int(l)^to_int(r));
}
template<a_safeint E, a_safeint F>
constexpr auto&
operator^=(E &l, F r) noexcept
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>> {
    static_assert(sizeof(E) == sizeof(F),"xor by different sized integer type");
    l = static_cast<E>(l^r);
    return l;
}

template<a_safeint E>
constexpr E
operator~(E l) noexcept
requires std::is_unsigned_v<detail_::ULT<E>> {
    return static_cast<E>(~to_int(l));
}


template<a_safeint E, a_safeint F>
constexpr E
operator<<(E l, F r) noexcept
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>> {
    assert(static_cast<size_t>(to_int(r)) < sizeof(E)*CHAR_BIT && "trying to shift by too many bits");
    return static_cast<E>(to_int(l)<<to_int(r));
}
template<a_safeint E, a_safeint F>
constexpr auto&
operator<<=(E &l, F r) noexcept
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>> {
    l = static_cast<E>(l<<r);
    return l;
}
template<a_safeint E, a_safeint F>
constexpr E
operator>>(E l, F r) noexcept
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>> {
    assert(static_cast<size_t>(to_int(r)) < sizeof(E)*CHAR_BIT && "trying to shift by too many bits");
    return static_cast<E>(to_int(l)>>to_int(r));
}
template<a_safeint E, a_safeint F>
constexpr auto&
operator>>=(E &l, F r) noexcept
requires std::is_unsigned_v<detail_::ULT<E>> && std::is_unsigned_v<detail_::ULT<F>> {
    l = static_cast<E>(l>>r);
    return l;
}


std::ostream& operator<<(std::ostream &out, a_safeint auto value){
    out << to_int(value);
    return out;
}

}



#endif /* SRC_PSSSAFEINT_ */
