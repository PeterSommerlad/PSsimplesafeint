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

#ifndef CUTE_DETERMINE_LIBRARY_H_
#define CUTE_DETERMINE_LIBRARY_H_
#include "cute_determine_version.h"
#if defined(USE_TR1)
#include <tr1/functional>
// bind already given by <functional> in cute_test.h from cute_suite.h
namespace boost_or_tr1 = std::tr1;
namespace cute {
	using namespace boost_or_tr1::placeholders;
}
#elif defined(USE_STD11)
#include <functional>
namespace boost_or_tr1 = std;
namespace cute {
	using namespace boost_or_tr1::placeholders;
}
#else
#include <boost/bind.hpp>
#include <boost/function.hpp>
namespace boost_or_tr1 = boost;
#endif

#endif /*CUTE_DETERMINE_LIBRARY_H_*/
