//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/json_io.hpp>
#include <missio/json/exception.hpp>
#include <missio/json/detail/parse.hpp>
#include <missio/json/detail/generate.hpp>

// STL headers
#include <iostream>
#include <iterator>


namespace missio
{
namespace json
{

value read(std::string const& str)
{
    value value;

    if(!detail::parse(str.begin(), str.end(), value))
        throw exception("cannot parse JSON string");

    return value;
}

std::string write(value const& value)
{
    std::string str;

    if(!detail::generate(value, std::back_inserter(str)))
        throw exception("cannot generate JSON string");

    return str;
}

//TODO: formatted write is not implemented
std::string write_formatted(value const& value)
{
    return write(value);
}

std::istream& operator>>(std::istream& is, value& value)
{
    std::istreambuf_iterator<char> begin(is);
    std::istreambuf_iterator<char> end;
    std::string str(begin, end);
    value = read(str);
    return is;
}

std::ostream& operator<<(std::ostream& os, value const& value)
{
    os << write_formatted(value);
    return os;
}

}   // namespace json
}   // namespace missio