/*
 * File: test/backend/StateTest.cpp
 */

#define BOOST_TEST_MODULE State test

#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/test/unit_test.hpp>

#include "util/ErrorTypes.hpp"
#include "backend/State.hpp"
#include "backend/Object.hpp"
#include "backend/TransitionFn.hpp"

using namespace std;
using PlayToLearn::Util::InvalidObjectError;
using PlayToLearn::Backend::State;
using PlayToLearn::Backend::Object;
using PlayToLearn::Backend::TransitionFn;

BOOST_AUTO_TEST_CASE(id_test) {
  // Create some states:
  State s_a;
  State s_b(State::ID(1));
  State s_c(State::ID(200));
  
  // Check that the IDs match:
  BOOST_CHECK_EQUAL(s_a.id(), State::ID());
  BOOST_CHECK_EQUAL(s_b.id(), State::ID(1));
  BOOST_CHECK_EQUAL(s_c.id(), State::ID(200));
}

BOOST_AUTO_TEST_CASE(object_test) {
  // Create a state and add some object IDs:
  State s;
  s.insert_object(Object::ID(1), TransitionFn::ID(4));
  s.insert_object(Object::ID(2), TransitionFn::ID(6));
  s.insert_object(Object::ID(3), TransitionFn::ID(2));
  
  // Check that the objects can be found:
  BOOST_CHECK(s.contains_object(Object::ID(1)));
  BOOST_CHECK(s.contains_object(Object::ID(2)));
  BOOST_CHECK(s.contains_object(Object::ID(3)));
  BOOST_CHECK(!s.contains_object(Object::ID(4)));
  
  // Check that the transition function IDs match:
  BOOST_CHECK_EQUAL(s.transition_fn_id(Object::ID(1)), TransitionFn::ID(4));
  BOOST_CHECK_EQUAL(s.transition_fn_id(Object::ID(2)), TransitionFn::ID(6));
  BOOST_CHECK_EQUAL(s.transition_fn_id(Object::ID(3)), TransitionFn::ID(2));
  
  // Check that iteration through the object IDs works:
  State::object_iterator itr = s.object_begin();
  BOOST_CHECK_EQUAL(itr->first, Object::ID(1));
  BOOST_CHECK_EQUAL(itr->second, TransitionFn::ID(4));
  ++itr;
  
  BOOST_CHECK_EQUAL(itr->first, Object::ID(2));
  BOOST_CHECK_EQUAL(itr->second, TransitionFn::ID(6));
  ++itr;
  
  BOOST_CHECK_EQUAL(itr->first, Object::ID(3));
  BOOST_CHECK_EQUAL(itr->second, TransitionFn::ID(2));
  ++itr;
  
  if (itr != s.object_end())
    BOOST_ERROR("Iterator hasn't reached end when it should.");
  
  // Check that removal of object IDs works:
  s.remove_object(Object::ID(2));
  BOOST_CHECK(!s.contains_object(Object::ID(2)));
}

BOOST_AUTO_TEST_CASE(bad_object_lookup) {
  // Create a state and add some object IDs:
  State s;
  s.insert_object(Object::ID(1), TransitionFn::ID(4));
  s.insert_object(Object::ID(2), TransitionFn::ID(6));
  s.insert_object(Object::ID(3), TransitionFn::ID(2));
  
  // Check that a bad lookup throws an exception:
  BOOST_CHECK_THROW(s.transition_fn_id(Object::ID(4)), InvalidObjectError);
}

bool StatesEquivalent(const State& s_a, const State& s_b) {
  if (s_a.id() != s_b.id())
    return false;
  
  State::const_object_iterator itr_a = s_a.object_begin();
  State::const_object_iterator itr_b = s_b.object_begin();
  while (itr_a != s_a.object_end()) {
    if (itr_b == s_b.object_end())
      return false;
    if (itr_a->first != itr_b->first)
      return false;
    if (itr_a->second != itr_b->second)
      return false;
    
    ++itr_a;
    ++itr_b;
  }
  
  return true;
}

BOOST_AUTO_TEST_CASE(input_output_test) {
  // Create a state and add some object IDs:
  State s_a(State::ID(2));
  s_a.insert_object(Object::ID(1), TransitionFn::ID(4));
  s_a.insert_object(Object::ID(2), TransitionFn::ID(6));
  s_a.insert_object(Object::ID(3), TransitionFn::ID(2));
  
  // Write our state object out to a file:
  ofstream output_file("test.xml");
  boost::archive::xml_oarchive output_archive(output_file);
  output_archive << boost::serialization::make_nvp("State", s_a);
  output_file.close();
  
  // Read the same state in from the file:
  State s_b;
  ifstream input_file("test.xml");
  boost::archive::xml_iarchive input_archive(input_file);
  input_archive >> boost::serialization::make_nvp("State", s_b);
  input_file.close();
  
  // Ensure that the two states are the same:
  BOOST_CHECK(StatesEquivalent(s_a, s_b));
}
