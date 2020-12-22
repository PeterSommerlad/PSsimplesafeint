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

#ifndef CUTE_COUNTING_LISTENER_H_
#define CUTE_COUNTING_LISTENER_H_
#include "cute_listener.h"
namespace cute{
	template <typename Listener=null_listener>
	struct counting_listener:Listener{
		counting_listener()
		:Listener()
		,numberOfTests(0),successfulTests(0),failedTests(0),errors(0),numberOfSuites(0),numberOfTestsInSuites(0){}

		counting_listener(Listener const &s)
		:Listener(s)
		,numberOfTests(0),successfulTests(0),failedTests(0),errors(0),numberOfSuites(0),numberOfTestsInSuites(0){}

		void begin(suite const &s,char const *info, size_t n_of_tests){
			++numberOfSuites;
			numberOfTestsInSuites+=n_of_tests;
			Listener::begin(s,info, n_of_tests);
		}
		void start(test const &t){
			++numberOfTests;
			Listener::start(t);
		}
		void success(test const &t,char const *msg){
			++successfulTests;
			Listener::success(t,msg);
		}
		void failure(test const &t,test_failure const &e){
			++failedTests;
			Listener::failure(t,e);
		}
		void error(test const &t,char const *what){
			++errors;
			Listener::error(t,what);
		}
		size_t numberOfTests;
		size_t successfulTests;
		size_t failedTests;
		size_t errors;
		size_t numberOfSuites;
		size_t numberOfTestsInSuites;

	};
}
#endif /*CUTE_COUNTING_LISTENER_H_*/
