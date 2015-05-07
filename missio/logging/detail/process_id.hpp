//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_detail_process_id_hpp
#define _missio_logging_detail_process_id_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>


namespace missio
{
namespace logging
{
namespace detail
{

class MISSIO_EXPORT process_id
{
public:
    process_id();

    process_id(process_id const&) = default;
    process_id& operator=(process_id const&) = default;

    unsigned long value() const;

private:
    static unsigned long get_current_process_id();

private:
    unsigned long value_;
};

}   // namespace detail
}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_detail_process_id_hpp
