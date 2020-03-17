// Copyright 2011-2012 Renato Tegon Forti
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST

#define BOOST_TEST_MODULE simple_common_application_test

#include <iostream>
#include <boost/application.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost;

class myapp {
public:
    myapp(application::context &context) : context_(context) {
    }

    int operator()() {
        return 0;
    }

private:
    application::context &context_;
};

BOOST_AUTO_TEST_SUITE(simple_common_application_test_suite)

BOOST_AUTO_TEST_CASE(path_aspect1) {
    application::context app_context;
    myapp app(app_context);

    BOOST_CHECK(application::launch<application::common>(app, app_context) == 0);
}

BOOST_AUTO_TEST_SUITE_END()