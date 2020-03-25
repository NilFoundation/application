//---------------------------------------------------------------------------//
// Copyright (c) 2014 Renato Tegon Forti
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef BOOST_APPLICATION_PATH_ASPECT_HPP
#define BOOST_APPLICATION_PATH_ASPECT_HPP

#include <boost/application/config.hpp>
#include <boost/application/detail/csbl.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#if defined(BOOST_WINDOWS_API)
#include <boost/application/detail/windows/path_impl.hpp>
#elif defined(BOOST_POSIX_API)
#include <boost/application/detail/posix/path_impl.hpp>
#else
#error "Sorry, no boost application are available for this platform."
#endif

namespace boost {
    namespace application {

        class path {
        public:
            path() : impl_(new detail::default_path_impl) {
            }

            filesystem::path current_path() {
                return impl_->current_path();
            }

            filesystem::path location(boost::system::error_code &ec) {
                return impl_->location(ec);
            }

            filesystem::path location() {
                return impl_->location();
            }

            filesystem::path executable_path_name(boost::system::error_code &ec) {
                return impl_->location(ec);
            }

            filesystem::path executable_path_name() {
                return impl_->location();
            }

            filesystem::path executable_path(boost::system::error_code &ec) {
                return location(ec).parent_path();
            }

            filesystem::path executable_path() {
                return impl_->location().parent_path();
            }

            filesystem::path executable_full_name(boost::system::error_code &ec) {
                return impl_->location(ec).filename();
            }

            filesystem::path executable_full_name() {
                return impl_->location().filename();
            }

            filesystem::path executable_name(boost::system::error_code &ec) {
                return impl_->location(ec).stem();
            }

            filesystem::path executable_name() {
                return impl_->location().stem();
            }

            filesystem::path home_path() {
                return impl_->home_path();
            }

            filesystem::path config_path() {
                return impl_->config_path();
            }

            filesystem::path app_data_path() {
                return impl_->app_data_path();
            }

            filesystem::path temp_path() {
                return impl_->temp_path();
            }

        private:
            csbl::shared_ptr<detail::default_path_impl> impl_;
        };

    }    // namespace application
}    // namespace boost

#endif    // BOOST_APPLICATION_PATH_ASPECT_HPP
