//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_utf8_hpp
#define _missio_unicode_utf8_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

// STL headers
#include <cstdint>
#include <string>


namespace missio
{
namespace unicode
{
namespace utf8
{

// calculate number of UTF32 code points
MISSIO_EXPORT std::size_t length(std::string const& str);

// replace invalid (non-UTF8) octets with replacement character
MISSIO_EXPORT void replace_invalid(std::string& str, std::uint32_t replacement_char);

// replace invalid (non-UTF8) octets with default replacement character
MISSIO_EXPORT void replace_invalid(std::string& str);

// validate UTF8 string and throws exception on invalid data
MISSIO_EXPORT void validate(std::string const& str);

// return true if string contains valid UTF8 string, false otherwise
MISSIO_EXPORT bool is_valid(std::string const& str);

}   // namespace utf8
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_utf8_hpp
