// Copyright 2011-2012 Renato Tegon Forti
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST

#define BOOST_TEST_MODULE launch_test

#include <iostream>
#include <boost/application.hpp>
#include <boost/test/unit_test.hpp>

using namespace boost;

class myapp {
public:
    int operator()() {
        return 0;
    }
};

class myapp2 {
public:
    myapp2(application::context &context) : context_(context) {
    }

    int operator()() {
        return 0;
    }

private:
    application::context &context_;
};

class my_signal_manager : public application::signal_manager {
public:

    my_signal_manager(application::context &context) : signal_manager(context) {
        application::handler<>::callback cb = boost::bind(&my_signal_manager::stop, this);

        bind(SIGINT, cb);
    }

    bool stop() {
        application::csbl::shared_ptr<application::wait_for_termination_request> th = context_.find<
                application::wait_for_termination_request>();

        th->proceed();

        return false;
    }
};

BOOST_AUTO_TEST_SUITE(launch_test_suite)
    // common

    BOOST_AUTO_TEST_CASE(common_launch1) {
        application::context cxt;
        myapp2 app(cxt);

        BOOST_CHECK(!application::launch<application::common>(app, cxt));
    }

    BOOST_AUTO_TEST_CASE(common_launch2) {
        myapp app;
        application::global_context::create();

        BOOST_CHECK(!application::launch<application::common>(app, application::global_context::get()));

        application::global_context::destroy();
    }

    BOOST_AUTO_TEST_CASE(common_launch3) {
        application::context cxt;
        myapp2 app(cxt);

        boost::system::error_code ec;
        BOOST_CHECK(!application::launch<application::common>(app, cxt, ec));
        BOOST_CHECK(!ec);
    }

    BOOST_AUTO_TEST_CASE(common_launch4) {
        myapp app;
        application::global_context::create();

        boost::system::error_code ec;
        BOOST_CHECK(!application::launch<application::common>(app, application::global_context::get(), ec));
        BOOST_CHECK(!ec);

        application::global_context::destroy();
    }

    // sm

    BOOST_AUTO_TEST_CASE(signal_manager1) {
        application::context cxt;
        myapp2 app(cxt);

        my_signal_manager sm(cxt);

        BOOST_CHECK(!application::launch<application::common>(app, sm, cxt));
    }

    BOOST_AUTO_TEST_CASE(signal_manager2) {
        myapp app;
        application::global_context::create();

        my_signal_manager sm(*application::global_context::get().get());

        BOOST_CHECK(!application::launch<application::common>(app, sm, application::global_context::get()));

        application::global_context::destroy();
    }

    BOOST_AUTO_TEST_CASE(signal_manager3) {
        application::context cxt;
        myapp2 app(cxt);

        my_signal_manager sm(cxt);

        boost::system::error_code ec;
        BOOST_CHECK(!application::launch<application::common>(app, sm, cxt, ec));
        BOOST_CHECK(!ec);
    }

    BOOST_AUTO_TEST_CASE(signal_manager4) {
        myapp app;
        application::global_context::create();
        my_signal_manager sm(*application::global_context::get().get());

        boost::system::error_code ec;
        BOOST_CHECK(!application::launch<application::common>(app, sm, application::global_context::get(), ec));
        BOOST_CHECK(!ec);

        application::global_context::destroy();
    }

    // server

