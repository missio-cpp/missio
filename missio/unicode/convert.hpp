//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_convert_hpp
#define _missio_unicode_convert_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/unicode/utf16.hpp>
#include <missio/unicode/utf8.hpp>

// STL headers
#include <cstring>
#include <cwchar>


namespace missio
{
namespace unicode
{

template <typename OctetIterator, typename OutputIterator>
void utf8_to_utf16(OctetIterator first, OctetIterator last, OutputIterator dest)
{
    while(first != last)
        utf16::write(utf8::next(first, last), dest);
}

template <typename OctetIterator, typename OutputIterator>
void utf8_to_utf32(OctetIterator first, OctetIterator last, OutputIterator dest)
{
    while(first != last)
        *dest++ = utf8::next(first, last);
}

template <typename UTF16Iterator, typename OutputIterator>
void utf16_to_utf8(UTF16Iterator first, UTF16Iterator last, OutputIterator dest)
{
    while(first != last)
        utf8::write(utf16::next(first, last), dest);
}

template <typename UTF16Iterator, typename OutputIterator>
void utf16_to_utf32(UTF16Iterator first, UTF16Iterator last, OutputIterator dest)
{
    while(first != last)
        *dest++ = utf16::next(first, last);
}

template <typename UTF32Iterator, typename OutputIterator>
void utf32_to_utf8(UTF32Iterator first, UTF32Iterator last, OutputIterator dest)
{
    while(first != last)
        utf8::write(*first++, dest);
}

template <typename UTF32Iterator, typename OutputIterator>
void utf32_to_utf16(UTF32Iterator first, UTF32Iterator last, OutputIterator dest)
{
    while(first != last)
        utf16::write(*first++, dest);
}

template <typename WideCharIterator, typename OutputIterator>
void wchar_to_utf8(WideCharIterator first, WideCharIterator last, OutputIterator dest)
{
#if defined(WCHAR_MAX) && (WCHAR_MAX == 0xFFFF)
    // Make a poor guess that wchar_t uses UTF-16 encoding (usually on Windows systems)
    utf16_to_utf8(first, last, dest);
#else
    // Otherwise assume wchar_t uses UTF-32 encoding (usually on Unix-based systems)
    utf32_to_utf8(first, last, dest);
#endif
}

template <typename OctetIterator, typename WideCharIterator>
void utf8_to_wchar(OctetIterator first, OctetIterator last, WideCharIterator dest)
{
#if defined(WCHAR_MAX) && (WCHAR_MAX == 0xFFFF)
    // Make a poor guess that wchar_t uses UTF-16 encoding (usually on Windows systems)
    utf8_to_utf16(first, last, dest);
#else
    // Otherwise assume wchar_t uses UTF-32 encoding (usually on Unix-based systems)
    utf8_to_utf32(first, last, dest);
#endif
}

inline std::string convert(std::wstring const& str)
{
    std::string result;

    wchar_to_utf8(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

inline std::string convert(wchar_t const* str)
{
    std::string result;

    wchar_to_utf8(str, str + std::wcslen(str), std::back_inserter(result));

    return result;
}

inline std::wstring convert(std::string const& str)
{
    std::wstring result;

    utf8_to_wchar(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

inline std::wstring convert(char const* str)
{
    std::wstring result;

    utf8_to_wchar(str, str + std::strlen(str), std::back_inserter(result));

    return result;
}

}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_convert_hpp
