/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2015-2018 Peter Sommerlad, IFS
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

#ifndef CUTE_RANGE_H_
#define CUTE_RANGE_H_

#include "cute_determine_version.h"

#include <iterator>
#include <algorithm>
#ifdef USE_STD11
#include <initializer_list>
#endif

namespace cute{
	template <typename ForwardIterator>
	struct range {
		typedef ForwardIterator const_iterator; // for to_stream dispatch
		typedef typename std::iterator_traits<const_iterator>::value_type value_type;
		const_iterator const b;
		const_iterator const e;
		range(ForwardIterator bb,ForwardIterator ee):b(bb),e(ee){}
		const_iterator begin() const { return b; }
		const_iterator end() const { return e; }
		template <typename RangeOrContainer>
		bool operator==(RangeOrContainer const &other) const{
#ifdef USE_STD14
			return std::equal(begin(),end(),other.begin(),other.end());
#else
			if (std::distance(begin(),end())==std::distance(other.begin(),other.end())){
				return std::equal(begin(),end(),other.begin());
			}
			return false;
#endif
		}
	};
	template <typename ForwardIterator>
	range<ForwardIterator> make_range(ForwardIterator b, ForwardIterator e){
		return range<ForwardIterator>(b,e);
	}

#ifdef USE_STD11
	template <typename Value>
	range<typename std::initializer_list<Value>::iterator>
	make_range(std::initializer_list<Value> const &il){
		return range<typename std::initializer_list<Value>::iterator>(il.begin(),il.end());
	}
#endif
}

#endif /* CUTE_RANGE_H_ */
