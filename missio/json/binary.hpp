//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_binary_hpp
#define _missio_json_binary_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/detail/container_traits.hpp>
#include <missio/json/string.hpp>

// STL headers
#include <initializer_list>
#include <cstdint>
#include <vector>


namespace missio
{
namespace json
{

class binary
{
public:
    typedef std::uint8_t value_type;
    typedef std::vector<value_type>::size_type size_type;
    typedef std::vector<value_type>::pointer pointer;
    typedef std::vector<value_type>::const_pointer const_pointer;
    typedef std::vector<value_type>::iterator iterator;
    typedef std::vector<value_type>::const_iterator const_iterator;

public:
    static binary from_base64_string(string const& str);
    static string to_base64_string(binary const& value);

public:
    binary() = default;
    ~binary() = default;

    binary(std::vector<std::uint8_t>&& data);

    binary(std::initializer_list<std::uint8_t> data);
    binary& operator=(std::initializer_list<std::uint8_t> data);

    template <typename T>
    binary(T const& data, detail::enable_if_char_container<T> const* = nullptr);

    template <typename T>
    binary(T const* data, std::size_t size, detail::enable_if_char_type<T> const* = nullptr);

    binary(binary const&) = default;
    binary& operator=(binary const&) = default;

    binary(binary&&) = default;
    binary& operator=(binary&&) = default;

    void assign(std::initializer_list<std::uint8_t> data);
    void append(std::initializer_list<std::uint8_t> data);

    template <typename T>
    void assign(T const& data, detail::enable_if_char_container<T> const* = nullptr);

    template <typename T>
    void append(T const& data, detail::enable_if_char_container<T> const* = nullptr);

    template <typename T>
    void assign(T const* data, std::size_t size, detail::enable_if_char_type<T> const* = nullptr);

    template <typename T>
    void append(T const* data, std::size_t size, detail::enable_if_char_type<T> const* = nullptr);

    void clear();

    bool empty() const;
    std::size_t size() const;

    std::uint8_t const* data() const;

    const_iterator begin() const;
    const_iterator end() const;

    friend bool operator<(binary const& lhs, binary const& rhs);
    friend bool operator==(binary const& lhs, binary const& rhs);

private:
    std::vector<std::uint8_t> data_;
};

// Implementation headers
#include <missio/json/binary.inl>

inline bool operator!=(binary const& lhs, binary const& rhs) { return !operator==(lhs, rhs); }
inline bool operator<=(binary const& lhs, binary const& rhs) { return !operator<(rhs, lhs); }
inline bool operator>=(binary const& lhs, binary const& rhs) { return !operator<(lhs, rhs); }
inline bool operator>(binary const& lhs, binary const& rhs) { return operator<(rhs, lhs); } 

}   // namespace json
}   // namespace missio

#endif  // _missio_json_binary_hpp
