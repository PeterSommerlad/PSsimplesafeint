/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2007-2018 Peter Sommerlad, IFS
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

#ifndef CUTE_BASE_H_
#define CUTE_BASE_H_

#include "cute_to_string.h"
#include "cute_determine_version.h"

#include <string>

namespace cute {
	struct test_failure {
		std::string reason;
		std::string filename;
		int lineno;

		test_failure(std::string const &r,char const *f, int line)
		:reason(r),filename(f),lineno(line)
		{ 	}
		char const * what() const { return reason.c_str(); }
	};
}

#if defined(USE_STD11) && !defined(_MSC_VER)
#define CUTE_FUNCNAME_PREFIX std::string(__func__)+": "
#else
#if defined( _MSC_VER ) || defined(__GNUG__)
//#if defined(USE_STD11)
//#define CUTE_FUNCNAME_PREFIX
// workaround doesn't work namespace { char const __FUNCTION__ []="lambda";}
// MSC can not use lambdas outside of function bodies for tests.
//#endif
// use -D CUTE_FUNCNAME_PREFIX if you want to use non-local lambdas with test macros
#if !defined(CUTE_FUNCNAME_PREFIX)
#define CUTE_FUNCNAME_PREFIX std::string(__FUNCTION__)+": "
#endif
#else // could provide #defines for other compiler-specific extensions... need to experiment, i.e., MS uses __FUNCTION__
#define CUTE_FUNCNAME_PREFIX std::string("")
#endif
#endif
#define ASSERTM(msg,cond) do { if (!(cond)) throw cute::test_failure(CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg),__FILE__,__LINE__);} while(false)
#define ASSERT(cond) ASSERTM(#cond,cond)
#define FAIL() ASSERTM("FAIL()",false)
#define FAILM(msg) ASSERTM(msg,false)
#endif /*CUTE_BASE_H_*/
