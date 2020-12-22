/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2007-2018 Peter Sommerlad, Emanuel Graf, IFS
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

#ifndef CUTE_EQUALS_H_
#define CUTE_EQUALS_H_
#include "cute_base.h"
#include "cute_diff_values.h"
#include "cute_determine_traits.h"
#include "cute_determine_version.h"
#include "cute_deprecated.h"
#include "cute_range.h"
#include <cmath>
#include <limits>
#include <algorithm>
#ifdef USE_STD11
#include <tuple>
#endif


namespace cute {


	namespace cute_do_equals {
		// provide some template meta programming tricks to select "correct" comparison for floating point and integer types
		template <typename ExpectedValue, typename ActualValue, typename DeltaValue>
		bool do_equals_floating_with_delta(ExpectedValue const &expected
				,ActualValue const &actual
				,DeltaValue const &delta) {
			using std::abs; // allow for user-defined types with abs overload
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
			return bool(abs(delta) >= abs(expected-actual)); // Accommodate non-standard boolean type with explicit conversion
#pragma GCC diagnostic pop
		}
		template <typename ExpectedValue, typename ActualValue, bool select_non_floating_point_type>
		bool do_equals_floating(ExpectedValue const &expected
					,ActualValue const &actual,const impl_place_for_traits::integral_constant<bool, select_non_floating_point_type>&){
			return bool(expected==actual); // normal case for most types uses operator==!, accommodate non bool operator ==
		}
		template <typename ExpectedValue, typename ActualValue>
		bool do_equals_floating(ExpectedValue const &expected
					,ActualValue const &actual,const impl_place_for_traits::true_type&){
			const ExpectedValue automatic_delta_masking_last_significant_digit=(10*std::numeric_limits<ExpectedValue>::epsilon())*expected;
			return do_equals_floating_with_delta(expected,actual,automatic_delta_masking_last_significant_digit);
		}
		// TMP-overload dispatch for floating points 2 bool params --> 4 overloads
		template <typename ExpectedValue, typename ActualValue, bool select_non_integral_type>
		bool do_equals(ExpectedValue const &expected
					,ActualValue const &actual
					,const impl_place_for_traits::integral_constant<bool, select_non_integral_type>&/*exp_is_integral*/
					,const impl_place_for_traits::integral_constant<bool, select_non_integral_type>&/*act_is_integral*/){
			return do_equals_floating(expected,actual,impl_place_for_traits::is_floating_point<ExpectedValue>());
		}
		template <typename ExpectedValue, typename ActualValue, bool select_non_integral_type>
		bool do_equals(ExpectedValue const &expected
					,ActualValue const &actual
					,const impl_place_for_traits::false_type&,const impl_place_for_traits::false_type&){
			return do_equals_floating(expected,actual,impl_place_for_traits::is_floating_point<ActualValue>());
		}
		template <typename ExpectedValue, typename ActualValue, bool select_non_integral_type>
		bool do_equals(ExpectedValue const &expected
					,ActualValue const &actual
					,const impl_place_for_traits::integral_constant<bool, select_non_integral_type>&/*exp_is_integral*/
					,const impl_place_for_traits::true_type&){
			return do_equals_floating(expected,actual,impl_place_for_traits::is_floating_point<ExpectedValue>());
		}
		template <typename ExpectedValue, typename ActualValue, bool select_non_integral_type>
		bool do_equals(ExpectedValue const &expected
					,ActualValue const &actual
					,const impl_place_for_traits::true_type&,const impl_place_for_traits::integral_constant<bool, select_non_integral_type>&/*act_is_integral*/){
			return do_equals_floating(expected,actual,impl_place_for_traits::is_floating_point<ActualValue>());
		}
#ifdef USE_STD11
		template <bool select_non_floating_point_type, typename ...ExpectedTypes, typename ...ActualTypes>
		bool do_equals(std::tuple<ExpectedTypes...> const &expected
					,std::tuple<ActualTypes...> const &actual,const std::integral_constant<bool, select_non_floating_point_type>&){
					return expected==actual;
		}
#endif
		// can I get rid of the following complexity by doing a do_equals_integral
		// parameterized by is_signed<ExpectedValue>==is_signed<ActualValue> or nofBits<A> < nofBits<B>


