//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef BOOST_APPLICATION_STATUS_ASPECT_HPP
#define BOOST_APPLICATION_STATUS_ASPECT_HPP

// application
#include <boost/application/config.hpp>

namespace boost {
    namespace application {

        /*!
         * @brief This aspect class is used internaly by applications types (modes)
         *
         * Indicates the current state of application,
         * 3 ways are possible:
         *
         * - application_stopped
         * - application_running
         * - application_paused (used only on server appliation on windows side)
         *
         */
        class status {
            friend class server;

            friend class common;

        public:
            // application current state
            enum application_state {
                stopped = 0,
                running,
                paused    // Windows Service
            };

            /*!
             * Constructs an application_state aspect.
             *
             * \param state The state of application.
             */
            status(application_state state) : application_state_(state) {
            }

            /*!
             * Retreaves current state of application.
             *
             * \return the state of application.
             *
             */
            application_state state() {
                return application_state_;
            }

            /*!
             * Sets the current state of application.
             *
             * \param state The state of application.
             *
             */
            void state(application_state state) {
                application_state_ = state;
            }

            bool operator==(application_state state) const {
                return state == application_state_;
            }

            bool operator!=(application_state state) const {
                return state != application_state_;
            }

        private:
            application_state application_state_;
        };

    }    // namespace application
}    // namespace boost

#endif    // BOOST_APPLICATION_STATUS_ASPECT_HPP
