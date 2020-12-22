/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2013-2018 Peter Sommerlad, IFS
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

#ifndef CUTE_XML_FILE_H_
#define CUTE_XML_FILE_H_

#include <fstream>
#include <string>

namespace cute {
struct xml_file_opener {
	std::string filename;
	std::ofstream out;
	xml_file_opener(int argc, char const *const* argv)
	:filename(argc>0&&argv[0]?basename(argv[0]):"testresult.xml")
	,out(filename.c_str()){}
	std::string basename(std::string path){
#if defined( _MSC_VER ) || defined(__MINGW32__)
		char const sep='\\';
#else
		char const sep='/';
#endif
		std::string::size_type pos=path.find_last_of(sep,path.size()-1);
		if (pos != std::string::npos) path.erase(0,pos+1);
		path+=".xml";
		return path;
	}
};
}

#endif /* CUTE_XML_FILE_H_ */
