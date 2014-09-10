//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------


template <typename T, typename>
binary::binary(T const& data) :
    data_(data.begin(), data.end())
{
}

template <typename T, typename>
binary& binary::operator=(T const& data)
{
    data_.assign(data.begin(), data.end());
    return *this;
}

template <typename T, typename>
binary::binary(std::initializer_list<T> data) :
    data_(data.begin(), data.end())
{
}

template <typename T, typename>
binary& binary::operator=(std::initializer_list<T> data)
{
    data_.assign(data.begin(), data.end());
    return *this;
}

template <typename T, typename>
binary::binary(T const* data, std::size_t size) :
    data_(data, data + size)
{
}

template <typename T, typename>
void binary::assign(T const& data)
{
    data_.assign(data.begin(), data.end());
}

template <typename T, typename>
void binary::append(T const& data)
{
    data_.insert(data_.end(), data.begin(), data.end());
}

template <typename T, typename>
void binary::assign(std::initializer_list<T> data)
{
    data_.assign(data.begin(), data.end());
}

template <typename T, typename>
void binary::append(std::initializer_list<T> data)
{
    data_.insert(data_.end(), data.begin(), data.end());
}

template <typename T, typename>
void binary::assign(T const* data, std::size_t size)
{
    data_.assign(data, data + size);
}

template <typename T, typename>
void binary::append(T const* data, std::size_t size)
{
    data_.insert(data_.end(), data, data + size);
}
