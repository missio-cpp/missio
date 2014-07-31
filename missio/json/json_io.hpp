//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_json_io_hpp
#define _missio_json_json_io_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/value.hpp>

// STL headers
#include <iosfwd>
#include <string>


namespace missio
{
namespace json
{

value read(std::string const& str);
std::string write(value const& value);
std::string write_formatted(value const& value);

std::istream& operator>>(std::istream& is, value& value);
std::ostream& operator<<(std::ostream& os, value const& value);

}   // namespace json
}   // namespace missio

#endif  // _missio_json_json_io_hpp
