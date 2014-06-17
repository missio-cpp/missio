//---------------------------------------------------------------------------
//
//    This file is part of Missio.Format library
//    Copyright (C) 2011, 2012, 2013 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_format_detail_real_format_hpp
#define _missio_format_detail_real_format_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)


namespace missio
{
namespace format
{
namespace detail
{

enum class real_format
{
    fixed,
    general,
    scientific
};

}   // namespace detail
}   // namespace format
}   // namespace missio

#endif  // _missio_format_detail_real_format_hpp
