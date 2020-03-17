//---------------------------------------------------------------------------//
// Copyright (c) 2014 Renato Tegon Forti
// Copyright (c) 2014 Antony Polukhin
// Copyright (c) 2018-2019 Nil Foundation
// Copyright (c) 2018-2019 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef BOOST_APPLICATION_DETAIL_PROCESS_ID_HPP
#define BOOST_APPLICATION_DETAIL_PROCESS_ID_HPP

#include <boost/application/config.hpp>
#include <boost/application/detail/csbl.hpp>
#include <boost/application/system_error.hpp>

#include <cstdlib>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
    namespace application {
        namespace detail {

            class process_id_impl {

            public:
                typedef pid_t native_pid_t;

                process_id_impl() : pid_(0) {
                }

                process_id_impl(native_pid_t pid) : pid_(pid) {
                }

                native_pid_t pid()

                    BOOST_NOEXCEPT {
                    if (pid_) {
                        return pid_;
                    }

                    pid_ = getpid();
                    return pid_;
                }

            private:
                native_pid_t pid_;
            };

        }    // namespace detail
    }        // namespace application
}    // namespace boost

#endif    // BOOST_APPLICATION_DETAIL_WINDOWS_PATH_FROM_ME_HPP
