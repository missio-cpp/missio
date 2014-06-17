//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/string.hpp>
#include <missio/utf8/convert.hpp>

// STL headers
#include <iterator>
#include <utility>


namespace missio
{
namespace json
{

string::string()
{
}

string::~string()
{
}

string::string(char const* str) :
    str_(str)
{
    utf8::validate(str_.begin(), str_.end());
}

string::string(wchar_t const* str)
{
    std::back_insert_iterator<std::string> insert_iterator(str_);
    utf8::wchar_to_utf8(str, str + std::wcslen(str), insert_iterator);
}

string::string(char const* str, std::size_t size) :
    str_(str, size)
{
    utf8::validate(str_.begin(), str_.end());
}

string::string(wchar_t const* str, std::size_t size)
{
    std::back_insert_iterator<std::string> insert_iterator(str_);
    utf8::wchar_to_utf8(str, str + size, insert_iterator);
}

string::string(std::string const& str) :
    str_(str)
{
    utf8::validate(str_.begin(), str_.end());
}

string::string(std::wstring const& str)
{
    std::back_insert_iterator<std::string> insert_iterator(str_);
    utf8::wchar_to_utf8(str.begin(), str.end(), insert_iterator);
}

string::string(std::string&& str) :
    str_(std::move(str))
{
}

string::string(string&& other) :
    str_(std::move(other.str_))
{
}

string& string::operator=(string&& other)
{
    if(&other != this)
        str_ = std::move(other.str_);
    return *this;

}

string::string(string const& other) :
    str_(other.str_)
{
}

string& string::operator=(string const& other)
{
    if(&other != this)
        str_ = other.str_;
    return *this;
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
    std::wstring str;

    std::back_insert_iterator<std::wstring> insert_iterator(str);
    utf8::utf8_to_wchar(str_.begin(), str_.end(), insert_iterator);

    return str;
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
