//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef BOOST_APPLICATION_WAIT_FOR_TERMINATION_REQUEST_ASPECT_HPP
#define BOOST_APPLICATION_WAIT_FOR_TERMINATION_REQUEST_ASPECT_HPP

#include <boost/application/config.hpp>
#include <boost/application/detail/csbl.hpp>

#if defined(BOOST_WINDOWS_API)
#include <boost/application/detail/windows/wait_for_termination_request_impl.hpp>
#elif defined(BOOST_POSIX_API)
#include <boost/application/detail/posix/wait_for_termination_request_impl.hpp>
#else
#error "Sorry, no boost application are available for this platform."
#endif

namespace boost {
    namespace application {

        /*!
         * @brief A contract class to be used by the user on your own
         *        class implementation of wait_for_termination_request aspect.
         *
         */
        class wait_for_termination_request : private boost::noncopyable {
        public:
            wait_for_termination_request() {
            }

            virtual ~wait_for_termination_request() {
            }

            /*!
             * Wait for termination request that need be
             * implemented on derived class.
             *
             */
            virtual void wait() = 0;

            /*!
             * Continue, that need be implemented on derived class.
             *
             */
            virtual void proceed() = 0;
        };

        /*!
         * @brief This aspect class handle termination request of application.
         *        User can override this behavior and define your own.
         *
         */
        class wait_for_termination_request_default_behaviour : public wait_for_termination_request {
        public:
            wait_for_termination_request_default_behaviour() : impl_(new wait_for_termination_request_impl()) {
            }

            /*!
             * Wait for termination request.
             *
             */
            void wait() {
                impl_->wait();
            }

            /*!
             * Continue, cause wait to be relesed
             *
             */
            void proceed() {
                impl_->proceed();
            }

        private:
            csbl::shared_ptr<wait_for_termination_request_impl> impl_;
        };

    }    // namespace application
}    // namespace boost

#endif    // BOOST_APPLICATION_WAIT_FOR_TERMINATION_REQUEST_ASPECT_HPP
