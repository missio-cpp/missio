//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------


template <typename T>
binary::binary(T const& data, detail::enable_if_char_container<T> const* /*= nullptr*/) :
    data_(data.begin(), data.end())
{
}

template <typename T>
binary::binary(T const* data, std::size_t size, detail::enable_if_char_type<T> const* /*= nullptr*/) :
    data_(data, data + size)
{
}

template <typename T>
void binary::assign(T const& data, detail::enable_if_char_container<T> const* /*= nullptr*/)
{
    data_.assign(data.begin(), data.end());
}

template <typename T>
void binary::append(T const& data, detail::enable_if_char_container<T> const* /*= nullptr*/)
{
    data_.insert(data_.end(), data.begin(), data.end());
}

template <typename T>
void binary::assign(T const* data, std::size_t size, detail::enable_if_char_type<T> const* /*= nullptr*/)
{
    data_.assign(data, data + size);
}

template <typename T>
void binary::append(T const* data, std::size_t size, detail::enable_if_char_type<T> const* /*= nullptr*/)
{
    data_.insert(data_.end(), data, data + size);
}
