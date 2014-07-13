//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_sink_iterator_hpp
#define _missio_format_detail_sink_iterator_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <iterator>
#include <cstddef>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Sink>
class sink_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    explicit sink_iterator(Sink& sink) :
        sink_(sink)
    {
    }

    sink_iterator(sink_iterator const&) = default;
    sink_iterator& operator=(sink_iterator const&) = delete;

    template <typename Char>
    sink_iterator& operator=(Char ch)
    {
        sink_.put(static_cast<char>(ch));
        return *this;
    }

    sink_iterator& operator*()
    {
        return *this;
    }

    sink_iterator& operator++()
    {
        return *this;
    }

    sink_iterator operator++(int)
    {
        return *this;
    }

private:
    Sink& sink_;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_sink_iterator_hpp
