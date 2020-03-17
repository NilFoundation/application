//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2018-2019 Nil Foundation
// Copyright (c) 2018-2019 Mikhail Komarov <nemo@nilfoundation.org>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef BOOST_APPLICATION_DETAIL_CSBL_HPP
#define BOOST_APPLICATION_DETAIL_CSBL_HPP

#include <boost/application/config.hpp>

// This enable we to use csbl:: and internally the library select correct
// names, e.g. : csbl::unique_ptr will be boost::shared_ptr or std::shared_ptr

namespace boost {
    namespace application {
        namespace csbl {
            // as common std-boost library

            BOOST_APPLICATION_FEATURE_SELECT

            template<class T>
            inline type_index get_type_id() {

#if defined(BOOST_APPLICATION_FEATURE_NS_SELECT_STD)
                return typeid(T);
#elif defined(BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST)
                return BOOST_APPLICATION_TYPE_INDEX_NS_SELECT::type_id<T>();
#else    // auto detect
#ifndef BOOST_NO_CXX11_HDR_TYPEINDEX
                return typeid(T);
#else
                return BOOST_APPLICATION_TYPE_INDEX_NS_SELECT::type_id<T>();
#endif
#endif
            }

        }    // namespace csbl
    }        // namespace application
}    // namespace boost

#endif    // BOOST_APPLICATION_DETAIL_CSBL_HPP
