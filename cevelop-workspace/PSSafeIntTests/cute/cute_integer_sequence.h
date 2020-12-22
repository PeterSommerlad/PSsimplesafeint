/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2016-2018 Felix Morgner
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *********************************************************************************/

#ifndef CUTE_INTEGER_SEQUENCE_H_
#define CUTE_INTEGER_SEQUENCE_H_

#include "cute_determine_version.h"

#ifdef USE_STD14
#include <utility>
namespace cute {
	using std::index_sequence;
	using std::index_sequence_for;
}
#else
#include <cstdint>
namespace cute {
	namespace do_not_use_this_namespace {
		template<typename IntType, IntType ...Ints>
		struct integer_sequence {
			using type = integer_sequence;
			using value_type = IntType;
			static constexpr std::size_t size() { return sizeof...(Ints); }
		};

		template<typename, typename, typename>
		struct flatten;

		template<typename IntType, IntType ...Lhs, IntType ...Rhs>
		struct flatten<IntType, integer_sequence<IntType, Lhs...>, integer_sequence<IntType, Rhs...>>
			: integer_sequence<IntType, Lhs..., (sizeof...(Lhs) + Rhs)...> {};

		template<typename IntType, std::size_t Last>
		struct make_integer_sequence;

		template<typename IntType>
		struct make_integer_sequence<IntType, 0>
			: integer_sequence<IntType>{};

		template<typename IntType>
		struct make_integer_sequence<IntType, 1>
			: integer_sequence<IntType, 0>{};

		template<typename IntType, std::size_t Last>
		struct make_integer_sequence
			: flatten<IntType, typename make_integer_sequence<IntType, Last / 2>::type,
			                   typename make_integer_sequence<IntType, Last - Last / 2>::type>::type {};

		template<std::size_t Last>
		using make_index_sequence = make_integer_sequence<std::size_t, Last>;
	}

	template<std::size_t ...Indices>
	using index_sequence = do_not_use_this_namespace::integer_sequence<std::size_t, Indices...>;

	template<typename ...Types>
	using index_sequence_for = do_not_use_this_namespace::make_index_sequence<sizeof...(Types)>;
}
#endif

#endif //CUTE_INTEGER_SEQUENCE_H_
