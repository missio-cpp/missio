//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2016 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/unicode/convert.hpp>

// Implementation headers
#include "case_folding.hpp"
#include "utf8_iterator.hpp"
#include "convert.hpp"

// STL headers
#include <iterator>


namespace missio
{
namespace unicode
{

std::string to_utf8(std::u16string const& str)
{
    std::string result;

    impl::utf16_to_utf8(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::string to_utf8(std::u32string const& str)
{
    std::string result;

    impl::utf32_to_utf8(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u16string to_utf16(std::string const& str)
{
    std::u16string result;

    impl::utf8_to_utf16(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u16string to_utf16(std::u32string const& str)
{
    std::u16string result;

    impl::utf32_to_utf16(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u32string to_utf32(std::string const& str)
{
    std::u32string result;

    impl::utf8_to_utf32(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u32string to_utf32(std::u16string const& str)
{
    std::u32string result;

    impl::utf16_to_utf32(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::string to_upper(std::string const& str)
{
    std::string result;

    return result;
}

std::string to_lower(std::string const& str)
{
    std::string result;

    return result;
}

std::string to_title(std::string const& str)
{
    std::string result;

    return result;
}

std::u16string to_upper(std::u16string const& str)
{
    std::u16string result;

    return result;
}

std::u16string to_lower(std::u16string const& str)
{
    std::u16string result;

    return result;
}

std::u16string to_title(std::u16string const& str)
{
    std::u16string result;

    return result;
}

std::u32string to_upper(std::u32string const& str)
{
    std::u32string result;

    return result;
}

std::u32string to_lower(std::u32string const& str)
{
    std::u32string result;

    return result;
}

std::u32string to_title(std::u32string const& str)
{
    std::u32string result;

    return result;
}

std::string fold_case(std::string const& str)
{
    std::string result;

    impl::fold_case_utf8(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u16string fold_case(std::u16string const& str)
{
    std::u16string result;

    impl::fold_case_utf16(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

std::u32string fold_case(std::u32string const& str)
{
    std::u32string result;

    impl::fold_case_utf32(str.begin(), str.end(), std::back_inserter(result));

    return result;
}

}   // namespace unicode
}   // namespace missio
