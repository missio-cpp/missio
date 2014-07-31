//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_group_value_hpp
#define _missio_format_detail_group_value_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)


namespace missio
{
namespace format
{
namespace detail
{

template <typename Value, typename Inserter>
struct group_value
{
    group_value(Value const& value, Inserter const& inserter) :
        value_(value),
        inserter_(inserter)
    {
    }

    explicit group_value(Value const& value) :
        value_(value)
    {
    }

    group_value(group_value const&) = delete;
    group_value& operator=(group_value const&) = delete;

    group_value(group_value&&) = default;
    group_value& operator=(group_value&&) = default;

    Value const& value() const
    {
        return value_;
    }

    Inserter const& inserter() const
    {
        return inserter_;
    }

private:
    Value const& value_;
    Inserter inserter_;
};

template <typename Value, typename Inserter>
auto make_group_value(Value const& value, Inserter const& inserter)
{
    return group_value<Value, Inserter>(value, inserter);
}

template <typename Inserter, typename Value>
auto make_group_value(Value const& value)
{
    return group_value<Value, Inserter>(value);
}

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_group_value_hpp
