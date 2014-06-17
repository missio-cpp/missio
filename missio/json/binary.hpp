//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
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
    binary();

    explicit binary(std::vector<unsigned char>&& data);
    explicit binary(std::vector<unsigned char> const& data);

    binary(unsigned char const* data, std::size_t size);

    binary(binary&& other);
    binary& operator=(binary&& other);

    binary(binary const& other);
    binary& operator=(binary const& other);

    void assign(std::vector<unsigned char> const& data);
    void append(std::vector<unsigned char> const& data);

    void assign(unsigned char const* data, std::size_t size);
    void append(unsigned char const* data, std::size_t size);

    void clear();

    bool empty() const;
    std::size_t size() const;

    std::vector<unsigned char> const& data() const;

    friend bool operator<(binary const& lhs, binary const& rhs);
    friend bool operator==(binary const& lhs, binary const& rhs);

private:
    std::vector<unsigned char> data_;
};

inline bool operator!=(binary const& lhs, binary const& rhs) { return !operator==(lhs, rhs); }
inline bool operator<=(binary const& lhs, binary const& rhs) { return !operator<(rhs, lhs); }
inline bool operator>=(binary const& lhs, binary const& rhs) { return !operator<(lhs, rhs); }
inline bool operator>(binary const& lhs, binary const& rhs) { return operator<(rhs, lhs); } 

}   // namespace json
}   // namespace missio

#endif  // _missio_json_binary_hpp
