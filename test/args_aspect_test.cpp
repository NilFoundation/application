//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#define BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST

#define BOOST_TEST_MODULE args_aspect_test

#include <iostream>
#include <boost/application.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost;

BOOST_AUTO_TEST_CASE(args_aspect_test_case) {
    auto &argc = boost::unit_test::framework::master_test_suite().argc;
    auto &argv = boost::unit_test::framework::master_test_suite().argv;
    application::args myargs(argc, argv);

    BOOST_CHECK(myargs.argc());

    const std::vector<std::string> &argvec = myargs.arg_vector();

    BOOST_CHECK(argvec.size());
}