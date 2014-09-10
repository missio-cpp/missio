//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_console_writer_hpp
#define _missio_logging_console_writer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/logging/writer_options.hpp>
#include <missio/logging/writer_base.hpp>
#include <missio/logging/message.hpp>

// STL headers
#include <string>


namespace missio
{
namespace logging
{

class console_options;

class console_writer : public writer_base
{
public:
    explicit console_writer(console_options const& options);
    virtual ~console_writer() = default;

protected:
    void write_impl(message const& message) override;
    void flush_impl() override;
};

class console_options : public basic_options<console_writer, console_options>
{
friend class console_writer;

public:
    explicit console_options(severity severity);

    console_options(console_options const&) = default;
    console_options& operator=(console_options const&) = delete;
};

}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_console_writer_hpp
