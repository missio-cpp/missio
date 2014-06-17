//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/writer_options.hpp>
#include <missio/logging/factory.hpp>


namespace missio
{
namespace logging
{

options_base::options_base(severity severity) :
    severity_(severity),
    format_("%Message%")
{
}

void options_base::add_writer(writer_base::pointer writer)
{
    factory::get_dispatcher().add_writer(writer);
}

}   // namespace logging
}   // namespace missio
