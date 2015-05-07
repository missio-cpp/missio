//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_sink_iterator_hpp
#define _missio_format_detail_sink_iterator_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

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

struct MISSIO_EXPORT null_policy
{
    template <typename Char>
    bool operator()(Char) const
    {
        return true;
    }
};

struct MISSIO_EXPORT counting_policy
{
    counting_policy() :
        count(0u)
    {
    }

    template <typename Char>
    bool operator()(Char) const
    {
        ++count;
        return true;
    }

    mutable std::size_t count;
};

struct MISSIO_EXPORT lower_case_policy
{
    template <typename Char>
    bool operator()(Char& ch) const
    {
        ch = std::tolower(ch);
        return true;
    }
};

struct MISSIO_EXPORT upper_case_policy
{
    template <typename Char>
    bool operator()(Char& ch) const
    {
        ch = std::toupper(ch);
        return true;
    }
};

struct MISSIO_EXPORT limit_count_policy
{
    explicit limit_count_policy(std::size_t max_count) :
        max_count(max_count),
        count(0u)
    {
    }

    template <typename Char>
    bool operator()(Char) const
    {
        return count++ < max_count;
    }

    std::size_t max_count;
    mutable std::size_t count;
};

template <typename Sink, typename Policy = null_policy>
class sink_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
    explicit sink_iterator(Sink& sink) :
        sink_(&sink)
    {
    }

    sink_iterator(Sink& sink, Policy const& policy) :
        sink_(&sink),
        policy_(policy)
    {
    }

    sink_iterator(sink_iterator const&) = default;
    sink_iterator& operator=(sink_iterator const&) = default;

    Policy const& policy() const
    {
        return policy_;
    }

    template <typename Char>
    void put(Char ch)
    {
        if(policy_(ch))
        {
            sink_->put(ch);
        }
    }

    template <typename Char>
    sink_iterator& operator=(Char ch)
    {
        if(policy_(ch))
        {
            sink_->put(ch);
        }

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
    Sink* sink_;
    Policy policy_;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_sink_iterator_hpp
