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

// calculates number of UTF32 code points
std::size_t MISSIO_EXPORT length(std::string const& str);

// replaces invalid (non-UTF8) octets with replacement character
void MISSIO_EXPORT replace_invalid(std::string& str, std::uint32_t replacement_char);

// replaces invalid (non-UTF8) octets with default replacement character
void MISSIO_EXPORT replace_invalid(std::string& str);

// validates UTF8 sequence and throws exception on invalid data
void MISSIO_EXPORT validate(std::string const& str);

// returns true if string contains valid UTF8 sequence, false otherwise
bool MISSIO_EXPORT is_valid(std::string const& str);

}   // namespace utf8
}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_utf8_hpp
