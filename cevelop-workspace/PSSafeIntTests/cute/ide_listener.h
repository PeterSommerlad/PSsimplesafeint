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

#ifndef IDE_LISTENER_H_
#define IDE_LISTENER_H_

#include "cute_listener.h"

#include <iostream>
#include <algorithm>
#ifdef _MSC_VER
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <sstream>
#endif

namespace cute {
	template <typename Listener=null_listener>
	struct ide_listener: Listener
	{
		ide_listener(std::ostream &os=std::cout):out(os) {}
		void begin(suite const &t,char const *info, size_t n_of_tests){
			out << std::dec << "\n#beginning " << info << " " << n_of_tests << '\n' << std::flush;
			Listener::begin(t,info,n_of_tests);
		}
		void end(suite const &t, char const *info){
			out << "\n#ending " << info << '\n' << std::flush;
			Listener::end(t,info);
		}
		void start(test const &t){
			out << "\n#starting " << t.name() << '\n' << std::flush;
			Listener::start(t);
		}
		void success(test const &t, char const *msg){
			out << "\n#success " <<  maskBlanks(t.name()) << " " << msg << '\n' << std::flush;
			Listener::success(t,msg);
		}
		void failure(test const &t,test_failure const &e){
			out << std::dec <<  "\n#failure " << maskBlanks(t.name()) << " " << e.filename << ":" << e.lineno << " " << (e.reason) << '\n' << std::flush;
			Listener::failure(t,e);
#ifdef _MSC_VER
			std::ostringstream os;
			os << std::dec << e.filename << "(" << e.lineno << ") : failure: " <<e.reason << " in " << t.name() << '\n' << std::flush;
			OutputDebugString(os.str().c_str());
#endif
		}
		void error(test const &t, char const *what){
			out << "\n#error " << maskBlanks(t.name()) << " " << what << '\n' << std::flush;
			Listener::error(t,what);
#ifdef _MSC_VER
			std::ostringstream os;
			os << what << " error in " << t.name() << '\n' << std::flush;
			OutputDebugString(os.str().c_str());
#endif
		}
		static std::string maskBlanks(std::string in) {
			std::transform(in.begin(),in.end(),in.begin(),blankToUnderscore());
			return in;
		}
	protected:
		struct blankToUnderscore{
            char operator()(char in) const {
			if (in == ' ') return '_';
			return in;
		}
        };
		std::ostream &out;
	};
}

#endif /*IDE_LISTENER_H_*/
