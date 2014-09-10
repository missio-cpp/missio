//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_writer_base_hpp
#define _missio_logging_writer_base_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/logging/message.hpp>
#include <missio/format/string.hpp>

// STL headers
#include <memory>
#include <string>


namespace missio
{
namespace logging
{

class options_base;

class writer_base
{
public:
    typedef std::shared_ptr<writer_base> pointer;

public:
    explicit writer_base(options_base const& options);
    virtual ~writer_base() = default;

    writer_base(writer_base const&) = delete;
    writer_base& operator=(writer_base const&) = delete;

    void write(message const& message) noexcept;
    void flush() noexcept;

protected:
    virtual void write_impl(message const& message) = 0;
    virtual void flush_impl() = 0;

protected:
    template <typename Sink>
    void format(Sink& sink, message const& message) const;

private:
    static std::string parse(std::string const& format);

private:
    severity const severity_;
    format::string const format_;
};

template <typename Sink>
void writer_base::format(Sink& sink, message const& message) const
{
    message.format(sink, format_);
}

}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_writer_base_hpp
