//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_string_hpp
#define _missio_format_string_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/parse_format.hpp>

// BOOST headers
#include <boost/noncopyable.hpp>

// STL headers
#include <string>


namespace missio
{
namespace format
{

class string :
    private boost::noncopyable
{
public:
    string(std::string const& format) :
        format_(format)
    {
        detail::parse_format(format_.data(), format_.size(), items_);
    }

    detail::item_buffer const& items() const
    {
        return items_;
    }

private:
    std::string const format_;
    detail::item_buffer items_;
};

}   // namespace format
}   // namespace missio

#endif  // _missio_format_string_hpp