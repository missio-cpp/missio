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

// STL headers
#include <exception>
#include <cstdint>
#include <string>


namespace missio
{
namespace unicode
{

class exception : public std::exception
{
public:
    exception() = default;

    virtual std::string message() const;
};

class input_underflow_error : public exception
{
public:
    input_underflow_error() = default;

    virtual char const* what() const throw();
};

class invalid_utf32_code_point : public exception
{
public:
    explicit invalid_utf32_code_point(std::uint32_t code_point);

    std::uint32_t code_point() const throw();

    virtual char const* what() const throw();

    virtual std::string message() const;

private:
    std::uint32_t code_point_;
};

class invalid_utf16_code_unit : public exception
{
public:
    explicit invalid_utf16_code_unit(std::uint16_t code_unit);

    std::uint16_t code_unit() const throw();

    virtual char const* what() const throw();

    virtual std::string message() const;

private:
    std::uint16_t code_unit_;
};

class invalid_utf8_sequence : public exception
{
public:
    template <typename OctetIterator>
    invalid_utf8_sequence(OctetIterator begin, OctetIterator end) :
        invalid_utf8_sequence(std::string(begin, end))
    {
    }

    explicit invalid_utf8_sequence(std::string const& sequence);

    std::string const& sequence() const throw();

    virtual char const* what() const throw();

    virtual std::string message() const;

private:
    std::string sequence_;
};

}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_exception_hpp
