//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_convert_hpp
#define _missio_unicode_convert_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

// STL headers
#include <string>


namespace missio
{
namespace unicode
{

// convert UTF16 / UTF32 string to UTF8 string
MISSIO_EXPORT std::string to_utf8(std::u16string const& str);
MISSIO_EXPORT std::string to_utf8(std::u32string const& str);

// convert UTF8 / UTF32 string to UTF16 string
MISSIO_EXPORT std::u16string to_utf16(std::string const& str);
MISSIO_EXPORT std::u16string to_utf16(std::u32string const& str);

// convert UTF8 / UTF16 string to UTF32 string
MISSIO_EXPORT std::u32string to_utf32(std::string const& str);
MISSIO_EXPORT std::u32string to_utf32(std::u16string const& str);

// convert UTF8 string to upper / lower / title case
MISSIO_EXPORT std::string to_upper(std::string const& str);
MISSIO_EXPORT std::string to_lower(std::string const& str);
MISSIO_EXPORT std::string to_title(std::string const& str);

// convert UTF16 string to upper / lower / title case
MISSIO_EXPORT std::u16string to_upper(std::u16string const& str);
MISSIO_EXPORT std::u16string to_lower(std::u16string const& str);
MISSIO_EXPORT std::u16string to_title(std::u16string const& str);

// convert UTF32 string to upper / lower / title case
MISSIO_EXPORT std::u32string to_upper(std::u32string const& str);
MISSIO_EXPORT std::u32string to_lower(std::u32string const& str);
MISSIO_EXPORT std::u32string to_title(std::u32string const& str);

// fold case of UTF8 / UTF16 / UTF32 string
MISSIO_EXPORT std::string fold_case(std::string const& str);
MISSIO_EXPORT std::u16string fold_case(std::u16string const& str);
MISSIO_EXPORT std::u32string fold_case(std::u32string const& str);

}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_convert_hpp
