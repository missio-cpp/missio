//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/syslog_writer.hpp>

#if defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L)

// POSIX headers
#include <syslog.h>


namespace missio
{
namespace logging
{

syslog_writer::syslog_writer(syslog_writer_options const& optins) :
    writer_base(options),
    ident_(options.ident_)
{
    ::openlog(ident_.c_str(), LOG_PID, LOG_USER);
}

syslog_writer::~syslog_writer() noexcept
{
    ::closelog();
}

void syslog_writer::write_impl(message const& message)
{
    sink_.erase();
    format(sink_, message);

    int const level = get_level(message);

    ::syslog(level, "%s", sink_.c_str());
}

void syslog_writer::flush_impl()
{
}

int syslog_writer::get_level(message const& message)
{
    switch(message.severity())
    {
        case failure: return LOG_CRIT;
        case error:   return LOG_ERR;
        case warning: return LOG_WARNING;
        case notice:  return LOG_NOTICE;
        case info:    return LOG_INFO;
        case debug:   return LOG_DEBUG;
    }

    return LOG_DEBUG;
}

syslog_options::syslog_options(severity severity) :
    basic_options(severity)
{
}

syslog_options& syslog_options::ident(std::string const& ident)
{
    ident_ = ident;
    return self();
}

}   // namespace logging
}   // namespace missio

#endif  // defined(_POSIX_VERSION) && (_POSIX_VERSION >= 200112L)
