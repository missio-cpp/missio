//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_reference_hpp
#define _missio_json_reference_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// Application headers
#include <missio/json/value.hpp>


namespace missio
{
namespace json
{

template <typename T>
class reference
{
friend class reference<T const>;

public:
    reference(reference<T>& other) :
        value_(other.value_)
    {
    }

    reference(value& value) :
        value_(value.get<T>())
    {
    }

    reference(T& value) :
        value_(value)
    {
    }

    operator T&()
    {
        return value_;
    }

    operator T const&() const
    {
        return value_;
    }

    T* operator->()
    {
        return &value_;
    }

    T const* operator->() const
    {
        return &value_;
    }

    template <typename Key>
    value& operator[](Key const& key)
    {
        return value_[key];
    }

    template <typename Key>
    value const& operator[](Key const& key) const
    {
        return value_[key];
    }

private:
    // prevent MSVC warning C4512: assignment operator could not be generated
    reference& operator=(reference const& other);

private:
    T& value_;
};

template <typename T>
class reference<T const>
{
public:
    reference(reference<T const> const& other) :
        value_(other.value_)
    {
    }

    reference(reference<T> const& other) :
        value_(other.value_)
    {
    }

    reference(value const& value) :
        value_(value.get<T>())
    {
    }

    reference(T const& value) :
        value_(value)
    {
    }

    operator T const&() const
    {
        return value_;
    }

    T const* operator->() const
    {
        return &value_;
    }

    template <typename Key>
    value const& operator[](Key const& key) const
    {
        return value_[key];
    }

private:
    // prevent MSVC warning C4512: assignment operator could not be generated
    reference& operator=(reference const& other);

private:
    T const& value_;
};

}   // namespace json
}   // namespace missio

#endif  // _missio_json_reference_hpp
