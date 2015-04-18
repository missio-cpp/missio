//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_syslog_writer_hpp
#define _missio_logging_syslog_writer_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/logging/writer_options.hpp>
#include <missio/logging/writer_base.hpp>
#include <missio/logging/message.hpp>

#if defined(__unix__) || defined(__unix)

// Unix headers
#include <unistd.h>

#endif

#if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L)

// STL headers
#include <string>


namespace missio
{
namespace logging
{

class syslog_options;

class syslog_writer : public writer_base
{
public:
    explicit syslog_writer(syslog_options const& optins);
    virtual ~syslog_writer() noexcept;

    syslog_writer(syslog_writer const&) = delete;
    syslog_writer& operator=(syslog_writer const&) = delete;

protected:
    void write_impl(message const& message) override;
    void flush_impl() override;

private:
    static int get_level(message const& message);

private:
    std::string sink_;
    std::string ident_;
};

class syslog_options : public basic_options<syslog_writer, syslog_options>
{
friend class syslog_writer;

public:
    explicit syslog_options(severity severity);

    syslog_options(syslog_options const&) = default;
    syslog_options& operator=(syslog_options const&) = delete;

    syslog_options& ident(std::string const& ident);

private:
    std::string ident_;
};

}   // namespace logging
}   // namespace missio

#endif  // defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L)

#endif  // _missio_logging_syslog_writer_hpp
