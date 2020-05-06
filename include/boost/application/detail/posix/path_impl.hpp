//---------------------------------------------------------------------------//
// Copyright (c) 2014 Renato Tegon Forti
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#ifndef BOOST_APPLICATION_DETAIL_POSIX_PATH_FROM_ME_HPP
#define BOOST_APPLICATION_DETAIL_POSIX_PATH_FROM_ME_HPP

#include <boost/application/config.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/predef/os.h>

#include <cstdlib>
#include <pwd.h>
#include <unistd.h>

#ifdef BOOST_OS_MACOS_AVAILABLE
#include <mach-o/dyld.h>
#include <sys/param.h>
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {
    namespace application {
        namespace detail {

            class default_path_impl {
                filesystem::path full_path_;

                boost::filesystem::path path_from_me(boost::system::error_code &ec) {
#ifdef BOOST_OS_MACOS_AVAILABLE
                    char path[4096], rpath[4096];
                    uint32_t size = sizeof(path);
                    if (_NSGetExecutablePath(path, &size) == 0) {
                        if (realpath(path, rpath)) {
                            return boost::filesystem::path(rpath);
                        } else {
                            ec = boost::system::error_code(errno, boost::system::system_category());
                            boost::throw_exception(boost::system::system_error(ec, "Cannot resolve the absolute path"));
                        }
                    } else {
                        ec = boost::system::error_code(errno, boost::system::system_category());
                        boost::throw_exception(boost::system::system_error(ec,
                                                                           "Path is too long (more than 4096 "
                                                                           "symbols)"));
                    }
#else
                    return boost::filesystem::read_symlink("/proc/self/exe", ec);
#endif
                }

                boost::filesystem::path getenv(const char *env_name) {
                    const char *res = ::getenv(env_name);
                    return res ? res : boost::filesystem::path();
                }

            public:
                filesystem::path current_path(void) {
                    return filesystem::current_path();
                }

                const filesystem::path &location(boost::system::error_code &ec) {
                    if (!full_path_.empty()) {
                        return full_path_;
                    }

                    boost::filesystem::path full_path = path_from_me(ec);
                    if (ec) {
                        full_path_ = boost::filesystem::path();
                    }

                    full_path_ = full_path;

                    return full_path_;
                }

                const filesystem::path &location() {
                    if (!full_path_.empty()) {
                        return full_path_;
                    }

                    boost::system::error_code ec;

                    full_path_ = location(ec);

                    if (ec) {
                        boost::throw_exception(boost::system::system_error(ec, "location() failed"));
                    }

                    return full_path_;
                }

                inline boost::filesystem::path home_path() {
                    boost::filesystem::path path = getenv("HOME");
                    if (path.empty()) {
                        struct passwd *pwd = getpwuid(getuid());
                        if (pwd) {
                            return pwd->pw_dir;
                        }
                        return ".";
                    }
                    return path;
                }

                inline boost::filesystem::path app_data_path() {
                    boost::filesystem::path path = getenv("XDG_DATA_HOME");
                    if (path.empty()) {
#ifdef BOOST_OS_MACOS_AVAILABLE
                        return home_path() / "Library/Preferences/";
#else
                        return home_path() / ".local/share";
#endif
                    }
                    return path;
                }

                inline boost::filesystem::path config_path() {

                    boost::filesystem::path path = getenv("XDG_CONFIG_HOME");
                    if (path.empty()) {
#ifdef BOOST_OS_MACOS_AVAILABLE
                        return home_path() / "Library/Preferences/";
#else
                        return home_path() / ".config";
#endif
                    }
                    return path;
                }

                inline boost::filesystem::path temp_path() {
                    boost::filesystem::path path = getenv("TMPDIR");
                    if (path.empty()) {
                        return "/tmp";
                    }    // Fallback if TMPDIR not available
                    return path;
                }
            };

        }    // namespace detail
    }        // namespace application
}    // namespace boost

#endif    // BOOST_APPLICATION_DETAIL_POSIX_PATH_FROM_ME_HPP
