//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/string.hpp>
#include <missio/unicode/unicode.hpp>

// STL headers
#include <iostream>
#include <iterator>
#include <utility>


namespace missio
{
namespace json
{

string::string(char const* str) :
    str_(str)
{
    unicode::utf8::validate(str_);
}

string::string(wchar_t const* str) :
    str_(unicode::to_utf8_string(str))
{
}

string::string(std::string&& str) :
    str_(std::forward<std::string>(str))
{
    unicode::utf8::validate(str_);
}

string::string(std::string const& str) :
    str_(str)
{
    unicode::utf8::validate(str_);
}

string::string(std::wstring const& str) :
    str_(unicode::to_utf8_string(str))
{
}

char const* string::c_str() const
{
    return str_.c_str();
}

string::operator std::string() const
{
    return str_;
}

string::operator std::wstring() const
{
    return unicode::to_wide_string(str_);
}

bool operator==(string const& lhs, string const& rhs)
{
    return lhs.str_ == rhs.str_;
}

bool operator<(string const& lhs, string const& rhs)
{
    return lhs.str_ < rhs.str_;
}

std::istream& operator>>(std::istream& is, string& str)
{
    std::string temp;

    is >> temp;
    str = temp;

    return is;
}

std::wistream& operator>>(std::wistream& is, string& str)
{
    std::wstring temp;

    is >> temp;
    str = temp;

    return is;
}

std::ostream& operator<<(std::ostream& os, string const& str)
{
    std::string temp;

    temp = str;
    os << temp;

    return os;
}

std::wostream& operator<<(std::wostream& os, string const& str)
{
    std::wstring temp;

    temp = str;
    os << temp;

    return os;
}

}   // namespace json
}   // namespace missio
