//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/detail/dispatch.hpp>
#include <missio/logging/factory.hpp>

// STL headers
#include <utility>


namespace missio
{
namespace logging
{
namespace detail
{

void dispatch(message&& message)
{
    factory::get_dispatcher().dispatch_message(std::forward<logging::message>(message));
}

}   // namespace detail
}   // namespace logging
}   // namespace missio
