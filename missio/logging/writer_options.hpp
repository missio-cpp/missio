//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_logging_writer_options_hpp
#define _missio_logging_writer_options_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

// Application headers
#include <missio/logging/writer_base.hpp>
#include <missio/logging/severity.hpp>

// STL headers
#include <memory>
#include <string>


namespace missio
{
namespace logging
{

class MISSIO_EXPORT options_base
{
friend class writer_base;

public:
    explicit options_base(severity severity);

    options_base(options_base const&) = default;
    options_base& operator=(options_base const&) = delete;

protected:
    void add_writer(writer_base::pointer writer);

protected:
    severity severity_;
    std::string format_;
};

template <typename Writer, typename Options>
class basic_options : public options_base
{
public:
    explicit basic_options(severity severity);

    basic_options(basic_options const&) = default;
    basic_options& operator=(basic_options const&) = delete;

    Options& format(std::string const& format);

    void add_writer();

protected:
    Options& self();
};

template <typename Writer, typename Options>
basic_options<Writer, Options>::basic_options(severity severity) :
    options_base(severity)
{
}

template <typename Writer, typename Options>
Options& basic_options<Writer, Options>::format(std::string const& format)
{
    format_ = format;
    return self();
}

template <typename Writer, typename Options>
void basic_options<Writer, Options>::add_writer()
{
    options_base::add_writer(std::make_shared<Writer>(self()));
}

template <typename Writer, typename Options>
Options& basic_options<Writer, Options>::self()
{
    return static_cast<Options&>(*this);
}

}   // namespace logging
}   // namespace missio

#endif  // _missio_logging_writer_options_hpp
