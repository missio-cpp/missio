//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_string_hpp
#define _missio_json_string_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <iosfwd>
#include <string>


namespace missio
{
namespace json
{

class string
{
public:
    string();
    ~string();

    string(char const* str);
    string(wchar_t const* str);

    string(char const* str, std::size_t size);
    string(wchar_t const* str, std::size_t size);

    string(std::string const& str);
    string(std::wstring const& str);

    string(std::string&& str);

    string(string&& other);
    string& operator=(string&& other);

    string(string const& other);
    string& operator=(string const& other);

    char const* c_str() const;

    operator std::string() const;
    operator std::wstring() const;

    friend bool operator==(string const& lhs, string const& rhs);
    friend bool operator<(string const& lhs, string const& rhs);

private:
    std::string str_;
};

std::istream& operator>>(std::istream& is, string& str);
std::wistream& operator>>(std::wistream& is, string& str);

std::ostream& operator<<(std::ostream& os, string const& str);
std::wostream& operator<<(std::wostream& os, string const& str);

inline bool operator!=(string const& lhs, string const& rhs) { return !operator==(lhs, rhs); }
inline bool operator<=(string const& lhs, string const& rhs) { return !operator<(rhs, lhs); }
inline bool operator>=(string const& lhs, string const& rhs) { return !operator<(lhs, rhs); }
inline bool operator>(string const& lhs, string const& rhs) { return operator<(rhs, lhs); }

}   // namespace json
}   // namespace missio

#endif  // _missio_json_string_hpp
