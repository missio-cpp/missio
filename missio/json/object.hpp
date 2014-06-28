//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_object_hpp
#define _missio_json_object_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/types.hpp>
#include <missio/json/value.hpp>

// STL headers
#include <utility>
#include <vector>


namespace missio
{
namespace json
{

class object
{
public:
    typedef std::pair<string, value> value_type;
    typedef std::vector<value_type>::size_type size_type;
    typedef std::vector<value_type>::iterator iterator;
    typedef std::vector<value_type>::const_iterator const_iterator;

public:
    object();
    ~object();

    object(object&& other);
    object& operator=(object&& other);

    object(object const& other);
    object& operator=(object const& other);

    bool empty() const;
    std::size_t size() const;

    iterator begin();
    const_iterator begin() const;

    iterator end();
    const_iterator end() const;

    iterator find(string const& key);
    const_iterator find(string const& key) const;

    bool contains(string const& key) const;

    void clear();

    void erase(iterator position);
    void erase(iterator first, iterator last);
    void erase(string const& key);

    bool insert(iterator position, value_type const& value);
    bool insert(string const& key, value const& value);

    value& operator[](string const& key);
    value const& operator[](string const& key) const;

    friend bool operator==(object const& lhs, object const& rhs);
    friend bool operator<(object const& lhs, object const& rhs);

private:
    std::vector<value_type> values_;
};

inline bool operator!=(object const& lhs, object const& rhs) { return !operator==(lhs, rhs); }
inline bool operator<=(object const& lhs, object const& rhs) { return !operator<(rhs, lhs); }
inline bool operator>=(object const& lhs, object const& rhs) { return !operator<(lhs, rhs); }
inline bool operator>(object const& lhs, object const& rhs) { return operator<(rhs, lhs); }

}   // namespace json
}   // namespace missio

#endif  // _missio_json_object_hpp