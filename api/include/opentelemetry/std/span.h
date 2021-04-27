// Copyright 2020, OpenTelemetry Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "opentelemetry/version.h"

// Standard library implementation requires at least C++17 compiler.
// Older C++14 compilers may provide support for __has_include as a
// conforming extension.
#if defined __has_include
#  if __has_include(<version>)  // Check for __cpp_{feature}
#    include <version>
#    if defined(__cpp_lib_span)
#      define HAVE_SPAN
#    endif
#  endif
#  if !defined(HAVE_SPAN)
#    // Check for Visual Studio span
#    if defined(_MSVC_VALUE) && _HAS_CXX20
#      define HAVE_SPAN
#    endif
#    // Check for other compiler span implementation
#    if !defined(_MSVC_VALUE) && __has_include(<span>)
       // This works as long as compiler standard is set to C++20
#      define HAVE_SPAN
#    endif
#  endif
#endif

#if !defined(HAVE_SPAN)
#  if defined(HAVE_GSL)
#    include <type_traits>
// Guidelines Support Library provides an implementation of std::span
#    include <gsl/gsl>
OPENTELEMETRY_BEGIN_NAMESPACE
namespace nostd
{
template <class ElementType, std::size_t Extent = gsl::dynamic_extent>
using span = gsl::span<ElementType, Extent>;
}
OPENTELEMETRY_END_NAMESPACE
#  define HAVE_SPAN
#  else
// No `gsl::span`, no `std::span`, fallback to `nostd::span`
#  endif

#else  // HAVE_SPAN
// Using std::span (https://wg21.link/P0122R7) from Standard Library available in C++20 :
// - GCC libstdc++ 10+
// - Clang libc++ 7
// - MSVC Standard Library 19.26*
// - Apple Clang 10.0.0*
#  include <limits>
#  include <span>
OPENTELEMETRY_BEGIN_NAMESPACE
namespace nostd
{
constexpr std::size_t dynamic_extent = (std::numeric_limits<std::size_t>::max());

template <class ElementType, std::size_t Extent = nostd::dynamic_extent>
using span = std::span<ElementType, Extent>;
}  // namespace nostd
OPENTELEMETRY_END_NAMESPACE
#endif  // of HAVE_SPAN
