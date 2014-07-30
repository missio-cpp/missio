//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/unicode/convert.hpp>

// Implementation headers
#include "wchar_convert.hpp"
#include "convert.hpp"

// STL headers
#include <iterator>


namespace missio
{
namespace unicode
{

std::string to_utf8_string(std::u16string const& str)
{
    std::string result;

    impl::utf16_to_utf8(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::string to_utf8_string(std::u32string const& str)
{
    std::string result;

    impl::utf32_to_utf8(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::string to_utf8_string(std::wstring const& str)
{
    std::string result;

    impl::wchar_convert::to_utf8(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u16string to_utf16_string(std::string const& str)
{
    std::u16string result;

    impl::utf8_to_utf16(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u16string to_utf16_string(std::u32string const& str)
{
    std::u16string result;

    impl::utf32_to_utf16(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u16string to_utf16_string(std::wstring const& str)
{
    std::u16string result;

    impl::wchar_convert::to_utf16(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u32string to_utf32_string(std::string const& str)
{
    std::u32string result;

    impl::utf8_to_utf32(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u32string to_utf32_string(std::u16string const& str)
{
    std::u32string result;

    impl::utf16_to_utf32(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u32string to_utf32_string(std::wstring const& str)
{
    std::u32string result;

    impl::wchar_convert::to_utf32(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::wstring to_wide_string(std::string const& str)
{
    std::wstring result;

    impl::wchar_convert::from_utf8(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::wstring to_wide_string(std::u16string const& str)
{
    std::wstring result;

    impl::wchar_convert::from_utf16(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::wstring to_wide_string(std::u32string const& str)
{
    std::wstring result;

    impl::wchar_convert::from_utf32(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

}   // namespace unicode
}   // namespace missio
