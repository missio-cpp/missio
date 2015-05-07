//---------------------------------------------------------------------------
//
//    This file is part of Missio.Common library
//    Copyright (C) 2011, 2012, 2015 Ilya Golovenko
//
//---------------------------------------------------------------------------
#ifndef _missio_common_export_hpp
#define _missio_common_export_hpp

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif  // defined(_MSC_VER) && (_MSC_VER >= 1200)

// BOOST headers
#include <boost/config.hpp>


#ifndef BOOST_SYMBOL_EXPORT
# define BOOST_SYMBOL_EXPORT
#endif

#ifndef BOOST_SYMBOL_IMPORT
# define BOOST_SYMBOL_IMPORT
#endif

#if defined MISSIO_BUILD_SHARED
# define MISSIO_EXPORT BOOST_SYMBOL_EXPORT
#elif defined MISSIO_LINK_SHARED
# define MISSIO_EXPORT BOOST_SYMBOL_IMPORT
#endif

#ifndef MISSIO_EXPORT
# define MISSIO_EXPORT
#endif

#endif  // _missio_common_export_hpp
