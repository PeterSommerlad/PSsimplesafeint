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

#ifndef OSTREAM_LISTENER_H_
#define OSTREAM_LISTENER_H_

#include "cute_listener.h"

#include <iostream>

namespace cute {
	// a "root" listener displaying output, use it as an example on how to build your own, e.g., for XML output
	template <typename Listener=null_listener>
	struct ostream_listener:Listener
	{
		std::ostream &out;
	public:
		ostream_listener(std::ostream &os=std::cerr):out(os) {}
		void begin(suite const &t,char const *info, size_t n_of_tests){
			out << "beginning: " << info << std::endl;
			Listener::begin(t,info, n_of_tests);
		}
		void end(suite const &t, char const *info){
			out << "ending: " << info << std::endl;
			Listener::end(t,info);
		}
		void start(test const &t){
			out << "starting: " << t.name() << std::endl;
			Listener::start(t);
		}
		void success(test const &t, char const *msg){
			out << t.name() << " " << msg << std::endl;
			Listener::success(t,msg);
		}
		void failure(test const &t,test_failure const &e){
			out << std::dec << e.filename << ":" << e.lineno << ": testcase failed: " << e.reason << " in " << t.name() << std::endl;
			Listener::failure(t,e);
		}
		void error(test const &t, char const *what){
			out << what << " in " << t.name() << std::endl;
			Listener::error(t,what);
		}
	};
}

#endif /*OSTREAM_LISTENER_H_*/
