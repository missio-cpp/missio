//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_sink_adapter_hpp
#define _missio_format_detail_sink_adapter_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <string>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Sink>
class sink_adapter
{
public:
    explicit sink_adapter(Sink& sink) :
        sink_(&sink)
    {
    }

    sink_adapter(sink_adapter const&) = default;
    sink_adapter& operator=(sink_adapter const&) = default;

    template <typename Char>
    void put(Char ch)
    {
        sink_->put(ch);
    }

private:
    Sink* sink_;
};

template <typename Char, typename Traits, typename Allocator>
class sink_adapter<std::basic_string<Char, Traits, Allocator>>
{
public:
    explicit sink_adapter(std::basic_string<Char, Traits, Allocator>& sink) :
        sink_(&sink)
    {
    }

    sink_adapter(sink_adapter const&) = default;
    sink_adapter& operator=(sink_adapter const&) = default;

    void put(Char ch)
    {
        sink_->push_back(ch);
    }

private:
    std::basic_string<Char, Traits, Allocator>* sink_;
};

template <typename Char, std::size_t N>
class sink_adapter<Char[N]>
{
public:
    explicit sink_adapter(Char (&sink)[N]) :
        sink_(sink),
        pos_(0u)
    {
    }

    ~sink_adapter()
    {
        sink_[pos_] = Char('\0');
    }

    sink_adapter(sink_adapter const&) = default;
    sink_adapter& operator=(sink_adapter const&) = default;

    void put(Char ch)
    {
        if(pos_ < N - 1)
            sink_[pos_++] = ch;
    }

private:
    Char* sink_;
    std::size_t pos_;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_sink_adapter_hpp
