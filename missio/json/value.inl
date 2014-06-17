//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------


template <typename T>
inline value::value(T const& value)
{
    assign(value);
}

template <typename T>
inline value& value::operator=(T const& value)
{
    assign(value);
    return *this;
}

template <typename T>
inline void value::assign(T const& value)
{
    detail::assign<T>::call(variant_, value);
}

template <typename T>
inline bool value::is() const
{
    return detail::is_type<T>::call(variant_);
}

template <typename T>
inline T value::as() const
{
    return detail::as_type<T>::call(variant_);
}

template <typename T>
inline value::operator T() const
{
    return as<T>();
}

template <typename T>
inline T& value::get()
{
    detail::convert<T>::call(variant_);
    return boost::get<T>(variant_);
}

template <typename T>
inline T const& value::get() const
{
    T const* value = boost::get<T>(&variant_);

    if(!value)
        throw exception("invalid value type");

    return *value;
}
