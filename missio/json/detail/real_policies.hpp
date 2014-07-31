//---------------------------------------------------------------------------
//
//    This file is part of Missio.JSON library
//    Copyright (C) 2011, 2012 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_json_detail_real_policies_hpp
#define _missio_json_detail_real_policies_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/spirit/include/karma.hpp>


namespace missio
{
namespace json
{
namespace detail
{

template <typename T>
struct high_precision_real_policies : boost::spirit::karma::real_policies<T>
{
    static unsigned precision(T)
    {
        return 6;
    }
};

}   // namespace detail
}   // namespace json
}   // namespace missio

#endif  // _missio_json_detail_real_policies_hpp
