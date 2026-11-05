// { dg-do compile { target c++11 } }
// { dg-require-gthreads "" }

// Copyright (C) 2026 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

#include <mutex>
#include <type_traits>

#ifdef __PSP__
// PSP mutexes own kernel resources even when statically initialized.
static_assert(!std::is_trivially_destructible<std::mutex>::value,
	      "mutex must destroy its semaphore");
static_assert(!std::is_trivially_destructible<std::timed_mutex>::value,
	      "timed_mutex must destroy its semaphore");
static_assert(!std::is_trivially_destructible<std::recursive_mutex>::value,
	      "recursive_mutex must destroy its semaphore");
static_assert(!std::is_trivially_destructible<std::recursive_timed_mutex>::value,
	      "recursive_timed_mutex must destroy its semaphore");
#endif
