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

#ifndef CUTE_RUNNER_H_
#define CUTE_RUNNER_H_

#include "cute_test.h"
#include "cute_suite.h"
#include "cute_listener.h"
#include "cute_determine_traits.h"

#include <algorithm>
#include <functional>
#include <iterator>
#include <set>

namespace cute {
	namespace runner_aux {
	struct prefixMatcher
	{
		prefixMatcher(std::string const &prefix):prefix(prefix){}
		bool operator()(std::string const &s) const {
			size_t found=s.find(prefix);
			return found==0 && (s.size()==prefix.size() || s[prefix.size()]=='#');
		}
	private:
		std::string const prefix;
	};
	struct prefixCutter
	{
		prefixCutter(std::string const &prefix):prefix(prefix){}
		std::string operator()(std::string s) const {
			size_t found=s.find(prefix);
			if ( found==0 && s.size()>prefix.size() && s[prefix.size()]=='#'){
				s = s.substr(prefix.size()+1);
			} else {
				s.clear(); // either no match, or no individual test
			}
			return s;
		}
	private:
		std::string const prefix;
	};
	class ArgvTestFilter
	{
	    std::set<std::string> match;
	    bool shouldRunSuite(std::string const &info, std::vector<std::string> const &args)
	    {
	        if(!args.size() || !info.size())
	            return true;
	        if(args.end() != find_if(args.begin(), args.end(), prefixMatcher(info))){
	           std::transform(args.begin(), args.end(), std::inserter(match,match.begin()),prefixCutter(info));
	           match.erase(std::string()); // get rid of empty string
	           return true;
	        }
	        return false;
	    }
	public:
	    bool const shouldrunsuite;
		ArgvTestFilter(std::string const &info, std::vector<std::string> const &args)
		:shouldrunsuite(shouldRunSuite(info,args)){}
	    bool shouldRun(const std::string & name) const
	    {
	        return match.empty() || match.count(name);
	    }
	};
	} // namespace runner_aux
	template <typename Listener=null_listener>
	struct runner{
		Listener &listener;
	    std::vector<std::string> args;
		runner(Listener &l, int argc = 0, const char *const *argv = 0):listener(l){
	        if(needsFiltering(argc,argv)){
	            std::remove_copy_if(argv + 1, argv + argc,back_inserter(args),std::logical_not<char const *>());
	        }
		}
		bool operator()(const test & t) const
	    {
	        return runit(t);
	    }

	    bool operator ()(suite const &s, const char *info = "") const
	    {
	    	runner_aux::ArgvTestFilter filter(info,args);

	        bool result = true;
	        if(filter.shouldrunsuite){
	            listener.begin(s, info, (size_t)
	            		count_if(s.begin(),s.end(),boost_or_tr1::bind(&runner_aux::ArgvTestFilter::shouldRun,filter,boost_or_tr1::bind(&test::name,_1))));
	            for(suite::const_iterator it = s.begin();it != s.end();++it){
	                if (filter.shouldRun(it->name())) result = this->runit(*it) && result;
	            }
	            listener.end(s, info);
	        }

	        return result;
	    }
	private:
	    bool needsFiltering(int argc, const char *const *argv) const
	    {
	        return argc > 1 && argv ;
	    }


	    bool runit(const test & t) const
	    {
	        try {
	            listener.start(t);
	            t();
	            listener.success(t, "OK");
	            return true;
	        } catch(const cute::test_failure & e){
	            listener.failure(t, e);
	        } catch(const std::exception & exc){
	            listener.error(t, demangle(exc.what()).c_str());
	        } catch(std::string & s){
	            listener.error(t, s.c_str());
	        } catch(const char *&cs) {
				listener.error(t,cs);
			} catch(...) {
				listener.error(t,"unknown exception thrown");
			}
			return false;
		}
	};
	template <typename Listener>
	runner<Listener> makeRunner(Listener &s, int argc = 0, const char *const *argv = 0){
		return runner<Listener>(s,argc,argv);
	}
}

#endif /*CUTE_RUNNER_H_*/
