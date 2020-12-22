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

#ifndef CUTE_TESTMEMBER_H_
#define CUTE_TESTMEMBER_H_

#include "cute_test.h"

namespace cute {
	template <typename TestClass>
	test makeMemberFunctionTest(TestClass &t,void (TestClass::*fun)(),char const *name){
		return test(boost_or_tr1::bind(fun,boost_or_tr1::ref(t)),demangle(typeid(TestClass).name())+"::"+name);
	}
	template <typename TestClass>
	test makeMemberFunctionTest(TestClass const &t,void (TestClass::*fun)()const,char const *name){
		return test(boost_or_tr1::bind(fun,boost_or_tr1::cref(t)),demangle(typeid(TestClass).name())+"::"+name);
	}
	template <typename TestClass,typename MemFun>
	struct incarnate_for_member_function {
		MemFun memfun;
		incarnate_for_member_function(MemFun f):memfun(f){}
		void operator()(){
			TestClass t;
			(t.*memfun)();
		}
	};
	template <typename TestClass, typename MemFun>
	test makeSimpleMemberFunctionTest(MemFun fun,char const *name){
		return test(incarnate_for_member_function<TestClass,MemFun>(fun),demangle(typeid(TestClass).name())+"::"+name);
	}
	template <typename TestClass,typename MemFun, typename Context>
	struct incarnate_for_member_function_with_context_object {
		MemFun memfun;
		Context context;
		incarnate_for_member_function_with_context_object(MemFun f,Context c)
		:memfun(f),context(c){}
		incarnate_for_member_function_with_context_object(incarnate_for_member_function_with_context_object const &other)
		:memfun(other.memfun),context(other.context){} // provide copy-ctor for std::function ctor requirement should be =default on C++11

		void operator()(){
			TestClass t(context);
			(t.*memfun)();
		}
	};
	template <typename TestClass, typename MemFun, typename Context>
	test makeMemberFunctionTestWithContext(Context c,MemFun fun,char const *name){
		return test(incarnate_for_member_function_with_context_object<TestClass,MemFun,Context>(fun,c),demangle(typeid(TestClass).name())+"::"+name);
	}
}

#define CUTE_MEMFUN(testobject,TestClass,MemberFunctionName) \
	cute::makeMemberFunctionTest(testobject,\
		&TestClass::MemberFunctionName,\
		#MemberFunctionName)
#define CUTE_SMEMFUN(TestClass,MemberFunctionName) \
	cute::makeSimpleMemberFunctionTest<TestClass>(\
		&TestClass::MemberFunctionName,\
		#MemberFunctionName)
#define CUTE_CONTEXT_MEMFUN(context_object,TestClass,MemberFunctionName) \
	cute::makeMemberFunctionTestWithContext<TestClass>(\
		context_object,\
		&TestClass::MemberFunctionName,\
		#MemberFunctionName)

#endif /*CUTE_TESTMEMBER_H_*/
