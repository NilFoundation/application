//---------------------------------------------------------------------------//
// Copyright (c) 2011-2012 Renato Tegon Forti
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#define BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST

#define BOOST_TEST_MODULE path_aspect_test

#include <iostream>
#include <boost/application.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost;

struct fixture {
    filesystem::path module_path_name;
    application::path path;
};

BOOST_AUTO_TEST_CASE(path_aspect) {
    auto &argc = boost::unit_test::framework::master_test_suite().argc;
    auto &argv = boost::unit_test::framework::master_test_suite().argv;

    filesystem::path module_path_name;

#if defined(BOOST_WINDOWS_API)
    wchar_t module_name[MAX_PATH];

    if (GetModuleFileNameW(0, module_name, sizeof(module_name)) > 0) {
        module_path_name = module_name;
    }
#elif defined(BOOST_POSIX_API)
    std::string command = argv[0];
    char resolved_path[PATH_MAX];

    // realpath -returns the canonicalized absolute pathname
    if (realpath(command.c_str(), resolved_path)) {
        module_path_name = std::string(resolved_path);
    }
#endif

    application::path path;

    { BOOST_CHECK(filesystem::current_path() == path.current_path()); }

    {
        filesystem::path module_path(module_path_name);
        BOOST_CHECK(module_path.stem() == path.executable_name());
    }

    {
        filesystem::path module_path(module_path_name);
        BOOST_CHECK(module_path.filename() == path.executable_full_name());
    }

    {
        filesystem::path module_path(module_path_name);
        BOOST_CHECK(module_path.parent_path() == path.executable_path());
    }

    { BOOST_CHECK(module_path_name == path.executable_path_name()); }

    std::string isempty;
    BOOST_CHECK(!isempty.size());

    isempty = path.app_data_path().string();
    BOOST_CHECK(isempty.size());

    isempty = path.home_path().string();
    BOOST_CHECK(isempty.size());

    isempty = path.config_path().string();
    BOOST_CHECK(isempty.size());

    isempty = path.app_data_path().string();
    BOOST_CHECK(isempty.size());

    isempty = path.temp_path().string();
    BOOST_CHECK(isempty.size());
}