//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------


template <typename T> value::value(T const& value)
{
    detail::assign_value_to_variant(variant_, value);
}

template <typename T> value& value::operator=(T const& value)
{
    detail::assign_value_to_variant(variant_, value);
    return *this;
}

template <typename T> value::value(T&& value)
{
    detail::assign_value_to_variant(variant_, value);
}

template <typename T> value& value::operator=(T&& value)
{
    detail::assign_value_to_variant(variant_, value);
    return *this;
}

template <typename T> bool value::is() const
{
    return detail::is_type<T>::call(variant_);
}

template <typename T> T value::as() const
{
    return detail::as_type<T>::call(variant_);
}

template <typename T> value::operator T() const
{
    return as<T>();
}

template <typename T> T& value::get()
{
    detail::convert<T>::call(variant_);
    return boost::get<T>(variant_);
}

template <typename T> T const& value::get() const
{
    T const* value = boost::get<T>(&variant_);

    if(!value)
        throw exception("invalid value type");

    return *value;
}
