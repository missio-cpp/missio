//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_print_hpp
#define _missio_format_print_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/print_impl.hpp>


namespace missio
{
namespace format
{

template <typename Sink, typename Format, typename ... Args>
void print(Sink& sink, Format const& format, Args const& ... args)
{
    detail::print(sink, format, args...);
}

}   // namespace format
}   // namespace missio

#endif  // _missio_format_print_hpp
