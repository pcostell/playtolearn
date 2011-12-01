/*
 * File: test/backend/StateTest.cpp
 */

#define BOOST_TEST_MODULE State test

#include "util/ErrorTypes.hpp"
#include "backend/State.hpp"
#include "backend/Object.hpp"
#include "backend/TransitionFn.hpp"
#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/test/unit_test.hpp>

using namespace std;
using PlayToLearn::Util::InvalidObjectError;
using PlayToLearn::Backend::State;
using PlayToLearn::Backend::Object;
using PlayToLearn::Backend::TransitionFn;

BOOST_AUTO_TEST_CASE(basic_use_test) {
  // Create three simple states:
  State s_a;
  State s_b(State::ID(1));
  State s_c(State::ID(200));
  
  // Check that the IDs match:
  BOOST_CHECK_EQUAL(s_a.id(), State::ID());
  BOOST_CHECK_EQUAL(s_b.id(), State::ID(1));
  BOOST_CHECK_EQUAL(s_c.id(), State::ID(200));
}
