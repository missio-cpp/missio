//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_insert_string_hpp
#define _missio_format_detail_insert_string_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/sink_iterator.hpp>
#include <missio/format/detail/string_view.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Sink>
void insert_string(Sink& sink, string_view const& str)
{
    insert_string(sink, std::begin(str), std::end(str));
}

template <typename Sink, typename Iterator>
void insert_string(Sink& sink, Iterator first, Iterator last)
{
    sink_iterator<Sink> sink_iterator(sink);

    while(first != last)
    {
        switch(*first)
        {
            case '{':       // always come in pairs
            case '}':       // so skip the first one
                ++first;    // no break after, intentionally

            default:
                *sink_iterator++ = *first;
        }

        ++first;
    }
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_insert_string_hpp
