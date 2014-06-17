//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_exception_hpp
#define _missio_unicode_exception_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/unicode/impl/common.hpp>

// STL headers
#include <exception>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <string>
#include <array>


namespace missio
{
namespace unicode
{

class exception : public std::exception
{
public:
    exception() = default;

    virtual std::string message() const
    {
        return std::string(what());
    }
};

class input_underflow_error : public exception
{
public:
    input_underflow_error() = default;

    virtual char const* what() const throw()
    {
        return "input underflow error";
    }
};

class invalid_utf32_code_point : public exception
{
public:
    template <typename UTF32>
    explicit invalid_utf32_code_point(UTF32 code_point) :
        code_point_(impl::make_uint32(code_point))
    {
    }

    virtual char const* what() const throw()
    {
        return "invalid UTF-32 code point";
    }

    std::uint32_t code_point() const throw()
    {
        return code_point_;
    }

    virtual std::string message() const
    {
        std::ostringstream os;

        os << what()
           << ": \\U"
           << std::hex
           << std::setw(8)
           << std::setfill('0')
           << std::uppercase
           << code_point_;

        return os.str();
    }

private:
    std::uint32_t code_point_;
};

class invalid_utf16_code_unit : public exception
{
public:
    template <typename UTF16>
    explicit invalid_utf16_code_unit(UTF16 code_unit) :
        code_unit_(impl::make_uint16(code_unit))
    {
    }

    virtual char const* what() const throw()
    {
        return "invalid or unexpected UTF-16 code unit";
    }

    std::uint16_t code_unit() const throw()
    {
        return code_unit_;
    }

    virtual std::string message() const
    {
        std::ostringstream os;

        os << what()
           << ": \\u"
           << std::hex
           << std::setw(4)
           << std::setfill('0')
           << std::uppercase
           << code_unit_;

        return os.str();
    }

private:
    std::uint16_t code_unit_;
};

class invalid_utf8_sequence : public exception
{
public:
    typedef std::array<std::uint8_t, 4> sequence_type;

public:
    template <typename OctetIterator>
    invalid_utf8_sequence(OctetIterator begin, OctetIterator end) :
        sequence_size_(0)
    {
        while(begin != end && sequence_size_ < sequence_.size())
        {
            sequence_[sequence_size_++] = impl::make_uint8(*begin++);
        }
    }

    virtual char const* what() const throw()
    {
        return "invalid UTF-8 sequence";
    }

    sequence_type const& sequence() const throw()
    {
        return sequence_;
    }

    std::size_t sequence_size() const throw()
    {
        return sequence_size_;
    }

    virtual std::string message() const
    {
        std::ostringstream os;

        os << what();

        if(sequence_size_ > 0)
        {
            os << ": "
               << std::hex
               << std::setw(2)
               << std::setfill('0')
               << std::uppercase;

            for(std::size_t i = 0; i < sequence_size_; ++i)
            {
                os << "\\x" << static_cast<std::size_t>(sequence_[i]);
            }
        }

        return os.str();
    }

private:
    sequence_type sequence_;
    std::size_t sequence_size_;
};

}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_exception_hpp
