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

#ifndef CUTE_RELOPS_H_
#define CUTE_RELOPS_H_

#include "cute_base.h"
#include "cute_diff_values.h"
#include <functional>

namespace cute {

namespace cute_relops_detail{
	template <typename LeftValue, typename RightValue>
	std::string compare_values(LeftValue const &left
						, RightValue const & right){
		return cute::diff_values(left,right,"left","right");
	}
}
template <template<typename> class RELOP,typename TL, typename TR>
void assert_relop(TL const &left
		, TR const &right
		,std::string const &msg
		,char const *file
		,int line) {
	if (RELOP<TL>()(left,right)) return;
	throw test_failure(msg + cute_relops_detail::compare_values(left,right),file,line);
}

}
#define ASSERT_LESSM(msg,left,right) cute::assert_relop<std::less>((left),(right),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg),__FILE__,__LINE__)
#define ASSERT_LESS(left,right) ASSERT_LESSM(#left " < " #right, (left),(right))
#define ASSERT_LESS_EQUALM(msg,left,right) cute::assert_relop<std::less_equal>((left),(right),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg),__FILE__,__LINE__)
#define ASSERT_LESS_EQUAL(left,right) ASSERT_LESS_EQUALM(#left " <= " #right, (left),(right))
#define ASSERT_GREATERM(msg,left,right) cute::assert_relop<std::greater>((left),(right),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg),__FILE__,__LINE__)
#define ASSERT_GREATER(left,right) ASSERT_GREATERM(#left " > " #right, (left),(right))
#define ASSERT_GREATER_EQUALM(msg,left,right) cute::assert_relop<std::greater_equal>((left),(right),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg),__FILE__,__LINE__)
#define ASSERT_GREATER_EQUAL(left,right) ASSERT_GREATER_EQUALM(#left " >= " #right, (left),(right))
#define ASSERT_NOT_EQUAL_TOM(msg,left,right) cute::assert_relop<std::not_equal_to>((left),(right),\
		CUTE_FUNCNAME_PREFIX+cute::cute_to_string::backslashQuoteTabNewline(msg),__FILE__,__LINE__)
#define ASSERT_NOT_EQUAL_TO(left,right) ASSERT_NOT_EQUAL_TOM(#left " != " #right, (left),(right))

#endif /* CUTE_RELOPS_H_ */
