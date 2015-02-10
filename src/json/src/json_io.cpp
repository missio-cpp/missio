//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/json/json_io.hpp>
#include <missio/json/exception.hpp>

// Implementation headers
#include "generate_json.hpp"
#include "parse_json.hpp"

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

    if(!detail::parse_json(str.begin(), str.end(), value))
        throw exception("cannot parse JSON string");

    return value;
}

std::string write(value const& value, std::size_t indent)
{
    std::string str;

    if(indent > 0)
    {
        if(!detail::generate_json(value, indent, std::back_inserter(str)))
            throw exception("cannot generate formatted JSON string");
    }
    else
    {
        if(!detail::generate_json(value, std::back_inserter(str)))
            throw exception("cannot generate JSON string");
    }

    return str;
}

std::istream& operator>>(std::istream& is, value& value)
{
    std::istreambuf_iterator<char> begin(is);
    std::istreambuf_iterator<char> end;

    value = read(std::string(begin, end));

    return is;
}

std::ostream& operator<<(std::ostream& os, value const& value)
{
    os << write(value, 4);
    return os;
}

}   // namespace json
}   // namespace missio
