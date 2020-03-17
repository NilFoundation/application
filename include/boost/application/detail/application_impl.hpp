//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2018-2019 Nil Foundation
// Copyright (c) 2018-2019 Mikhail Komarov <nemo@nilfoundation.org>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef BOOST_APPLICATION_DETAIL_APPLICATION_IMPL_HPP
#define BOOST_APPLICATION_DETAIL_APPLICATION_IMPL_HPP

// application
#include <boost/application/config.hpp>
#include <boost/application/context.hpp>

namespace boost {
    namespace application {

        // share context on modes
        class application_impl : private boost::noncopyable {
        public:
            application_impl(context &cxt) : context_(cxt) {
            }

            context &get_context() {
                return context_;
            }

        protected:
            context &context_;
        };

    }    // namespace application
}    // namespace boost

#endif    // BOOST_APPLICATION_DETAIL_APPLICATION_IMPL_HPP
