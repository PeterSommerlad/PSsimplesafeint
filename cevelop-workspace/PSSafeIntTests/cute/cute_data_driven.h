/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2013-2018 Peter Sommerlad, IFS
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

#ifndef CUTE_DATA_DRIVEN_H_
#define CUTE_DATA_DRIVEN_H_

#include "cute_base.h"
#include "cute_equals.h"
#include "cute_relops.h"

#define DDTM(msg) (cute::test_failure(cute::cute_to_string::backslashQuoteTabNewline(msg),__FILE__,__LINE__))
#define DDT() DDTM("")

#define ASSERT_DDTM(cond,msg,failure) do{ \
	if (!(cond)) \
		throw cute::test_failure(CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg)+(failure).reason,\
				(failure).filename.c_str(),(failure).lineno);\
} while (false)
#define ASSERT_DDT(cond,failure) ASSERT_DDTM(cond,#cond,(failure))

#define ASSERT_EQUAL_DDTM(msg,expected,actual,failure) cute::assert_equal((expected),(actual),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg)\
		+(failure).reason,(failure).filename.c_str(),(failure).lineno)
#define ASSERT_EQUAL_DDT(expected,actual,failure) ASSERT_EQUAL_DDTM(#expected " == " #actual, (expected),(actual),(failure))
#define ASSERT_EQUAL_DELTA_DDTM(msg,expected,actual,delta,failure) cute::assert_equal_delta((expected),(actual),(delta),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg)\
		+(failure).reason,(failure).filename.c_str(),(failure).lineno)
#define ASSERT_EQUAL_DELTA_DDT(expected,actual,delta,failure) ASSERT_EQUAL_DELTA_DDTM(#expected " == " #actual " with error " #delta  ,(expected),(actual),(delta),(failure))

#define ASSERT_LESS_DDTM(msg,left,right,failure) cute::assert_relop<std::less>((left),(right),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg)\
		+(failure).reason,(failure).filename.c_str(),(failure).lineno)
#define ASSERT_LESS_DDT(left,right,failure) ASSERT_LESS_DDTM(#left " < " #right, (left),(right),(failure))

#define ASSERT_LESS_EQUAL_DDTM(msg,left,right,failure) cute::assert_relop<std::less_equal>((left),(right),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg)\
		+(failure).reason,(failure).filename.c_str(),(failure).lineno)
#define ASSERT_LESS_EQUAL_DDT(left,right,failure) ASSERT_LESS_EQUAL_DDTM(#left " <= " #right, (left),(right),(failure))

#define ASSERT_GREATER_DDTM(msg,left,right,failure) cute::assert_relop<std::greater>((left),(right),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg)\
		+(failure).reason,(failure).filename.c_str(),(failure).lineno)
#define ASSERT_GREATER_DDT(left,right,failure) ASSERT_GREATER_DDTM(#left " > " #right, (left),(right),(failure))

#define ASSERT_GREATER_EQUAL_DDTM(msg,left,right,failure) cute::assert_relop<std::greater_equal>((left),(right),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg)\
		+(failure).reason,(failure).filename.c_str(),(failure).lineno)
#define ASSERT_GREATER_EQUAL_DDT(left,right,failure) ASSERT_GREATER_EQUAL_DDTM(#left " >= " #right, (left),(right),(failure))

#define ASSERT_NOT_EQUAL_TO_DDTM(msg,left,right,failure) cute::assert_relop<std::not_equal_to>((left),(right),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg)\
		+(failure).reason,(failure).filename.c_str(),(failure).lineno)
#define ASSERT_NOT_EQUAL_TO_DDT(left,right,failure) ASSERT_NOT_EQUAL_TO_DDTM(#left " != " #right, (left),(right),(failure))



#endif /* CUTE_DATA_DRIVEN_H_ */
