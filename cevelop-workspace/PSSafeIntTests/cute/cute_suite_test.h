/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2006-2018 Peter Sommerlad, IFS
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

#ifndef CUTE_SUITE_TEST_H_
#define CUTE_SUITE_TEST_H_
#include "cute_suite.h"
#include "cute_determine_library.h"

#include <algorithm>
namespace cute{
	// make a whole suite a test, failure stops the suite's execution
	struct suite_test {
		suite theSuite;
		suite_test(suite const &s):theSuite(s){}
		void operator()(){
			std::for_each(theSuite.begin(),theSuite.end(),boost_or_tr1::bind(&test::operator(),_1));
		}
	};
}
#define CUTE_SUITE_TEST(s) cute::test(cute::suite_test((s)),#s)
#define CUTE_SUITE_TEST_NAME(s, name) cute::test(cute::suite_test((s)),name)
#endif /*CUTE_SUITE_TEST_H_*/
