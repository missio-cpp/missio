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

// BOOST headers
#include <boost/utility/string_ref.hpp>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Sink>
void insert_string(Sink& sink, boost::string_ref const& str)
{
    insert_string(sink_iterator<Sink>(sink), str.begin(), str.end());
}

template <typename Sink, typename Iterator>
void insert_string(Sink sink, Iterator first, Iterator last)
{
    while(first != last)
    {
        switch(*first)
        {
            case '{':       // always come in pairs
            case '}':       // so skip the first one
                ++first;    // no break after, intentionally

            default:
                *sink++ = *first;
        }

        ++first;
    }
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_insert_string_hpp