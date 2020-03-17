//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2013 Stanislav Ivochkin
// Copyright (c) 2018-2019 Nil Foundation
// Copyright (c) 2018-2019 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef BOOST_APPLICATION_SELFPIPE_ASPECT_HPP
#define BOOST_APPLICATION_SELFPIPE_ASPECT_HPP

#include <boost/application/config.hpp>
#include <boost/application/base_type.hpp>

// platform usage
#if defined(BOOST_POSIX_API)
#include <unistd.h>
#include <fcntl.h>
#endif

namespace boost {
    namespace application {

        namespace posix {

            /*!
             * @brief POSIX platform specific aspect that implement self-pipe trick.
             *
             */
            class selfpipe : private boost::noncopyable {

            public:
                selfpipe() {
                    boost::system::error_code ec;

                    setup(ec);

                    if (ec) {
                        BOOST_APPLICATION_THROW_LAST_SYSTEM_ERROR_USING_MY_EC("selfpipe() failed", ec);
                    }
                }

                selfpipe(boost::system::error_code &ec) {
                    setup(ec);
                }

                virtual ~selfpipe() {
                    teardown();
                }

            protected:
                void setup(boost::system::error_code &ec) {
                    if (pipe(fd_) == -1) {
                        ec = last_error_code();
                        return;
                    }

                    fcntl(fd_[readfd], F_SETFL, fcntl(fd_[readfd], F_GETFL) | O_NONBLOCK);

                    fcntl(fd_[writefd], F_SETFL, fcntl(fd_[writefd], F_GETFL) | O_NONBLOCK);
                }

                void teardown() {
                    close(fd_[readfd]);
                    close(fd_[writefd]);
                }

            public:
                int read_fd() const {
                    return fd_[readfd];
                }

                int write_fd() const {
                    return fd_[writefd];
                }

                void poke() {
                    write(fd_[writefd], "", 1);
                }

            private:
                enum { readfd = 0, writefd = 1 };

                int fd_[2];

            };    // selfpipe

        }    // namespace posix

// platform usage
#if defined(BOOST_WINDOWS_API)
        // not available
        // using windows::self_pipe;
#error "Sorry, the Windows platform don't support 'selfpipe' aspect."
#elif defined(BOOST_POSIX_API)
        using posix::selfpipe;
#else
#error "Sorry, selfpipe are available for this platform."
#endif

    }    // namespace application
}    // namespace boost

#endif    // BOOST_APPLICATION_SELFPIPE_ASPECT_HPP
