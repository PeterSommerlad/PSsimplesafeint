/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2009-2018 Peter Sommerlad, IFS
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

#ifndef CUTE_DEMANGLE_H_
#define CUTE_DEMANGLE_H_
#include <string>
// needs adaptation for different compilers
// dependency to demangle is a given,
// otherwise we have to use macros everywhere
#ifdef __GNUG__ // also for clang...
#include <cxxabi.h> // __cxa_demangle
#include <cstdlib> // ::free() 
namespace cute {
	extern inline std::string demangle(char const *name);

namespace cute_impl_demangle {
inline std::string plain_demangle(char const *name){
	if (!name) return "unknown";
	char const *toBeFreed = abi::__cxa_demangle(name,0,0,0);
	std::string result(toBeFreed?toBeFreed:name);
	::free(const_cast<char*>(toBeFreed));
	return result;
}
#if defined(_LIBCPP_ABI_NAMESPACE) || defined(_LIBCPP_NAMESPACE) || defined(_GLIBCXX_USE_CXX11_ABI)
inline void patch_library_namespace(std::string &mightcontaininlinenamespace) {
// libc++ uses inline namespace std::_LIBCPP_NAMESPACE:: for its classes. This breaks the tests relying on meta information. re-normalize the names back to std::
// libstdc++ (at least in version 6.3.1) puts some STL classes into the inline namespace std::_GLIBCXX_NAMESPACE_CXX11 if in C++11 mode
	std::string::size_type pos=std::string::npos;
#define XNS(X) #X
#define NS(X) XNS(X)
#if defined( _LIBCPP_NAMESPACE)
#define TOREPLACE "::" NS(_LIBCPP_NAMESPACE)
#elif defined(_LIBCPP_ABI_NAMESPACE)
#define TOREPLACE  "::" NS(_LIBCPP_ABI_NAMESPACE)
#else
#define TOREPLACE "::" NS(_GLIBCXX_NAMESPACE_CXX11)
#endif
	std::string const nothing;
	while (std::string::npos != (pos= mightcontaininlinenamespace.find(TOREPLACE)))
			mightcontaininlinenamespace.erase(pos,sizeof(TOREPLACE)-1);
#undef NS
#undef XNS
#undef TOREPLACE
}
inline void patchresultforstring(std::string& result) {
	static const std::string stringid=plain_demangle(typeid(std::string).name());
	std::string::size_type pos=std::string::npos;
	while(std::string::npos != (pos=result.find(stringid))){
		if (!result.compare(pos+stringid.size(),2," >",2)) result.erase(pos+stringid.size(),1); // makes templates look nice
		result.replace(pos,stringid.size(),"std::string");
	}
	patch_library_namespace(result);
}
#endif

}
inline std::string demangle(char const *name){
	if (!name) return "unknown";
	std::string result(cute_impl_demangle::plain_demangle(name));
#if defined(_LIBCPP_ABI_NAMESPACE) || defined(_LIBCPP_NAMESPACE) || defined(_GLIBCXX_USE_CXX11_ABI)
	cute_impl_demangle::patchresultforstring(result);
#endif
	return result;
}
}
#else
namespace cute {
#ifdef _MSC_VER
namespace cute_demangle_impl {

inline void removeMSKeyword(std::string &name,std::string const &kw){
	std::string::size_type pos=std::string::npos;
	while (std::string::npos != (pos= name.find(kw)))
			name.erase(pos,kw.size());

}
inline void patchresultforstring(std::string& result) {
	static const std::string stringid=(typeid(std::string).name());
	std::string::size_type pos=std::string::npos;
	while(std::string::npos != (pos=result.find(stringid))){
		if (!result.compare(pos+stringid.size(),2," >",2)) result.erase(pos+stringid.size(),1); // makes templates look nice
		result.replace(pos,stringid.size(),"std::string");
	}
}

inline void patchMSMangling(std::string &name){
	patchresultforstring(name);
	removeMSKeyword(name,"class ");
	removeMSKeyword(name,"struct ");
	for (std::string::iterator i=name.begin(); i != name.end(); ++i){
		if (*i==','){  i = name.insert(i+1,' ');}
	}
	std::string::size_type pos=0;
	while(std::string::npos !=(pos=name.find(" ,",pos))){
		name.erase(pos,1);
		++pos;
	}
}
}
inline std::string demangle(char const *name){
	std::string result(name?name:"unknown");
	cute_demangle_impl::patchMSMangling(result);
	return result;
}

#else
// this default works reasonably with MSVC71 and 8, hopefully for others as well
inline std::string demangle(char const *name){
	return std::string(name?name:"unknown");
}
#endif
}
#endif

#endif /* CUTE_DEMANGLE_H_ */
