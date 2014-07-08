//---------------------------------------------------------------------------
//
//    This file is part of Missio.Logging library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------

// Application headers
#include <missio/logging/writer_base.hpp>
#include <missio/logging/writer_options.hpp>

// BOOST headers
#include <boost/algorithm/string.hpp>


namespace missio
{
namespace logging
{

writer_base::writer_base(options_base const& options) :
    severity_(options.severity_),
    format_(parse(options.format_))
{
}

writer_base::~writer_base() throw()
{
}

void writer_base::write(message const& message) throw()
{
    if(message.get_severity() <= severity_)
    {
        try
        {
            write_impl(message);
        }
        catch(...)
        {
        }
    }
}

void writer_base::flush() throw()
{
    try
    {
        flush_impl();
    }
    catch(...)
    {
    }
}

std::string writer_base::parse(std::string const& format)
{
    std::string result(format);

    boost::algorithm::ireplace_all(result, "%MessageID%", "{0}");
    boost::algorithm::ireplace_all(result, "%TimeStamp%", "{1}");
    boost::algorithm::ireplace_all(result, "%Severity%",  "{2}");
    boost::algorithm::ireplace_all(result, "%ProcessID%", "{3}");
    boost::algorithm::ireplace_all(result, "%ThreadID%",  "{4}");
    boost::algorithm::ireplace_all(result, "%Component%", "{5}");
    boost::algorithm::ireplace_all(result, "%Function%",  "{6}");
    boost::algorithm::ireplace_all(result, "%File%",      "{7}");
    boost::algorithm::ireplace_all(result, "%Line%",      "{8}");
    boost::algorithm::ireplace_all(result, "%Message%",   "{9}");

    return result;
}

}   // namespace logging
}   // namespace missio
