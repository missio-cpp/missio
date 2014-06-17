//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_type_inserter_hpp
#define _missio_format_detail_type_inserter_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Applciation headers
#include <missio/format/detail/repeat_directive.hpp>
#include <missio/format/detail/generate_value.hpp>
#include <missio/format/detail/type_generator.hpp>
#include <missio/format/detail/real_generator.hpp>
#include <missio/format/detail/int_generator.hpp>
#include <missio/format/detail/format_value.hpp>

// BOOST headers
#include <boost/spirit/include/karma.hpp>


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
        int_generator<Value, Radix> const& generator(make_generator<Value>());
        generate_value(sink, value, generator(precision_, force_sign_, upper_case_));
    }

private:
    template <typename Value>
    static int_generator<Value, Radix> const& make_generator()
    {
        static int_generator<Value, Radix> const generator;
        return generator;
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
        generate_value(sink, value, make_generator<Value>(precision_, force_sign_, upper_case_));
    }

private:
    template <typename Value>
    static typename real_generator<Value, Format>::type make_generator(int precision, bool force_sign, bool upper_case)
    {
        return real_generator<Value, Format>::make(precision, force_sign, upper_case);
    }

private:
    int precision_;
    bool force_sign_;
    bool upper_case_;
};

struct align_inserter
{
    explicit align_inserter(int align) :
        align_(align)
    {
    }

    template <typename Sink, typename Value>
    void call(Sink& sink, Value const& value) const
    {
        sink_buffer buffer;

        format_value(buffer, value);

        call(sink, buffer, type_generator<sink_buffer>::get());
    }

    template <typename Sink, typename Value, typename Generator>
    void call(Sink& sink, Value const& value, Generator const& generator) const
    {
        if(align_ > 0)
            generate_value(sink, value, boost::spirit::karma::right_align(align_)[generator]);
        else
            generate_value(sink, value, boost::spirit::karma::left_align(-align_)[generator]);
    }

private:
    int align_;
};

struct repeat_inserter
{
    explicit repeat_inserter(unsigned int count) :
        count_(count)
    {
    }

    template <typename Sink, typename Value>
    void call(Sink& sink, Value const& value) const
    {
        sink_buffer buffer;

        format_value(buffer, value);

        call(sink, buffer, type_generator<sink_buffer>::get());
    }

    template <typename Sink, typename Value, typename Generator>
    void call(Sink& sink, Value const& value, Generator const& generator) const
    {
        generate_value(sink, value, repeat_directive(count_)[generator]);
    }

private:
    unsigned int count_;
};

struct lower_case_inserter
{
    template <typename Sink, typename Value>
    static void call(Sink& sink, Value const& value)
    {
        call(sink, value, type_generator<Value>::get());
    }

    template <typename Sink, typename Value, typename Generator>
    static void call(Sink& sink, Value const& value, Generator const& generator)
    {
        generate_value(sink, value, boost::spirit::karma::lower[generator]);
    }
};

struct upper_case_inserter
{
    template <typename Sink, typename Value>
    static void call(Sink& sink, Value const& value)
    {
        call(sink, value, type_generator<Value>::get());
    }

    template <typename Sink, typename Value, typename Generator>
    static void call(Sink& sink, Value const& value, Generator const& generator)
    {
        generate_value(sink, value, boost::spirit::karma::upper[generator]);
    }
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_type_inserter_hpp
