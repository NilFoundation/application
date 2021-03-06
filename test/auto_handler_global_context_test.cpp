//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#define BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST

#define BOOST_TEST_MODULE auto_handler_global_context_test

#include <iostream>
#include <boost/application.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost;

inline application::global_context_ptr this_application() {
    return application::global_context::get();
}

class myapp {
public:
    myapp(application::context &context) : context_(context) {
    }

    int operator()() {
        return 0;
    }

    bool stop() {
        return true;    // return true to stop, false to ignore
    }

    bool pause() {
        return true;    // return true to pause, false to ignore
    }

    bool resume() {
        return true;    // return true to resume, false to ignore
    }

private:
    application::context &context_;
};

BOOST_AUTO_TEST_SUITE(auto_handler_global_context_test_suite)

BOOST_AUTO_TEST_CASE(auto_handler_global_context_test_case) {
    system::error_code ec;

    application::global_context_ptr app_context = application::global_context::create(ec);
    BOOST_CHECK(!ec.value());

    application::auto_handler<myapp> app(app_context);

    BOOST_CHECK(application::launch<application::server>(app, app_context, ec) == 0);
    BOOST_CHECK(!ec.value());

    application::global_context::destroy(ec);
    BOOST_CHECK(!ec.value());
}

BOOST_AUTO_TEST_SUITE_END()