//---------------------------------------------------------------------------//
// Copyright (c) 2011-2014 Renato Tegon Forti
// Copyright (c) 2018-2020 Mikhail Komarov <nemo@nil.foundation>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//---------------------------------------------------------------------------//

#define BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST

#define BOOST_TEST_MODULE aspect_map_test

#include <iostream>
#include <utility>

#include <boost/application.hpp>

#include <boost/test/unit_test.hpp>

using namespace boost;

//
// Test aspects
//

class my_msg_aspect_test {
    std::string hi_message_;

public:
    my_msg_aspect_test(std::string hi_message) : hi_message_(std::move(hi_message)) {
    }

    const std::string &say_hi() const {
        return hi_message_;
    }

    void set(const std::string &hi_message) {
        hi_message_ = hi_message;
    }
};

class my_sum_aspect_test {
    int result_;

public:
    my_sum_aspect_test(int x, int y) : result_(x + y) {
    }

    int get() const {
        return result_;
    }

    void add(int z) {
        result_ += z;
    }
};

//
// Reduction for my_msg_aspect_test
//

shared_ptr<my_msg_aspect_test> my_msg_aspect_test_reduction_function(const shared_ptr<my_msg_aspect_test> &lhs,
                                                                     const shared_ptr<my_msg_aspect_test> &rhs) {
    shared_ptr<my_msg_aspect_test> temp(boost::make_shared<my_msg_aspect_test>(""));

    temp->set(lhs->say_hi() + " : " + rhs->say_hi());

    return temp;
}

shared_ptr<my_sum_aspect_test> my_sum_aspect_test_reduction_function(const shared_ptr<my_sum_aspect_test> &lhs,
                                                                     const shared_ptr<my_sum_aspect_test> &rhs) {
    shared_ptr<my_sum_aspect_test> temp(boost::make_shared<my_sum_aspect_test>(1, 1));

    temp->add(rhs->get());

    return temp;
}

template<int LOOP_INTERACTIONS = 100>
class parallel_test {
    application::aspect_map my_aspect_map_;
    boost::thread_group group_;

public:
    parallel_test() {
        group_.add_thread(new boost::thread(&parallel_test::insert_sleep_removes_aspect1, this));
        group_.add_thread(new boost::thread(&parallel_test::insert_sleep_removes_aspect2, this));
        group_.add_thread(new boost::thread(&parallel_test::find_and_access, this));
        group_.add_thread(new boost::thread(&parallel_test::insert_sleep_aspect1, this));
        group_.add_thread(new boost::thread(&parallel_test::use_sleep_remove_aspect1, this));
    }

    void wait() {
        // wait for them
        group_.join_all();
        BOOST_CHECK(my_aspect_map_.size() == 0);
    }

    // use it, sleep and the remove aspect.
    void use_sleep_remove_aspect1() {
        for (int i = 0; i < LOOP_INTERACTIONS; i++) {    // atomic
            strict_lock<application::aspect_map> guard(my_aspect_map_);

            shared_ptr<my_msg_aspect_test> res = my_aspect_map_.find<my_msg_aspect_test>(guard);

            if (res) {
                BOOST_CHECK(res->say_hi() == "HI");

                boost::this_thread::sleep(boost::posix_time::milliseconds(i * (3 + 1)));

                my_aspect_map_.erase<my_msg_aspect_test>(guard);
            }
        }
    }

    // loop with insert/sleep/removes an aspect
    void insert_sleep_removes_aspect1() {
        for (int i = 0; i < LOOP_INTERACTIONS; i++) {    // atomic
            strict_lock<application::aspect_map> guard(my_aspect_map_);

            my_aspect_map_.insert<my_msg_aspect_test>(boost::make_shared<my_msg_aspect_test>("HI"), guard);

            boost::this_thread::sleep(boost::posix_time::milliseconds(i + 10));

            my_aspect_map_.erase<my_msg_aspect_test>(guard);
        }
    }

