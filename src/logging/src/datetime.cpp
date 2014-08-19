//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/datetime.hpp>


namespace missio
{
namespace logging
{
namespace detail
{

static char const* const month_names[12] =
{
    "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
}

char const* datetime::get_month_name() const
{
    return 1 <= month && month <= 12 ? month_names[month - 1] : "";
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
