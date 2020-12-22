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

#ifndef CUTE_TEST_H_
#define CUTE_TEST_H_

#include "cute_determine_library.h"
#include "cute_demangle.h"

// make plain functions as tests more 'cute':
namespace cute {

	struct test{
		void operator()()const{ theTest(); }
		std::string name()const{ return name_;}


		// (real) functor types can (almost) spell their name
		// but a name can also be given explicitely, e.g. for CUTE() macro
		// for simple test functions
		template <typename VoidFunctor>
		test(VoidFunctor const &t, std::string sname = demangle(typeid(VoidFunctor).name()))
		:name_(sname),theTest(t){}
		// separate overload to allow nicer C++11 initializers with {"name",lambda}
		template <typename VoidFunctor>
		test(std::string sname,VoidFunctor const &t)
		:name_(sname),theTest(t){}

	private:
		std::string name_;
		boost_or_tr1::function<void()> theTest;
	};

}

#define CUTE(name) cute::test((&name),(#name))

#endif /*CUTE_TEST_H_*/