    void insert_sleep_removes_aspect2() {
        for (int i = 0; i < LOOP_INTERACTIONS; i++) {    // atomic
            strict_lock<application::aspect_map> guard(my_aspect_map_);

            my_aspect_map_.insert<my_sum_aspect_test>(boost::make_shared<my_sum_aspect_test>(1, 1), guard);

            boost::this_thread::sleep(boost::posix_time::milliseconds(i + 15));

            my_aspect_map_.erase<my_sum_aspect_test>(guard);
        }
    }

    // loop with insert and sleep
    void insert_sleep_aspect1() {
        for (int i = 0; i < LOOP_INTERACTIONS; i++) {    // atomic
            strict_lock<application::aspect_map> guard(my_aspect_map_);

            if (!my_aspect_map_.find<my_msg_aspect_test>(guard)) {
                my_aspect_map_.insert<my_msg_aspect_test>(boost::make_shared<my_msg_aspect_test>("HI"), guard);

                boost::this_thread::sleep(boost::posix_time::milliseconds(i + 5));
            }
        }
    }

    // loop to find the aspect and if found do something
    void find_and_access() {
        for (int i = 0; i < LOOP_INTERACTIONS; i++) {    // atomic
            strict_lock<application::aspect_map> guard(my_aspect_map_);

            shared_ptr<my_msg_aspect_test> a1 = my_aspect_map_.find<my_msg_aspect_test>(guard);

            if (a1) {
                typedef boost::function2<shared_ptr<my_msg_aspect_test>,
                                         shared_ptr<my_msg_aspect_test>,
                                         shared_ptr<my_msg_aspect_test>>
                    reduction;

                reduction rf = &my_msg_aspect_test_reduction_function;

                my_aspect_map_.reduce<my_msg_aspect_test, reduction>(make_shared<my_msg_aspect_test>("HI"), rf, guard);
            }

            shared_ptr<my_sum_aspect_test> a2 = my_aspect_map_.find<my_sum_aspect_test>(guard);

            if (a2) {
                typedef boost::function2<shared_ptr<my_sum_aspect_test>,
                                         shared_ptr<my_sum_aspect_test>,
                                         shared_ptr<my_sum_aspect_test>>
                    reduction;

                reduction rf = &my_sum_aspect_test_reduction_function;

                my_aspect_map_.reduce<my_sum_aspect_test, reduction>(make_shared<my_sum_aspect_test>(1, 1), rf, guard);
            }
        }
    }
};

//
// tests
//

BOOST_AUTO_TEST_SUITE(aspect_map_test_suite)
//
// Internal locking Version.
//

BOOST_AUTO_TEST_CASE(aspect_map_default_constructor_test) {
    application::aspect_map my_aspect_map;

    BOOST_CHECK(!my_aspect_map.find<my_msg_aspect_test>());
}

BOOST_AUTO_TEST_CASE(aspect_map_insert_find_size_test) {
    application::aspect_map my_aspect_map;
    shared_ptr<my_msg_aspect_test> res =
        my_aspect_map.insert<my_msg_aspect_test>(boost::make_shared<my_msg_aspect_test>("HI"));

    BOOST_CHECK(res.get() == 0);
    BOOST_CHECK(my_aspect_map.size() == 1);
    BOOST_CHECK(my_aspect_map.find<my_msg_aspect_test>()->say_hi() == "HI");
}

BOOST_AUTO_TEST_CASE(aspect_map_insert_test) {
    application::aspect_map my_aspect_map;
    shared_ptr<my_msg_aspect_test> res1 =
        my_aspect_map.insert<my_msg_aspect_test>(boost::make_shared<my_msg_aspect_test>("HI"));
    shared_ptr<my_msg_aspect_test> res2 =
        my_aspect_map.insert<my_msg_aspect_test>(boost::make_shared<my_msg_aspect_test>("HI HI"));

    BOOST_CHECK(res2.get() != 0);
    BOOST_CHECK(res2->say_hi() == "HI");
    BOOST_CHECK(my_aspect_map.size() == 1);
    BOOST_CHECK(my_aspect_map.find<my_msg_aspect_test>()->say_hi() == "HI");
}

