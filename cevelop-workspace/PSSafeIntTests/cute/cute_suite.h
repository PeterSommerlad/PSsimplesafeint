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

#ifndef CUTE_SUITE_H_
#define CUTE_SUITE_H_

#include "cute_test.h"

#include <vector>

namespace cute {
	typedef std::vector<test> suite;
	// convenience operator for appending to suites, might not be right
	// deprecated, not supported by plug-in, not needed with Eclipse plug-in
	inline
	suite &operator+=(suite &left, suite const &right){
		left.insert(left.end(),right.begin(),right.end());
		return left;
	}
	inline
	suite &operator+=(suite &left, test const &right){
		left.push_back(right);
		return left;
	}
}

#endif /*CUTE_SUITE_H_*/
