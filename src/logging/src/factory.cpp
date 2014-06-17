//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/factory.hpp>


namespace missio
{
namespace logging
{

std::unique_ptr<dispatcher> factory::dispatcher_;

void factory::create_dispatcher()
{
    if(!dispatcher_)
        dispatcher_.reset(new dispatcher);
}

void factory::destroy_dispatcher()
{
    dispatcher_.reset();
}

dispatcher& factory::get_dispatcher()
{
    return *dispatcher_;
}

}   // namespace logging
}   // namespace missio
