//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
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
#include <cctype>


namespace missio
{
namespace format
{
namespace detail
{

struct null_policy
{
    template <typename Char>
    Char operator()(Char ch) const
    {
        return ch;
    }
};

struct counting_policy
{
    counting_policy() :
        count(0u)
    {
    }

    template <typename Char>
    Char operator()(Char ch) const
    {
        ++count;
        return ch;
    }

    mutable std::size_t count;
};

struct lower_case_policy
{
    template <typename Char>
    Char operator()(Char ch) const
    {
        return std::tolower(ch);
    }
};

struct upper_case_policy
{
    template <typename Char>
    Char operator()(Char ch) const
    {
        return std::toupper(ch);
    }
};

template <typename Sink, typename Policy = null_policy>
class sink_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    explicit sink_iterator(Sink& sink) :
        sink_(sink)
    {
    }

    sink_iterator(sink_iterator const&) = default;
    sink_iterator& operator=(sink_iterator const&) = delete;

    Policy const& policy() const
    {
        return policy_;
    }

    template <typename Char>
    void put(Char ch)
    {
        sink_.put(policy_(ch));
    }

    template <typename Char>
    sink_iterator& operator=(Char ch)
    {
        sink_.put(policy_(ch));
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
    Policy policy_;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_sink_iterator_hpp
