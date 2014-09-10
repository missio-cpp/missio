//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/console_writer.hpp>

// STL headers
#include <functional>
#include <iostream>
#include <memory>


namespace missio
{
namespace logging
{

console_writer::console_writer(console_options const& options) :
    writer_base(options)
{
}

void console_writer::write_impl(message const& message)
{
    format(std::clog, message);
}

void console_writer::flush_impl()
{
    std::clog.flush();
}

console_options::console_options(severity severity) :
    basic_options(severity)
{
}

}   // namespace logging
}   // namespace missio
