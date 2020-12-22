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

#ifndef CUTE_DIFF_VALUES_H_
#define CUTE_DIFF_VALUES_H_
#include "cute_to_string.h"
namespace cute {
	// you could provide your own overload for diff_values for your app-specific types
	// be sure to use tabs as given below, then the CUTE eclipse plug-in will parse correctly
	template <typename ExpectedValue, typename ActualValue>
	std::string diff_values(ExpectedValue const &expected
						, ActualValue const & actual
						, char const *left="expected"
						, char const *right="but was"){
		// construct a simple message...to be parsed by IDE support
		std::string res;
		res += ' ';
		res += left;
		res+=":\t" + cute_to_string::backslashQuoteTabNewline(cute_to_string::to_string(expected))+'\t';
		res += right;
		res +=":\t"+cute_to_string::backslashQuoteTabNewline(cute_to_string::to_string(actual))+'\t';
		return res;
	}
}

#endif /* CUTE_DIFF_VALUES_H_ */
