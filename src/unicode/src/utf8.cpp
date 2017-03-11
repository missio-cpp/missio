//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011 - 2017 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/unicode/utf8.hpp>

// Implementation headers
#include "utf8.hpp"

// STL headers
#include <algorithm>
#include <iterator>


namespace missio
{
namespace unicode
{
namespace utf8
{

std::size_t length(std::string const& str)
{
    return impl::utf8::length(str.begin(), str.end());
}

void replace_invalid(std::string& str, char32_t replacement_char)
{
    std::string result;

    impl::utf8::replace_invalid(str.begin(), str.end(), std::back_inserter(result), replacement_char);

    std::swap(str, result);
}

void replace_invalid(std::string& str)
{
    std::string result;

    impl::utf8::replace_invalid(str.begin(), str.end(), std::back_inserter(result));

    std::swap(str, result);
}

void validate(std::string const& str)
{
    impl::utf8::validate(str.begin(), str.end());
}

bool is_valid(std::string const& str)
{
    return impl::utf8::is_valid(str.begin(), str.end());
}

}   // namespace utf8
}   // namespace unicode
}   // namespace missio
