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

    template <typename T>
    using enable_if_octet_container = detail::enable_if_octet_container<T>;

public:
    static binary from_base64_string(string const& str);
    static string to_base64_string(binary const& value);

public:
    binary() = default;
    ~binary() = default;

    binary(binary const&) = default;
    binary& operator=(binary const&) = default;

    binary(binary&&) = default;
    binary& operator=(binary&&) = default;

    binary(void const* data, std::size_t size);

    binary(std::vector<value_type>&& data);
    binary& operator=(std::vector<value_type>&& data);

    binary(std::initializer_list<value_type> data);
    binary& operator=(std::initializer_list<value_type> data);

    template <typename Container, typename = enable_if_octet_container<Container>>
    binary(Container const& container);

    template <typename Container, typename = enable_if_octet_container<Container>>
    binary& operator=(Container const& container);

    void assign(void const* data, std::size_t size);
    void append(void const* data, std::size_t size);

    void assign(std::initializer_list<value_type> data);
    void append(std::initializer_list<value_type> data);

    template <typename Container, typename = enable_if_octet_container<Container>>
    void assign(Container const& container);

    template <typename Container, typename = enable_if_octet_container<Container>>
    void append(Container const& container);

    void clear();

    bool empty() const;
    size_type size() const;

    const_pointer data() const;

    const_iterator begin() const;
    const_iterator end() const;

private:
    std::vector<value_type> data_;
};

// Implementation headers
#include <missio/json/binary.inl>

bool operator<(binary const& lhs, binary const& rhs);
bool operator==(binary const& lhs, binary const& rhs);
bool operator!=(binary const& lhs, binary const& rhs);

}   // namespace json
}   // namespace missio

#endif  // _missio_json_binary_hpp
