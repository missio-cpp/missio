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
#include <missio/json/string.hpp>

// STL headers
#include <cstdint>
#include <vector>


namespace missio
{
namespace json
{

class binary
{
public:
    static binary from_base64_string(string const& str);
    static string to_base64_string(binary const& value);

public:
    binary() = default;

    binary(std::initializer_list<std::uint8_t> data);
    binary(std::uint8_t const* data, std::size_t size);

    template <std::size_t N>
    explicit binary(std::uint8_t const* (&data)[N]);

    template <template <typename ...> class Container, typename ... Args>
    explicit binary(Container<std::uint8_t, Args...> const& data);

    binary(binary const&) = default;
    binary& operator=(binary const&) = default;

    binary(binary&&) = default;
    binary& operator=(binary&&) = default;

    void assign(std::uint8_t const* data, std::size_t size);
    void append(std::uint8_t const* data, std::size_t size);

    template <std::size_t N>
    void assign(std::uint8_t const* (&data)[N]);

    template <std::size_t N>
    void append(std::uint8_t const* (&data)[N]);

    void clear();

    bool empty() const;
    std::size_t size() const;

    std::uint8_t const* data() const;

    friend bool operator<(binary const& lhs, binary const& rhs);
    friend bool operator==(binary const& lhs, binary const& rhs);

private:
    std::vector<std::uint8_t> data_;
};

template <std::size_t N>
binary::binary(std::uint8_t const* (&data)[N]) : binary(data, N)
{
}

template <template <typename ...> class Container, typename ... Args>
binary::binary(Container<std::uint8_t, Args...> const& data) : binary(data.data(), data.size())
{
}

template <std::size_t N>
void binary::assign(std::uint8_t const* (&data)[N])
{
    assign(data, N);
}

template <std::size_t N>
void binary::append(std::uint8_t const* (&data)[N])
{
    append(data, N);
}

inline bool operator!=(binary const& lhs, binary const& rhs) { return !operator==(lhs, rhs); }
inline bool operator<=(binary const& lhs, binary const& rhs) { return !operator<(rhs, lhs); }
inline bool operator>=(binary const& lhs, binary const& rhs) { return !operator<(lhs, rhs); }
inline bool operator>(binary const& lhs, binary const& rhs) { return operator<(rhs, lhs); } 

}   // namespace json
}   // namespace missio

#endif  // _missio_json_binary_hpp
