//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_array_hpp
#define _missio_json_array_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/types.hpp>
#include <missio/json/value.hpp>

// STL headers
#include <vector>


namespace missio
{
namespace json
{

class array
{
public:
    typedef value value_type;
    typedef std::vector<value_type>::size_type size_type;
    typedef std::vector<value_type>::iterator iterator;
    typedef std::vector<value_type>::const_iterator const_iterator;

public:
    array() = default;

    array(array const&) = default;
    array& operator=(array const&) = default;

    array(array&&) = default;
    array& operator=(array&&) = default;

    bool empty() const;
    void clear();

    std::size_t size() const;
    void resize(std::size_t size);

    std::size_t capacity() const;
    void reserve(std::size_t size);

    void grow(std::size_t size);
    void shrink(std::size_t size);

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    value& front();
    value const& front() const;

    value& back();
    value const& back() const;

    void push_back(value&& value);
    void push_back(value const& value);

    void pop_back();

    void erase(iterator position);
    void erase(iterator first, iterator last);

    void insert(iterator position, value&& value);
    void insert(iterator position, value const& value);

    value& operator[](std::size_t index);
    value const& operator[](std::size_t index) const;

    friend bool operator==(array const& lhs, array const& rhs);
    friend bool operator<(array const& lhs, array const& rhs);

private:
    std::vector<value_type> values_;
};

inline bool operator!=(array const& lhs, array const& rhs) { return !operator==(lhs, rhs); }
inline bool operator<=(array const& lhs, array const& rhs) { return !operator<(rhs, lhs); }
inline bool operator>=(array const& lhs, array const& rhs) { return !operator<(lhs, rhs); }
inline bool operator>(array const& lhs, array const& rhs) { return operator<(rhs, lhs); }

}   // namespace json
}   // namespace missio

#endif  // _missio_json_array_hpp
