//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef BOOST_APPLICATION_PID_ASPECT_HPP
#define BOOST_APPLICATION_PID_ASPECT_HPP

#include <boost/application/config.hpp>
#include <boost/application/detail/csbl.hpp>

#if defined(BOOST_WINDOWS_API)
#include <boost/application/detail/windows/process_id_impl.hpp>
#elif defined(BOOST_POSIX_API)
#include <boost/application/detail/posix/process_id_impl.hpp>
#else
#error "Sorry, no boost application are available for this platform."
#endif

namespace boost {
    namespace application {

        /*!
         * @brief A class aspect to be used to obtain a PID of proccess.
         *
         */
        class process_id : public detail::process_id_impl {
            typedef detail::process_id_impl base_t;

        public:
            typedef process_id_impl::native_pid_t native_pid_t;

            process_id() {
            }

            process_id(native_pid_t p) : base_t(p) {
            }

            virtual ~process_id() {
            }

            /*!
             * Obtain a PID of proccess.
             *
             */
            native_pid_t pid()

                BOOST_NOEXCEPT {
                return base_t::pid();
            }
        };

    }    // namespace application
}    // namespace boost

#endif    // BOOST_APPLICATION_PID_ASPECT_HPP
