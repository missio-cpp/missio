//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/unicode/wchar.hpp>

// Implementation headers
#include "wchar_convert.hpp"

// STL headers
#include <iterator>


namespace missio
{
namespace unicode
{

std::string to_utf8(std::wstring const& str)
{
    std::string result;

    impl::wchar_convert::to_utf8(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u16string to_utf16(std::wstring const& str)
{
    std::u16string result;

    impl::wchar_convert::to_utf16(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u32string to_utf32(std::wstring const& str)
{
    std::u32string result;

    impl::wchar_convert::to_utf32(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::wstring to_wide(std::string const& str)
{
    std::wstring result;

    impl::wchar_convert::from_utf8(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::wstring to_wide(std::u16string const& str)
{
    std::wstring result;

    impl::wchar_convert::from_utf16(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::wstring to_wide(std::u32string const& str)
{
    std::wstring result;

    impl::wchar_convert::from_utf32(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::wstring to_upper(std::wstring const& str)
{
    std::wstring result;

    return result;
}

std::wstring to_lower(std::wstring const& str)
{
    std::wstring result;

    return result;
}

}   // namespace unicode
}   // namespace missio
