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

#ifndef CUTE_THROWS_H_
#define CUTE_THROWS_H_

#include "cute_base.h"

// should we allow arbitrary code and remove the parentheses around the macro expansion?
// not now, strange compilation side-effects might result.
namespace cute {
	namespace do_not_use_this_namespace {
		struct assert_throws_failure_exception {
			struct cute::test_failure original;
			assert_throws_failure_exception(std::string const &r,char const *f, int line):
					original(r,f, line){}
		};
	}
}

#define ASSERT_THROWSM(anuncommonmessagetextparametername,code,exc) \
	do { \
		try { \
			{ code ; } \
			throw cute::do_not_use_this_namespace::assert_throws_failure_exception((anuncommonmessagetextparametername),__FILE__,__LINE__); \
		} catch(exc const &){ \
		} catch(cute::do_not_use_this_namespace::assert_throws_failure_exception const &atf){throw atf.original;} \
	} while(0)
#define ASSERT_THROWS(code,exc) ASSERT_THROWSM(" expecting " #code " to throw " #exc,code,exc)

#endif /*CUTE_THROWS_H_*/
