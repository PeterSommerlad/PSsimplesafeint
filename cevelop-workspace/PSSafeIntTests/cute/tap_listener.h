/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2017-2018 Felix Morgner
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

#ifndef TAP_LISTENER_H_
#define TAP_LISTENER_H_

#include <cstdint>
#include <iostream>

#include "cute_listener.h"

namespace cute {

	template<typename Listener=null_listener>
	struct tap_listener : Listener {
		tap_listener(std::ostream & out = std::cout) : out(out),nofTests(0) { }

		~tap_listener() {
			if (nofTests) {
				out << "1.." << nofTests << '\n';
			}
		}

		void begin(suite const & suite, char const * info, size_t n_of_tests) {
			out << "# Starting suite '" << info << "' containing " << n_of_tests << " tests\n";
			Listener::begin(suite, info, n_of_tests);
		}

		void end(suite const & suite, char const * info) {
			out << "# Ending suite '" << info << "'\n";
			Listener::end(suite, info);
		}

		void start(test const & test) {
			++nofTests;
			Listener::start(test);
		}

		void success(test const & test, char const * msg) {
			out << "ok " << nofTests << ' ' << test.name() << '\n';
			Listener::success(test, msg);
		}

		void failure(test const & test, test_failure const & reason) {
			out << "not ok " << nofTests << ' ' << test.name() << '\n';
			out << "# Assertion failed: " << reason.what() << '\n';
			Listener::failure(test, reason);
		}

		void error(test const & test, char const * what) {
			out << "not ok " << nofTests << ' ' << test.name() << '\n';
			out << "# Unexpected exception: " << what << '\n';
			Listener::error(test, what);
		}

	private:
		std::ostream & out;
		std::size_t nofTests;
	};

}

#endif /* TAP_LISTENER_H_ */

