//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_format_adapter_hpp
#define _missio_format_detail_format_adapter_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/string.hpp>
#include <missio/format/detail/item_buffer.hpp>
#include <missio/format/detail/parse_format.hpp>

// STL headers
#include <cstddef>
#include <cstring>
#include <string>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Format>
class format_adapter;

template <>
class format_adapter<char const*>
{
public:
    explicit format_adapter(char const* format)
    {
        parse_format(format, std::strlen(format), items_);
    }

    format_adapter(format_adapter const&) = delete;
    format_adapter& operator=(format_adapter const&) = delete;

    item_buffer const& items() const
    {
        return items_;
    }

private:
    item_buffer items_;
};

template <>
class format_adapter<std::string>
{
public:
    explicit format_adapter(std::string const& format)
    {
        parse_format(format.data(), format.size(), items_);
    }

    format_adapter(format_adapter const&) = delete;
    format_adapter& operator=(format_adapter const&) = delete;

    item_buffer const& items() const
    {
        return items_;
    }

private:
    item_buffer items_;
};

template <>
class format_adapter<string>
{
public:
    explicit format_adapter(string const& format) :
        format_(format)
    {
    }

    format_adapter(format_adapter const&) = delete;
    format_adapter& operator=(format_adapter const&) = delete;

    item_buffer const& items() const
    {
        return format_.items();
    }

private:
    string const& format_;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_format_adapter_hpp
