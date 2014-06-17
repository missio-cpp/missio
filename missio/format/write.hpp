//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_write_hpp
#define _missio_format_write_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/format/detail/write_impl.hpp>


namespace missio
{
namespace format
{

template <typename Sink, typename ... Args>
void write(Sink& sink, Args const& ... args)
{
    detail::write(sink, args...);
}

}   // namespace format
}   // namespace missio

#endif  // _missio_format_write_hpp
