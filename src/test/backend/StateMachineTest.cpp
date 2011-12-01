/*
 * File: test/backend/StateMachineTest.cpp
 */

#define BOOST_TEST_MODULE StateMachine test

#include "util/ErrorTypes.hpp"
#include "backend/StateMachine.hpp"
#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/test/unit_test.hpp>

using namespace std;
using PlayToLearn::Util::InvalidStateError;
using PlayToLearn::Util::InvalidTransitionFnError;
using PlayToLearn::Backend::StateMachine;
using PlayToLearn::Backend::State;
using PlayToLearn::Backend::TransitionFn;

BOOST_AUTO_TEST_CASE(containment_test) {
  // Create our simple state machine:
  StateMachine sm;
  State state_a(State::ID(1));
  State state_b(State::ID(2));
  TransitionFn transition_fn_a(TransitionFn::ID(1));
  
  sm.add_state(state_a);
  sm.add_state(state_b);
  sm.add_transition_fn(transition_fn_a);
  
  // Check their containment:
  BOOST_CHECK(sm.contains_state(state_a.id()));
  BOOST_CHECK(sm.contains_state(state_b.id()));
  BOOST_CHECK(sm.contains_transition_fn(transition_fn_a.id()));
  
  // Check state lookup:
  State& state_c = sm.state(State::ID(1));
  State& state_d = sm.state(State::ID(2));
  BOOST_CHECK_EQUAL(state_c.id(), State::ID(1));
  BOOST_CHECK_EQUAL(state_d.id(), State::ID(2));
  
  // Check that the state machine doesn't contain other bogus stuff:
  BOOST_CHECK(!sm.contains_state(State::ID(3)));
  BOOST_CHECK(!sm.contains_state(State::ID(15)));
  BOOST_CHECK(!sm.contains_state(State::ID()));
  BOOST_CHECK(!sm.contains_transition_fn(TransitionFn::ID(2)));
  BOOST_CHECK(!sm.contains_transition_fn(TransitionFn::ID(10)));
  BOOST_CHECK(!sm.contains_transition_fn(TransitionFn::ID()));
  
  // Check the removal of a state:
  sm.remove_state(state_a.id());
  BOOST_CHECK(!sm.contains_state(state_a.id()));
  BOOST_CHECK(sm.contains_state(state_b.id()));
}

BOOST_AUTO_TEST_CASE(current_state_test) {
  // Create our simple state machine:
  StateMachine sm;
  State state_a(State::ID(1));
  State state_b(State::ID(2));
  sm.add_state(state_a);
  sm.add_state(state_b);
  
  // Check the switching of the current state:
  sm.set_current_state(state_a.id());
  State& state_c = sm.current_state();
  BOOST_CHECK_EQUAL(state_a.id(), sm.current_state_id());
  BOOST_CHECK_EQUAL(state_a.id(), state_c.id());
  
  sm.set_current_state(state_b.id());
  State& state_d = sm.current_state();
  BOOST_CHECK_EQUAL(state_b.id(), sm.current_state_id());
  BOOST_CHECK_EQUAL(state_b.id(), state_d.id());
}

BOOST_AUTO_TEST_CASE(bad_lookup) {
  // Create our simple state machine:
  StateMachine sm;
  State state_a(State::ID(1));
  State state_b(State::ID(2));
  sm.add_state(state_a);
  sm.add_state(state_b);
  sm.set_current_state(State::ID(4));
  
  // Check that these operations indeed throw exceptions:
  BOOST_CHECK_THROW(sm.state(State::ID(3)), InvalidStateError);
  BOOST_CHECK_THROW(sm.current_state(), InvalidStateError);
  BOOST_CHECK_THROW(sm.transition_fn(TransitionFn::ID(1)), InvalidTransitionFnError);
}

BOOST_AUTO_TEST_CASE(input_output_test) {
  // Create our simple state machines:
  StateMachine sm_a;
  State state_a(State::ID(1));
  State state_b(State::ID(2));
  TransitionFn transition_fn_a(TransitionFn::ID(1));
  transition_fn_a.add_state(State::ID(1));
  
  sm_a.add_state(state_a);
  sm_a.add_state(state_b);
  sm_a.add_transition_fn(transition_fn_a);
  
  // Write our StateMachine out to a file:
  ofstream output_file("test.xml");
  boost::archive::xml_oarchive output_archive(output_file);
  output_archive << boost::serialization::make_nvp("StateMachine", sm_a);
  output_file.close();
  
  // Read the same StateMachine in from the file:
  StateMachine sm_b;
  ifstream input_file("test.xml");
  boost::archive::xml_iarchive input_archive(input_file);
  input_archive >> boost::serialization::make_nvp("StateMachine", sm_b);
  input_file.close();
  
  // Ensure that the two state machines are the same:
  BOOST_CHECK(sm_b.contains_state(state_a.id()));
  BOOST_CHECK(sm_b.contains_state(state_b.id()));
  BOOST_CHECK(sm_b.contains_transition_fn(transition_fn_a.id()));
  
  // Check TransitionFn serialization:
  TransitionFn& transition_fn_b = sm_b.transition_fn(transition_fn_a.id());
  BOOST_CHECK_EQUAL(transition_fn_a.num_states(), transition_fn_b.num_states());
  for (int i = 0; i < transition_fn_a.num_states(); ++i)
    BOOST_CHECK_EQUAL(transition_fn_a.state_at(i), transition_fn_b.state_at(i));
}
