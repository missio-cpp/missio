//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_string_hpp
#define _missio_format_string_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/item_buffer.hpp>

// STL headers
#include <string>


namespace missio
{
namespace format
{

class string
{
public:
    string(std::string const& format);

    string(string const&) = delete;
    string& operator=(string const&) = delete;

    detail::item_buffer const& items() const;

private:
    std::string const format_;
    detail::item_buffer items_;
};

}   // namespace format
}   // namespace missio

#endif  // _missio_format_string_hpp
