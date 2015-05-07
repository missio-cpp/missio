//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_type_inserter_hpp
#define _missio_format_detail_type_inserter_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Applciation headers
#include <missio/format/detail/generate_value.hpp>
#include <missio/format/detail/real_generator.hpp>
#include <missio/format/detail/int_generator.hpp>
#include <missio/format/detail/type_adapter.hpp>

// BOOST headers
#include <boost/spirit/include/karma.hpp>

// STL headers
#include <algorithm>


namespace missio
{
namespace format
{
namespace detail
{

template <unsigned int Radix>
struct int_inserter
{
    int_inserter(int precision, bool force_sign, bool upper_case = false) :
        precision_(precision),
        force_sign_(force_sign),
        upper_case_(upper_case)
    {
    }

    template <typename Sink, typename Value>
    void call(Sink& sink, Value value) const
    {
        static int_generator<Value, Radix> const generator{};

        generate_value(sink, value, generator(precision_, force_sign_, upper_case_));
    }

private:
    int precision_;
    bool force_sign_;
    bool upper_case_;
};

template <real_format Format>
struct real_inserter
{
    real_inserter(int precision, bool force_sign, bool upper_case = false) :
        precision_(precision),
        force_sign_(force_sign),
        upper_case_(upper_case)
    {
    }

    template <typename Sink, typename Value>
    void call(Sink& sink, Value value) const
    {
        generate_value(sink, value, make_real_generator<Value, Format>(precision_, force_sign_, upper_case_));
    }

private:
    int precision_;
    bool force_sign_;
    bool upper_case_;
};

struct left_align_inserter
{
    explicit left_align_inserter(std::size_t align, char pad = ' ') :
        align_(align),
        pad_(pad)
    {
    }

    template <typename Sink, typename Value>
    void call(Sink& sink, Value const& value) const
    {
        sink_iterator<Sink, counting_policy> sink_iterator(sink);
        counting_policy const& counter = sink_iterator.policy();

        type_adapter<Value>::format(sink_iterator, value);

        if(align_ > counter.count)
        {
            std::fill_n(sink_iterator, align_ - counter.count, pad_);
        }
    }

private:
    std::size_t align_;
    char pad_;
};

struct right_align_inserter
{
    explicit right_align_inserter(std::size_t align, char pad = ' ') :
        align_(align),
        pad_(pad)
    {
    }

    template <typename Sink, typename Value>
    void call(Sink& sink, Value const& value) const
    {
        sink_buffer buffer;

        type_adapter<Value>::format(buffer, value);

        sink_iterator<Sink> sink_iterator(sink);

        if(align_ > buffer.size())
        {
            std::fill_n(sink_iterator, align_ - buffer.size(), pad_);
        }

        std::copy(std::begin(buffer), std::end(buffer), sink_iterator);
    }

private:
    std::size_t align_;
    char pad_;
};

struct max_width_inserter
{
    explicit max_width_inserter(std::size_t max_width) :
        max_width_(max_width)
    {
    }

    template <typename Sink, typename Value>
    void call(Sink& sink, Value const& value) const
    {
        limit_count_policy const policy(max_width_);

        sink_iterator<Sink, limit_count_policy> sink_iterator(sink, policy);

        type_adapter<Value>::format(sink_iterator, value);
    }

private:
    std::size_t max_width_;
};

struct repeat_inserter
{
    explicit repeat_inserter(std::size_t count) :
        count_(count)
    {
    }

    template <typename Sink, typename Value>
    void call(Sink& sink, Value const& value) const
    {
        for(std::size_t i = 0; i < count_; ++i)
        {
            type_adapter<Value>::format(sink, value);
        }
    }

private:
    std::size_t count_;
};

struct lower_case_inserter
{
    template <typename Sink, typename Value>
    static void call(Sink& sink, Value const& value)
    {
        sink_iterator<Sink, lower_case_policy> sink_iterator(sink);

        type_adapter<Value>::format(sink_iterator, value);
    }
};

struct upper_case_inserter
{
    template <typename Sink, typename Value>
    static void call(Sink& sink, Value const& value)
    {
        sink_iterator<Sink, upper_case_policy> sink_iterator(sink);

        type_adapter<Value>::format(sink_iterator, value);
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_type_inserter_hpp