		// this is an optimization for avoiding if and sign-extend overhead if both int types are the same as below
		template <typename IntType>
		bool do_equals(IntType const &expected
					,IntType const &actual
					,const impl_place_for_traits::true_type&,const impl_place_for_traits::true_type&){
			return expected==actual;
		}
		// bool cannot be made signed, therefore we need the following three overloads, also to avoid ambiguity
		template <typename IntType>
		bool do_equals(bool const &expected
					,IntType const &actual
					,const impl_place_for_traits::true_type&,const impl_place_for_traits::true_type&){
			return expected== !(!actual); // warning from VS
		}
		template <typename IntType>
		bool do_equals(IntType const &expected
					,bool const &actual
					,const impl_place_for_traits::true_type&,const impl_place_for_traits::true_type&){
			return !(!expected)==actual; // warning from VS
		}
		// do not forget the inline on a non-template overload!
		// this overload is needed to actually avoid ambiguity for comparing bool==bool as a best match
		inline bool do_equals(bool const &expected
				      ,bool const &actual
				      , const impl_place_for_traits::true_type&,const impl_place_for_traits::true_type&){
			return expected==actual;
		}
		// overload for char const *, my test case failed because VC++ doesn't use string constant folding like g++/clang
		// a feature where we should do string comparison
		inline bool do_equals(char const *const &expected
				      ,char const *const &actual
				      , const impl_place_for_traits::false_type&,const impl_place_for_traits::false_type&){
			return std::string(expected) == actual;
		}
		template <typename IntegralType>
		size_t nof_bits(IntegralType const &){
			return std::numeric_limits<IntegralType>::digits;
		}
#if defined(USE_STD11)||defined(USE_TR1)
		template <typename ExpectedValue, typename ActualValue>
		bool do_equals_integral(ExpectedValue const &expected
				,ActualValue const &actual
				,const impl_place_for_traits::true_type&,const impl_place_for_traits::true_type&){
			if (nof_bits(expected) < nof_bits(actual))
						return static_cast<ActualValue>(expected) == actual;
			else
						return expected == static_cast<ExpectedValue>(actual);
			return false;
		}
		template <typename ExpectedValue, typename ActualValue>
		bool do_equals_integral(ExpectedValue const &expected
				,ActualValue const &actual
				,const impl_place_for_traits::false_type&,const impl_place_for_traits::true_type&){
//TODO complicated case, one signed one unsigned type. since it is about equality casting to the longer should work?
			if (sizeof(ExpectedValue) >	sizeof(ActualValue))
				return expected==static_cast<ExpectedValue>(actual);
			else
				return static_cast<ActualValue>(expected) == actual;
		}
		template <typename ExpectedValue, typename ActualValue>
		bool do_equals_integral(ExpectedValue const &expected
				,ActualValue const &actual
				,const impl_place_for_traits::true_type&,const impl_place_for_traits::false_type&){
//TODO
			if (sizeof(ExpectedValue) < sizeof(ActualValue))
				return static_cast<ActualValue>(expected)==	actual;
			else
				return expected == static_cast<ExpectedValue>(actual);
		}
		template <typename ExpectedValue, typename ActualValue>
		bool do_equals_integral(ExpectedValue const &expected
				,ActualValue const &actual
				,const impl_place_for_traits::false_type&,const impl_place_for_traits::false_type&){
			if (nof_bits(expected) < nof_bits(actual))
						return static_cast<ActualValue>(expected) == actual;
			else
						return expected == static_cast<ExpectedValue>(actual);
			return false;
		}
#endif
		// will not work if either type is bool, therefore the overloads above.
		template <typename ExpectedValue, typename ActualValue>
		bool do_equals(ExpectedValue const &expected
					,ActualValue const &actual
					,const impl_place_for_traits::true_type&,const impl_place_for_traits::true_type&){
#if defined(USE_STD11) || defined(USE_TR1)
			return do_equals_integral(expected,actual,
					impl_place_for_traits::is_signed<ExpectedValue>()
					,impl_place_for_traits::is_signed<ActualValue>());
#else
//TODO: replace the following code with a dispatcher on signed/unsigned
			typedef typename impl_place_for_traits::make_signed<ExpectedValue>::type ex_s;
			typedef typename impl_place_for_traits::make_signed<ActualValue>::type ac_s;
				// need to sign extend with the longer type, should work...
			    // might be done through more template meta prog tricks....but...
				if (nof_bits(expected) < nof_bits(actual))
					return static_cast<ac_s>(expected) == static_cast<ac_s>(actual);
				else
					return static_cast<ex_s>(expected) == static_cast<ex_s>(actual);
#endif
		}
	} // namespace equals_impl
	template <typename ExpectedValue, typename ActualValue>
	void assert_equal(ExpectedValue const &expected
				,ActualValue const &actual
				,std::string const &msg
				,char const *file
				,int line) {
		// unfortunately there is no is_integral_but_not_bool_or_enum
		typedef typename impl_place_for_traits::is_integral<ExpectedValue> exp_integral;
		typedef typename impl_place_for_traits::is_integral<ActualValue> act_integral;
		if (cute_do_equals::do_equals(expected,actual,exp_integral(),act_integral()))
			return;
		throw test_failure(msg + diff_values(expected,actual),file,line);
	}

	template <typename ExpectedValue, typename ActualValue, typename DeltaValue>
	void assert_equal_delta(ExpectedValue const &expected
				,ActualValue const &actual
				,DeltaValue const &delta
				,std::string const &msg
				,char const *file
				,int line) {
		if (cute_do_equals::do_equals_floating_with_delta(expected,actual,delta)) return;
		throw test_failure(msg + diff_values(expected,actual),file,line);
	}

}

#define ASSERT_EQUALM(msg,expected,actual) cute::assert_equal((expected),(actual),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg),__FILE__,__LINE__)
#define ASSERT_EQUAL(expected,actual) ASSERT_EQUALM(#expected " == " #actual, (expected),(actual))
#define ASSERT_EQUAL_DELTAM(msg,expected,actual,delta) cute::assert_equal_delta((expected),(actual),(delta),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg),__FILE__,__LINE__)
#define ASSERT_EQUAL_DELTA(expected,actual,delta) ASSERT_EQUAL_DELTAM(#expected " == " #actual " with error " #delta  ,(expected),(actual),(delta))

DEPRECATE(ASSERT_EQUAL_RANGES_M, ASSERT_EQUAL_RANGESM)
#define ASSERT_EQUAL_RANGES_M(msg,expbeg,expend,actbeg,actend) DEPRECATED(ASSERT_EQUAL_RANGES_M), ASSERT_EQUALM(msg,cute::make_range(expbeg,expend),cute::make_range(actbeg,actend))
#define ASSERT_EQUAL_RANGESM(msg,expbeg,expend,actbeg,actend) ASSERT_EQUALM(msg,cute::make_range(expbeg,expend),cute::make_range(actbeg,actend))
#define ASSERT_EQUAL_RANGES(expbeg,expend,actbeg,actend) ASSERT_EQUAL_RANGESM("range{" #expbeg "," #expend "} == range{" #actbeg "," #actend "}",expbeg,expend,actbeg,actend)
#endif /*CUTE_EQUALS_H_*/
