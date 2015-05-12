//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_detail_message_id_hpp
#define _missio_logging_detail_message_id_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

// STL headers
#include <cstdint>


namespace missio
{
namespace logging
{
namespace detail
{

class MISSIO_EXPORT message_id
{
public:
    message_id();

    message_id(message_id const&) = default;
    message_id& operator=(message_id const&) = default;

    std::uint64_t value() const;

private:
    std::uint64_t value_;
};

}   // namespace detail
}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_detail_message_id_hpp
