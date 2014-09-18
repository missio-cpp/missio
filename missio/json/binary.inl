//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012, 2014 Ilya Golovenko
//
//---------------------------------------------------------------------------


template <typename Container, typename>
binary::binary(Container const& container) : binary(container.data(), container.size())
{
}

template <typename Container, typename>
binary& binary::operator=(Container const& container)
{
    assign(container.data(), container.size());
    return *this;
}

template <typename Container, typename>
void binary::assign(Container const& container)
{
    assign(container.data(), container.size());
}

template <typename Container, typename>
void binary::append(Container const& container)
{
    append(container.data(), container.size());
}
