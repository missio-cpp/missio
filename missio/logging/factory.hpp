//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_factory_hpp
#define _missio_logging_factory_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/logging/dispatcher.hpp>

// STL headers
#include <memory>


namespace missio
{
namespace logging
{

class factory
{
public:
    factory() = delete;
    ~factory() = delete;

    static void create_dispatcher();
    static void destroy_dispatcher();

    static dispatcher& get_dispatcher();

private:
    static std::unique_ptr<dispatcher> dispatcher_;
};

}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_factory_hpp
