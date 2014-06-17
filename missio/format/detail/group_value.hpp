//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012 Ilya Golovenko
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

    Value const& value() const
    {
        return value_;
    }

    Inserter const& inserter() const
    {
        return inserter_;
    }

private:
    // prevent MSVC warning C4512: assignment operator could not be generated
    group_value& operator=(group_value const& other);

private:
    Value const& value_;
    Inserter inserter_;
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_group_value_hpp
