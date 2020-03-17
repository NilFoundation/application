// Copyright 2011-2014 Renato Tegon Forti
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST

#define BOOST_TEST_MODULE handler_test

#include <iostream>
#include <boost/application.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost;

struct handler_test {
    bool handler() {
        return true;
    }
};

struct fixture {
    handler_test app_handler_test;
    application::context app_context;
};

BOOST_AUTO_TEST_SUITE()

BOOST_FIXTURE_TEST_CASE(test_case1, fixture) {
    application::handler<> h;

    BOOST_CHECK(!h.is_valid());
    BOOST_CHECK(!h.is_valid());
}

BOOST_FIXTURE_TEST_CASE(test_case2, fixture) {
    application::handler<>::callback cb = boost::bind(&handler_test::handler, &app_handler_test);

    application::handler<> h(cb);
    BOOST_CHECK(h.is_valid());

    application::handler<>::callback *hvb = nullptr;
    BOOST_CHECK(h.get(hvb));
    BOOST_CHECK((*hvb)());
}

BOOST_FIXTURE_TEST_CASE(test_case3, fixture) {
    application::handler<>::callback cb = boost::bind(&handler_test::handler, &app_handler_test);

    application::handler<> h;
    h.set(cb);

    BOOST_CHECK(h.is_valid());

    application::handler<>::callback *hcb = nullptr;
    BOOST_CHECK(h.get(hcb));
    BOOST_CHECK((*hcb)());
}

BOOST_AUTO_TEST_SUITE_END()