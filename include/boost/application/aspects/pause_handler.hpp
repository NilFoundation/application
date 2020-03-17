//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2018-2019 Nil Foundation
// Copyright (c) 2018-2019 Mikhail Komarov <nemo@nilfoundation.org>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef BOOST_APPLICATION_ASPECT_PAUSE_HANDLER_HPP
#define BOOST_APPLICATION_ASPECT_PAUSE_HANDLER_HPP

#include <boost/application/config.hpp>
#include <boost/application/handler.hpp>

namespace boost {
    namespace application {

        class pause_handler : public handler<> {
        public:
            pause_handler(const callback &cb) : handler<>(cb) {
            }
        };

        class pause_handler_default_behaviour : public pause_handler {
        public:
            pause_handler_default_behaviour(const callback &cb) : pause_handler(cb) {
            }
        };

    }    // namespace application
}    // namespace boost

#endif    // BOOST_APPLICATION_ASPECT_PAUSE_HANDLER_HPP
