//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------


template <typename T> value::value(T const& value)
{
    detail::assign(variant_, value);
}

template <typename T> value& value::operator=(T const& value)
{
    detail::assign(variant_, value);
    return *this;
}

template <typename T> value::value(T&& value)
{
    detail::assign(variant_, std::forward<T>(value));
}

template <typename T> value& value::operator=(T&& value)
{
    detail::assign(variant_, std::forward<T>(value));
    return *this;
}

template <typename T> bool value::is() const
{
    return detail::is_type<T>::call(variant_);
}

template <typename T> value::result_type_of_get<T> value::get() const
{
    return detail::get_type<T>::call(variant_);
}

template <typename T, typename> value::operator T const&() const
{
    return get<T>();
}

template <typename T> value::operator T() const
{
    return get<T>();
}
