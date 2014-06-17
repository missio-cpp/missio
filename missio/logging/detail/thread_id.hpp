//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_detail_thread_id_hpp
#define _missio_logging_detail_thread_id_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)


namespace missio
{
namespace logging
{
namespace detail
{

class thread_id
{
public:
    thread_id();

    thread_id(thread_id const&) = default;
    thread_id& operator=(thread_id const&) = default;

    unsigned long value() const;

private:
    static unsigned long get_current_thread_id();

private:
    unsigned long value_;
};

}   // namespace detail
}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_detail_thread_id_hpp
