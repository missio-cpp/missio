//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/format/detail/format_adapter.hpp>

// Implementation headers
#include "parse_format.hpp"


namespace missio
{
namespace format
{
namespace detail
{

format_adapter<char const*>::format_adapter(char const* format)
{
    parse_format(format, format + std::strlen(format), items_);
}

item_buffer const& format_adapter<char const*>::items() const
{
    return items_;
}

format_adapter<std::string>::format_adapter(std::string const& format)
{
    parse_format(format.begin(), format.end(), items_);
}

item_buffer const& format_adapter<std::string>::items() const
{
    return items_;
}

format_adapter<string>::format_adapter(string const& format) :
    format_(format)
{
}

item_buffer const& format_adapter<string>::items() const
{
    return format_.items();
}

}   // namespace detail
}   // namespace format
}   // namespace missio
