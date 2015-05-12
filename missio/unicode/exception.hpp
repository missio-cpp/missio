//---------------------------------------------------------------------------
//
//    This file is part of Missio.Unicode library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_unicode_exception_hpp
#define _missio_unicode_exception_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Common headers
#include <missio/common/export.hpp>

// STL headers
#include <exception>
#include <cstdint>
#include <string>


namespace missio
{
namespace unicode
{

class MISSIO_EXPORT exception : public std::exception
{
public:
    exception() = default;

    virtual std::string message() const;
};

class MISSIO_EXPORT input_underflow_error : public exception
{
public:
    input_underflow_error() = default;

    char const* what() const noexcept override;
};

class MISSIO_EXPORT invalid_utf32_code_point : public exception
{
public:
    explicit invalid_utf32_code_point(std::uint32_t code_point);

    std::uint32_t code_point() const noexcept;

    char const* what() const noexcept override;

    std::string message() const override;

private:
    std::uint32_t code_point_;
};

class MISSIO_EXPORT invalid_utf16_code_unit : public exception
{
public:
    explicit invalid_utf16_code_unit(std::uint16_t code_unit);

    std::uint16_t code_unit() const noexcept;

    char const* what() const noexcept override;

    std::string message() const override;

private:
    std::uint16_t code_unit_;
};

class MISSIO_EXPORT invalid_utf8_sequence : public exception
{
public:
    template <typename OctetIterator>
    invalid_utf8_sequence(OctetIterator begin, OctetIterator end) :
        invalid_utf8_sequence(std::string(begin, end))
    {
    }

    explicit invalid_utf8_sequence(std::string const& sequence);

    std::string const& sequence() const noexcept;

    char const* what() const noexcept override;

    std::string message() const override;

private:
    std::string sequence_;
};

}   // namespace unicode
}   // namespace missio

#endif  // _missio_unicode_exception_hpp