#if defined( BOOST_WINDOWS_API )

    // on windows we always will receive error:
    // 1063 (0x427)
    // The service process could not connect to the service controller.

    BOOST_AUTO_TEST_CASE(server1){
       application::context cxt;
       myapp2 app(cxt);

       try
       {
          int ret = application::launch<application::server>(app, cxt);
       }
       catch(boost::system::system_error& se)
       {
          BOOST_CHECK(se.code().value() == 1063);
       }
    }

    BOOST_AUTO_TEST_CASE(server2){
       myapp app;
       application::global_context::create();

       try
       {
          int ret = application::launch<application::server>(app, application::global_context::get());
       }
       catch(boost::system::system_error& se)
       {
          BOOST_CHECK(se.code().value() == 1056);
       }

       application::global_context::destroy();
    }

    BOOST_AUTO_TEST_CASE(server3){
       application::context cxt;
       myapp2 app(cxt);

       boost::system::error_code ec;
       int ret = application::launch<application::server>(app, cxt, ec);
       BOOST_CHECK(ec.value() == 1056);
    }

    BOOST_AUTO_TEST_CASE(server4){
       myapp app;
       application::global_context::create();

       boost::system::error_code ec;
       int ret = application::launch<application::server>(app, application::global_context::get(), ec);
       BOOST_CHECK(ec.value() == 1056);

       application::global_context::destroy();
    }

    // sm

    BOOST_AUTO_TEST_CASE(signal_manager5){
       application::context cxt;
       myapp2 app(cxt);

       my_signal_manager sm(cxt);

       try
       {
          int ret = application::launch<application::server>(app, sm, cxt);
       }
       catch(boost::system::system_error& se)
       {
          BOOST_CHECK(se.code().value() == 1056);
       }
    }

    BOOST_AUTO_TEST_CASE(signal_manager6){
       myapp app;
       application::global_context::create();
       my_signal_manager sm(*application::global_context::get().get());

       try
       {
          int ret = application::launch<application::server>(app, sm, application::global_context::get());
       }
       catch(boost::system::system_error& se)
       {
          BOOST_CHECK(se.code().value() == 1056);
       }

       application::global_context::destroy();
    }

    BOOST_AUTO_TEST_CASE(signal_manager7){

       application::context cxt;
       myapp2 app(cxt);

       my_signal_manager sm(cxt);

       boost::system::error_code ec;
       int ret = application::launch<application::server>(app, sm, cxt, ec);
       BOOST_CHECK(ec.value() == 1056);
    }

    BOOST_AUTO_TEST_CASE(signal_manager8){
       myapp app;
       application::global_context::create();
       my_signal_manager sm(*application::global_context::get().get());

       boost::system::error_code ec;
       int ret = application::launch<application::server>(app, sm, application::global_context::get(), ec);
       BOOST_CHECK(ec.value() == 1056);

       application::global_context::destroy();
    }

#elif defined( BOOST_POSIX_API )

    BOOST_AUTO_TEST_CASE(server1) {

        application::context cxt;
        myapp2 app(cxt);

        BOOST_CHECK(!application::launch<application::server>(app, cxt));
    }

    BOOST_AUTO_TEST_CASE(server2) {
        myapp app;
        application::global_context::create();

        BOOST_CHECK(!application::launch<application::server>(app, application::global_context::get()));

        application::global_context::destroy();
    }

    BOOST_AUTO_TEST_CASE(server3) {
        application::context cxt;
        myapp2 app(cxt);

        boost::system::error_code ec;
        BOOST_CHECK(!application::launch<application::server>(app, cxt, ec));
        BOOST_CHECK(!ec);
    }

    BOOST_AUTO_TEST_CASE(server4) {
        myapp app;
        application::global_context::create();

        boost::system::error_code ec;
        BOOST_CHECK(!application::launch<application::server>(app, application::global_context::get(), ec));
        BOOST_CHECK(!ec);

        application::global_context::destroy();
    }

    // sm

    BOOST_AUTO_TEST_CASE(signal_manager5) {

        application::context cxt;
        myapp2 app(cxt);

        my_signal_manager sm(cxt);

        BOOST_CHECK(!application::launch<application::server>(app, sm, cxt));
    }

    BOOST_AUTO_TEST_CASE(signal_manager6) {
        myapp app;
        application::global_context::create();

        my_signal_manager sm(*application::global_context::get().get());

        BOOST_CHECK(!application::launch<application::server>(app, sm, application::global_context::get()));

        application::global_context::destroy();
    }

    BOOST_AUTO_TEST_CASE(signal_manager7) {
        application::context cxt;
        myapp2 app(cxt);

        my_signal_manager sm(cxt);

        boost::system::error_code ec;
        BOOST_CHECK(!application::launch<application::server>(app, sm, cxt, ec));
        BOOST_CHECK(!ec);
    }

    BOOST_AUTO_TEST_CASE(signal_manager8) {
        myapp app;
        application::global_context::create();
        my_signal_manager sm(*application::global_context::get().get());

        boost::system::error_code ec;
        BOOST_CHECK(!application::launch<application::server>(app, sm, application::global_context::get(), ec));
        BOOST_CHECK(!ec);

        application::global_context::destroy();
    }

#endif

BOOST_AUTO_TEST_SUITE_END()