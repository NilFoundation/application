// Copyright 2011-2012 Renato Tegon Forti
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST

#define BOOST_TEST_MODULE path_aspect_test
#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API

#include <iostream>
#include <boost/application.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost;

struct fixture {
    filesystem::path module_path_name;
    application::path path;
};

int main(int argc, char *argv[]) {
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

    return boost::unit_test::unit_test_main(init_unit_test, argc, argv);
}

BOOST_AUTO_TEST_SUITE(path_aspect_test_suite)

BOOST_FIXTURE_TEST_CASE(path_aspect1, fixture) {
    BOOST_CHECK(filesystem::current_path() == path.current_path());
}

BOOST_FIXTURE_TEST_CASE(path_aspect2, fixture) {
    const filesystem::path &module_path(module_path_name);
    BOOST_CHECK(module_path.stem() == path.executable_name());
}

BOOST_FIXTURE_TEST_CASE(path_aspect3, fixture) {
    const filesystem::path &module_path(module_path_name);
    BOOST_CHECK(module_path.filename() == path.executable_full_name());
}

BOOST_FIXTURE_TEST_CASE(path_aspect4, fixture) {
    const filesystem::path &module_path(module_path_name);
    BOOST_CHECK(module_path.parent_path() == path.executable_path());
}

BOOST_FIXTURE_TEST_CASE(path_aspect5, fixture) {
    BOOST_CHECK(module_path_name == path.executable_path_name());
}

BOOST_FIXTURE_TEST_CASE(path_aspect6, fixture) {
    std::string isempty;
    BOOST_CHECK(isempty.empty());

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

BOOST_AUTO_TEST_SUITE_END()