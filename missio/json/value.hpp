//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_value_hpp
#define _missio_json_value_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application header
#include <missio/json/types.hpp>
#include <missio/json/array.hpp>
#include <missio/json/object.hpp>
#include <missio/json/string.hpp>
#include <missio/json/exception.hpp>
#include <missio/json/detail/assign.hpp>
#include <missio/json/detail/convert.hpp>
#include <missio/json/detail/is_type.hpp>
#include <missio/json/detail/as_type.hpp>
#include <missio/json/detail/null_traits.hpp>
#include <missio/json/detail/type_traits.hpp>

// BOOST headers
#include <boost/variant.hpp>

// STL headers
#include <type_traits>
#include <utility>


namespace missio
{
namespace json
{

class value
{
public:
    typedef boost::variant<
        null,
        real,
        integer,
        boolean,
        string,
        boost::recursive_wrapper<array>,
        boost::recursive_wrapper<object>
    > variant_type;

public:
    typedef variant_type::types types;

    template <typename T>
    using is_value = typename std::is_same<detail::remove_ref_const<T>, value>::type;

    template <typename T>
    using enable_if_not_value = typename std::enable_if<!is_value<T>::value>::type;

public:
    value() = default;
    ~value() = default;

    value(value const&) = default;
    value& operator=(value const&) = default;

    value(value&&) = default;
    value& operator=(value&&) = default;

    template <typename T, typename Enable = enable_if_not_value<T>>
    value(T const& value);

    template <typename T, typename Enable = enable_if_not_value<T>>
    value& operator=(T const& value);

    template <typename T, typename Enable = enable_if_not_value<T>>
    value(T&& value);

    template <typename T, typename Enable = enable_if_not_value<T>>
    value& operator=(T&& value);

    template <typename T> bool is() const;

    template <typename T> T as() const;

    template <typename T> T& get();
    template <typename T> T const& get() const;

    template <typename T> operator T() const;
    template <typename T> operator T const&() const;

    variant_type const& variant() const;

    value& operator[](std::size_t index);
    value const& operator[](std::size_t index) const;

    value& operator[](string const& key);
    value const& operator[](string const& key) const;

    friend bool operator==(value const& lhs, value const& rhs);
    friend bool operator<(value const& lhs, value const& rhs);

private:
    variant_type variant_;
};

// Implementation headers
#include <missio/json/value.inl>

inline bool operator!=(value const& lhs, value const& rhs) { return !operator==(lhs, rhs); }
inline bool operator<=(value const& lhs, value const& rhs) { return !operator<(rhs, lhs); }
inline bool operator>=(value const& lhs, value const& rhs) { return !operator<(lhs, rhs); }
inline bool operator>(value const& lhs, value const& rhs) { return operator<(rhs, lhs); } 

}   // namespace json
}   // namespace missio

#endif  // _missio_json_value_hpp
