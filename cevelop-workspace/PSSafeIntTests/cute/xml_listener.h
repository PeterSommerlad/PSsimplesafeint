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

#ifndef XML_LISTENER_H_
#define XML_LISTENER_H_

#include "cute_listener.h"
#include "cute_xml_file.h" // for convenience

#include <ostream>

namespace cute {
	template <typename Listener=null_listener>
	class xml_listener:public Listener
	{
	protected:
		std::string mask_xml_chars(std::string in){
			std::string::size_type pos=0;
			while((pos=in.find_first_of("\x00\x01\x02\x03\x04\x05\x06\x07\x08\x0b\x0c\x0e\x0f\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\"&'<>", pos, 34))!=std::string::npos){
				switch(in[pos]){
				case '&': in.replace(pos,1,"&amp;"); pos +=5; break;
				case '<': in.replace(pos,1,"&lt;"); pos += 4; break;
				case '>': in.replace(pos,1,"&gt;"); pos += 4; break;
				case '"': in.replace(pos,1,"&quot;"); pos+=6; break;
				case '\'':in.replace(pos,1,"&apos;"); pos+=6; break;
				default:
					char c = in[pos];
					std::string replacement = "0x" + cute_to_string::hexit(c);
					in.replace(pos, 1, replacement); pos += replacement.size(); break;
					break;
				}
			}
			return in;
		}
		std::ostream &out;
		std::string current_suite;
	public:
		xml_listener(std::ostream &os):out(os) {
			out << "<testsuites>\n";
		}
		~xml_listener(){
			out << "</testsuites>\n"<< std::flush;
		}

		void begin(suite const &t,char const *info, size_t n_of_tests){
			current_suite=mask_xml_chars(info);
			out << std::dec << "\t<testsuite name=\"" << current_suite << "\" tests=\"" << n_of_tests << "\">\n";
			Listener::begin(t,info, n_of_tests);
		}
		void end(suite const &t, char const *info){
			out << "\t</testsuite>\n";
			current_suite.clear();
			Listener::end(t,info);
		}
		void start(test const &t){
			out << "\t\t<testcase classname=\""<<current_suite <<"\" name=\""<< mask_xml_chars(t.name())<<"\"";
			Listener::start(t);
		}
		void success(test const &t, char const *msg){
			out << "/>\n";
			Listener::success(t,msg);
		}
		void failure(test const &t,test_failure const &e){
			out << std::dec <<  ">\n\t\t\t<failure message=\"" << mask_xml_chars(e.filename) << ":" << e.lineno << " "
				<< mask_xml_chars(e.reason) << "\">\n"<<mask_xml_chars(e.reason)<<"\n\t\t\t</failure>\n\t\t</testcase>\n";
			Listener::failure(t,e);
		}
		void error(test const &t, char const *what){
			out << ">\n\t\t\t<error message=\"" << mask_xml_chars(t.name()) << " " << mask_xml_chars(what)
				<< "\" type=\"unexpected exception\">\n"<<mask_xml_chars(what)
				<<"\n\t\t\t</error>\n\t\t</testcase>\n";
			Listener::error(t,what);
		}
	};
}

#endif /*IDE_LISTENER_H_*/
