//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#define BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST

#define BOOST_TEST_MODULE auto_app_test

#include <iostream>
#include <boost/application.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/application/auto_app.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost;

class myapp1 {
    application::context &context_;

public:
    myapp1(application::context &context) : context_(context) {
    }

    int operator()() {
        std::cout << "myapp1" << std::endl;

        application::csbl::shared_ptr<application::args> myargs = context_.find<application::args>();

        if (myargs) {
            const std::vector<std::string> &arg_vector = myargs->arg_vector();

            // only print args on screen
            for (std::vector<std::string>::const_iterator it = arg_vector.begin(); it != arg_vector.end(); ++it) {
                std::cout << *it << std::endl;
            }

            BOOST_CHECK(arg_vector.size());
        }

        return 0;
    }
};

class myapp2 {

public:
    int operator()() {
        std::cout << "myapp2" << std::endl;

        application::csbl::shared_ptr<application::args> myargs =
            application::global_context::get()->find<application::args>();

        if (myargs) {
            const std::vector<std::string> &arg_vector = myargs->arg_vector();

            // only print args on screen
            for (const auto &it : arg_vector) {
                std::cout << it << std::endl;
            }

            BOOST_CHECK(arg_vector.size());
        }

        return 0;
    }
};

BOOST_AUTO_TEST_SUITE(auto_app_test_suite)

BOOST_AUTO_TEST_CASE(auto_app_test_case) {
    auto &argc = boost::unit_test::framework::master_test_suite().argc;
    auto &argv = boost::unit_test::framework::master_test_suite().argv;
    system::error_code ec;

    BOOST_CHECK(!(application::auto_app<application::common, myapp1>::start(ec)));
    BOOST_CHECK(!(application::auto_app<application::common, myapp1>::start()));

    BOOST_CHECK(!(application::auto_app<application::common, myapp1>::start(
        uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"), ec)));
    BOOST_CHECK(!(application::auto_app<application::common, myapp1>::start(
        uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"))));

    BOOST_CHECK(!(application::auto_app<application::common, myapp1>::start(argc, argv, ec)));
    BOOST_CHECK(!(application::auto_app<application::common, myapp1>::start(argc, argv)));

    BOOST_CHECK(!(application::auto_app<application::common, myapp1>::start(
        argc, argv, uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"), ec)));
    BOOST_CHECK(!(application::auto_app<application::common, myapp1>::start(
        argc, argv, uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"))));

    BOOST_CHECK(!(application::auto_app<application::common, myapp2, application::global_context>::start(ec)));
    BOOST_CHECK(!(application::auto_app<application::common, myapp2, application::global_context>::start()));

    BOOST_CHECK(!(application::auto_app<application::common, myapp2, application::global_context>::start(
        uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"), ec)));
    BOOST_CHECK(!(application::auto_app<application::common, myapp2, application::global_context>::start(
        uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"))));

    BOOST_CHECK(
        !(application::auto_app<application::common, myapp2, application::global_context>::start(argc, argv, ec)));
    BOOST_CHECK(!(application::auto_app<application::common, myapp2, application::global_context>::start(argc, argv)));

    BOOST_CHECK(!(application::auto_app<application::common, myapp2, application::global_context>::start(
        argc, argv, uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"), ec)));
    BOOST_CHECK(!(application::auto_app<application::common, myapp2, application::global_context>::start(
        argc, argv, uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"))));

    /*
    BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp1> >()));
    BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp2, application::global_context>
    >())); BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp1, application::context>
    >()));

    BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp1>
    >(boost::uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"))));
    BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp2, application::global_context>
    >(boost::uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"))));
    BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp1, application::context>
    >(boost::uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"))));

    BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp1> >(argc, argv)));
    BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp2, application::global_context>
    >(argc, argv))); BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp1,
    application::context> >(argc, argv)));

    BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp1> >(argc, argv,
    boost::uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"))));
    BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp2, application::global_context>
    >(argc, argv, boost::uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"))));
    BOOST_CHECK(!(application::launch<application::auto_app<application::common, myapp1, application::context> >(argc,
    argv, boost::uuids::string_generator()("{2F66E4AD-ECA5-475D-8784-4BAA329EF9F1}"))));
    */
}

BOOST_AUTO_TEST_SUITE_END()