#define BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST

#define BOOST_TEST_MODULE tunit_test
#define BOOST_TEST_NO_MAIN
#define BOOST_TEST_ALTERNATIVE_INIT_API

//intro
#include <iostream>
#include <boost/application.hpp>

#include <boost/test/unit_test.hpp>

// other unit
#include "myapp.hpp"

int main(int argc, char *argv[]) {
    myapp app;
    application::global_context_ptr ctx = application::global_context::create();

    this_application()->insert<application::args>(boost::make_shared<application::args>(argc, argv));

    BOOST_CHECK(application::launch<application::common>(app, ctx) == 0);

    application::global_context::destroy();

    return boost::unit_test::unit_test_main(init_unit_test, argc, argv);
}
