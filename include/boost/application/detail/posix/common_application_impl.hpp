//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2018-2019 Nil Foundation
// Copyright (c) 2018-2019 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef BOOST_APPLICATION_COMMON_APPLICATION_IMPL_HPP
#define BOOST_APPLICATION_COMMON_APPLICATION_IMPL_HPP

#include <boost/application/config.hpp>
#include <boost/application/base_type.hpp>
#include <boost/application/detail/application_impl.hpp>
#include <boost/application/aspects/termination_handler.hpp>
#include <boost/application/signal_binder.hpp>

#include <boost/thread/thread.hpp>
#include <boost/lambda/lambda.hpp>

namespace boost {
    namespace application {

        template<typename CharType>
        class common_application_impl_ : public application_impl {
        public:
            typedef csbl::function<int(void)> mainop;

            // string types to be used internaly to handle unicode on windows
            typedef CharType char_type;
            typedef std::basic_string<char_type> string_type;

            common_application_impl_(const mainop &main, signal_binder &sb, application::context &context,
                                     boost::system::error_code &ec) :
                application_impl(context),
                main_(main) {
                sb.start();
            }

            virtual ~common_application_impl_() {
            }

            int run() {
                return main_();
            }

        private:
            mainop main_;
        };

        /////////////////////////////////////////////////////////////////////////////
        // server_application_impl
        //

        // args versions for Multi-Byte string and Unicode string
        typedef common_application_impl_<character_types::char_type> common_application_impl;
        // wchar_t / char

    }    // namespace application
}    // namespace boost

#endif    // BOOST_APPLICATION_COMMON_APPLICATION_IMPL_HPP
