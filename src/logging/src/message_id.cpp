//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/message_id.hpp>

// STL headers
#include <atomic>


namespace missio
{
namespace logging
{
namespace detail
{

static std::atomic<std::uint64_t> counter(1);

message_id::message_id() :
    value_(counter.fetch_add(1))
{
}

std::uint64_t message_id::value() const
{
    return value_;
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