BOOST_AUTO_TEST_CASE(aspect_map_replace_test) {
    application::aspect_map my_aspect_map;
    shared_ptr<my_msg_aspect_test> res =
        my_aspect_map.insert<my_msg_aspect_test>(boost::make_shared<my_msg_aspect_test>("HI"));

    BOOST_CHECK(res.get() == 0);
    BOOST_CHECK(my_aspect_map.size() == 1);
    BOOST_CHECK(my_aspect_map.find<my_msg_aspect_test>()->say_hi() == "HI");

    res = my_aspect_map.exchange<my_msg_aspect_test>(boost::make_shared<my_msg_aspect_test>("HI:HI"));

    BOOST_CHECK(res.get() == 0);
    BOOST_CHECK(my_aspect_map.size() == 1);
    BOOST_CHECK(my_aspect_map.find<my_msg_aspect_test>()->say_hi() == "HI:HI");
}

BOOST_AUTO_TEST_CASE(aspect_map_erase_test) {
    application::aspect_map my_aspect_map;
    shared_ptr<my_msg_aspect_test> res =
        my_aspect_map.insert<my_msg_aspect_test>(boost::make_shared<my_msg_aspect_test>("HI"));

    BOOST_CHECK(res.get() == 0);
    BOOST_CHECK(my_aspect_map.size() == 1);
    BOOST_CHECK(my_aspect_map.find<my_msg_aspect_test>()->say_hi() == "HI");

    res = my_aspect_map.erase<my_msg_aspect_test>();

    BOOST_CHECK(res.get());
    BOOST_CHECK(my_aspect_map.size() == 0);
    // BOOST_CHECK(my_aspect_map.find<my_msg_aspect_test>() == false);
}

BOOST_AUTO_TEST_CASE(aspect_map_reduction_test) {
    typedef boost::
        function2<shared_ptr<my_msg_aspect_test>, shared_ptr<my_msg_aspect_test>, shared_ptr<my_msg_aspect_test>>
            reduction;

    reduction rf = &my_msg_aspect_test_reduction_function;

    application::aspect_map my_aspect_map;
    my_aspect_map.insert<my_msg_aspect_test>(make_shared<my_msg_aspect_test>("HI"));
    my_aspect_map.reduce<my_msg_aspect_test, reduction>(make_shared<my_msg_aspect_test>("HI"), rf);

    BOOST_CHECK(my_aspect_map.find<my_msg_aspect_test>()->say_hi() == "HI : HI");
}

BOOST_AUTO_TEST_CASE(aspect_map_size_exists_test) {
    application::aspect_map my_aspect_map;
    my_aspect_map.insert<my_msg_aspect_test>(boost::make_shared<my_msg_aspect_test>("HI"));

    BOOST_CHECK(my_aspect_map.size());
}

BOOST_AUTO_TEST_CASE(aspect_map_empty_test) {
    application::aspect_map my_aspect_map;
    my_aspect_map.insert<my_msg_aspect_test>(boost::make_shared<my_msg_aspect_test>("HI"));

    BOOST_CHECK(my_aspect_map.empty());
}

BOOST_AUTO_TEST_CASE(aspect_map_clear_test) {
    application::aspect_map my_aspect_map;
    my_aspect_map.insert<my_msg_aspect_test>(boost::make_shared<my_msg_aspect_test>("HI"));

    my_aspect_map.clear();

    BOOST_CHECK(!my_aspect_map.empty());
}

BOOST_AUTO_TEST_CASE(aspect_map_concurrent_access_test) {
    parallel_test<100>().wait();
}

BOOST_AUTO_TEST_SUITE_END()