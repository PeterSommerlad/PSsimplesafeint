/*********************************************************************************
 * This file is part of CUTE.
 *
 * Copyright (c) 2016-2018 Peter Sommerlad, IFS
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

#ifndef CUTE_DEPRECATED_H_
#define CUTE_DEPRECATED_H_

#if __cplusplus >= 201402L
#define DEPRECATE(orig, repl) [[deprecated ("Use "#repl" instead.")]] inline void orig() {}
#elif defined(__GNUG__)
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#if GCC_VERSION >= 40500 || defined(__clang__)
#define DEPRECATE(orig, repl) __attribute__((deprecated("Use "#repl" instead."))) inline void orig() {}
#else
#define DEPRECATE(orig, repl) __attribute__((deprecated)) inline void orig() {}
#endif
#elif defined(_MSC_VER)
#define DEPRECATE(orig, repl) __declspec(deprecated(#orig" is deprecated, use "#repl" instead.")) inline void orig() {}
#endif

#ifdef DEPRECATE
#define DEPRECATED(name) name()
#endif

#endif /*CUTE_DEPRECATED_H_*/
