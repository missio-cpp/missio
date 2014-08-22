//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_string_view_hpp
#define _missio_format_detail_string_view_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// STL headers
#include <iostream>
#include <string>


namespace missio
{
namespace format
{
namespace detail
{

template <typename Char, typename Traits = std::char_traits<Char>>
class basic_string_view
{
public:
    typedef Char value_type;
    typedef std::size_t size_type;
    typedef Char const* pointer;
    typedef Char const* const_pointer;
    typedef Char const* iterator;
    typedef Char const* const_iterator;
    typedef Char const& reference;
    typedef Char const& const_reference;

public:
    basic_string_view() :
        data_(nullptr),
        size_(0u)
    {
    }

    basic_string_view(const_pointer data, size_type size) :
        data_(data),
        size_(size)
    {
    }

    basic_string_view(basic_string_view const&) = default;
    basic_string_view& operator=(basic_string_view const&) = default;

    basic_string_view(basic_string_view&&) = default;
    basic_string_view& operator=(basic_string_view&&) = default;

    const_iterator begin() const
    {
        return data_;
    }

    const_iterator end() const
    {
        return data_ + size_;
    }

    const_pointer data() const
    {
        return data_;
    }

    size_type size() const
    {
        return size_;
    }

private:
    pointer data_;
    size_type size_;
};

template <typename Char, typename Traits>
std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, basic_string_view<Char, Traits> const& str)
{
    os.write(str.data(), str.size());
    return os;
}

typedef basic_string_view<char> string_view;
typedef basic_string_view<wchar_t> wstring_view;
typedef basic_string_view<char16_t> u16string_view;
typedef basic_string_view<char32_t> u32string_view;

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_string_view_hpp
