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

#ifndef CUTE_TEST_INCARNATE_H_
#define CUTE_TEST_INCARNATE_H_

#include "cute_test.h"

// idea blatantly stolen from Aeryn
namespace cute {
	template <typename TestFunctor>
	struct test_incarnate {
		void operator()(){
			TestFunctor()();
		}
	};
	// TODO: check if there are problems with references.
	template <typename TestFunctor, typename ContextObject>
	struct test_incarnate_with_context {
		test_incarnate_with_context(ContextObject context):theContext(context)
		{}
		test_incarnate_with_context(test_incarnate_with_context const &other):theContext(other.theContext){} // provide copy-ctor in case compiler will define it deleted
		void operator()(){
			TestFunctor t(theContext);// wouldn't create temporary to call with ()()
			t();
		}
		ContextObject theContext;
	};
	template <typename TestFunctor,typename ContextObject>
	test make_incarnate_with_context(ContextObject obj){
		return test(test_incarnate_with_context<TestFunctor,ContextObject>(obj),demangle(typeid(TestFunctor).name()));
	}
}

#define CUTE_INCARNATE(TestFunctor) cute::test(cute::test_incarnate<TestFunctor>(),cute::demangle(typeid(TestFunctor).name()))
#define CUTE_INCARNATE_WITH_CONTEXT(TestFunctor,contextObject) cute::make_incarnate_with_context<TestFunctor>(contextObject)

#endif /*CUTE_TEST_INCARNATE_H_*/
