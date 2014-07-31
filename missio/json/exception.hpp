//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_exception_hpp
#define _missio_json_exception_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <stdexcept>
#include <string>


namespace missio
{
namespace json
{

class exception : public std::runtime_error
{
public:
    explicit exception(std::string const& message) :
        std::runtime_error(message)
    {
    }
};

}   // namespace json
}   // namespace missio

#endif  // _missio_json_exception_hpp
