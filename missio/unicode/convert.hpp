//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
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

// converts UTF16 string to UTF8 string
MISSIO_EXPORT std::string to_utf8_string(char16_t const* str);
MISSIO_EXPORT std::string to_utf8_string(std::u16string const& str);

// converts UTF32 string to UTF8 string
MISSIO_EXPORT std::string to_utf8_string(char32_t const* str);
MISSIO_EXPORT std::string to_utf8_string(std::u32string const& str);

// converts wide string to UTF8 string
MISSIO_EXPORT std::string to_utf8_string(wchar_t const* str);
MISSIO_EXPORT std::string to_utf8_string(std::wstring const& str);

// converts UTF8 string to UTF16 string
MISSIO_EXPORT std::u16string to_utf16_string(char const* str);
MISSIO_EXPORT std::u16string to_utf16_string(std::string const& str);

// converts UTF32 string to UTF16 string
MISSIO_EXPORT std::u16string to_utf16_string(char32_t const* str);
MISSIO_EXPORT std::u16string to_utf16_string(std::u32string const& str);

// converts wide string to UTF16 string
MISSIO_EXPORT std::u16string to_utf16_string(wchar_t const* str);
MISSIO_EXPORT std::u16string to_utf16_string(std::wstring const& str);

// converts UTF8 string to UTF32 string
MISSIO_EXPORT std::u32string to_utf32_string(char const* str);
MISSIO_EXPORT std::u32string to_utf32_string(std::string const& str);

// converts UTF16 string to UTF32 string
MISSIO_EXPORT std::u32string to_utf32_string(char16_t const* str);
MISSIO_EXPORT std::u32string to_utf32_string(std::u16string const& str);

// converts wide string to UTF32 string
MISSIO_EXPORT std::u32string to_utf32_string(wchar_t const* str);
MISSIO_EXPORT std::u32string to_utf32_string(std::wstring const& str);

// converts UTF8 string to wide string
MISSIO_EXPORT std::wstring to_wide_string(char const* str);
MISSIO_EXPORT std::wstring to_wide_string(std::string const& str);

// converts UTF16 string to wide string
MISSIO_EXPORT std::wstring to_wide_string(char16_t const* str);
MISSIO_EXPORT std::wstring to_wide_string(std::u16string const& str);

// converts UTF32 string to wide string
MISSIO_EXPORT std::wstring to_wide_string(char32_t const* str);
MISSIO_EXPORT std::wstring to_wide_string(std::u32string const& str);

}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_convert_hpp
