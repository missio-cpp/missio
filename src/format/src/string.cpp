//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/format/string.hpp>

// Implementation headers
#include "parse_format.hpp"


namespace missio
{
namespace format
{

string::string(std::string const& format) :
    format_(format)
{
    detail::parse_format(format_.begin(), format_.end(), items_);
}

detail::item_buffer const& string::items() const
{
    return items_;
}

}   // namespace format
}   // namespace missio
