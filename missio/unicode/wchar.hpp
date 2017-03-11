//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_wchar_hpp
#define _missio_unicode_wchar_hpp

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

// Convert wide string to UTF-8 / UTF-16 / UTF-32 string
MISSIO_EXPORT std::string to_utf8(std::wstring const& str);
MISSIO_EXPORT std::u16string to_utf16(std::wstring const& str);
MISSIO_EXPORT std::u32string to_utf32(std::wstring const& str);

// Convert UTF-8 / UTF-16 / UTF-32 string to wide string
MISSIO_EXPORT std::wstring to_wide(std::string const& str);
MISSIO_EXPORT std::wstring to_wide(std::u16string const& str);
MISSIO_EXPORT std::wstring to_wide(std::u32string const& str);

// Convert wide string to upper / lower case
MISSIO_EXPORT std::wstring to_upper(std::wstring const& str);
MISSIO_EXPORT std::wstring to_lower(std::wstring const& str); 

}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_wchar_hpp
