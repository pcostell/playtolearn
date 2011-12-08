/*
 * File: test/backend/TransitionFnTest.cpp
 */

#define BOOST_TEST_MODULE TransitionFn test

#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/test/unit_test.hpp>

#include "util/ErrorTypes.hpp"
#include "backend/AttributeMap.hpp"
#include "backend/State.hpp"
#include "backend/TransitionFn.hpp"

using namespace std;
using PlayToLearn::Util::InvalidStateIndexError;
using PlayToLearn::Util::MissingTransitionFnScriptError;
using PlayToLearn::Backend::AttributeMap;
using PlayToLearn::Backend::State;
using PlayToLearn::Backend::TransitionFn;

BOOST_AUTO_TEST_CASE(id_test) {
  // Create some transition functions:
  TransitionFn fn_a;
  TransitionFn fn_b(TransitionFn::ID(3));
  TransitionFn fn_c(TransitionFn::ID(29));
  
  // Check that the IDs match:
  BOOST_CHECK_EQUAL(fn_a.id(), TransitionFn::ID());
  BOOST_CHECK_EQUAL(fn_b.id(), TransitionFn::ID(3));
  BOOST_CHECK_EQUAL(fn_c.id(), TransitionFn::ID(29));
}

BOOST_AUTO_TEST_CASE(states_test) {
  // Create a transition function and add some states:
  TransitionFn fn;
  fn.add_state(State::ID(3));
  fn.add_state(State::ID(2));
  fn.add_state(State::ID());
  fn.add_state(State::ID(50));
  
  // Check that the function has consistent state data:
  BOOST_CHECK_EQUAL(fn.num_states(), 4);
  BOOST_CHECK_EQUAL(fn.state_at(0), State::ID(3));
  BOOST_CHECK_EQUAL(fn.state_at(1), State::ID(2));
  BOOST_CHECK_EQUAL(fn.state_at(2), State::ID());
  BOOST_CHECK_EQUAL(fn.state_at(3), State::ID(50));
  
  // Check removal of states:
  fn.remove_state(2);
  BOOST_CHECK_EQUAL(fn.num_states(), 3);
  BOOST_CHECK_EQUAL(fn.state_at(0), State::ID(3));
  BOOST_CHECK_EQUAL(fn.state_at(1), State::ID(2));
  BOOST_CHECK_EQUAL(fn.state_at(2), State::ID(50));
}

BOOST_AUTO_TEST_CASE(bad_state_test) {
  // Create a transition function and add some states:
  TransitionFn fn;
  fn.add_state(State::ID(3));
  fn.add_state(State::ID(2));
  fn.add_state(State::ID());
  fn.add_state(State::ID(50));
  
  // Check that the proper exceptions are thrown:
  BOOST_CHECK_THROW(fn.state_at(-1), InvalidStateIndexError);
  BOOST_CHECK_THROW(fn.state_at(4), InvalidStateIndexError);
  BOOST_CHECK_THROW(fn.state_at(30), InvalidStateIndexError);
  BOOST_CHECK_THROW(fn.remove_state(-30), InvalidStateIndexError);
  BOOST_CHECK_THROW(fn.remove_state(5), InvalidStateIndexError);
  BOOST_CHECK_THROW(fn.remove_state(60), InvalidStateIndexError);
}

BOOST_AUTO_TEST_CASE(python_code_test) {
  // Create two transition functions and add some states:
  TransitionFn fn_a(TransitionFn::ID(0));
  fn_a.add_state(State::ID(3));
  fn_a.add_state(State::ID(2));
  fn_a.add_state(State::ID());
  fn_a.add_state(State::ID(50));
  TransitionFn fn_b(TransitionFn::ID(1));
  fn_b.add_state(State::ID(1));
  fn_b.add_state(State::ID(8));
  
  // The Python code:
  string code = "def state_transition_0(am, gs):\n";
  code += "  if am['answer'] == 'A':\n";
  code += "    return 0\n";
  code += "  elif am['answer'] == 'B':\n";
  code += "    return 1\n";
  code += "  elif am['answer'] == 'C':\n";
  code += "    return 2\n";
  code += "  return 3\n";
  fn_a.set_python_function(code);
  code  = "def state_transition_1(am, gs):\n";
  code += "  if am['answer'] == 'A':\n";
  code += "    return 0\n";
  code += "  return 1\n";
  fn_b.set_python_function(code);
  AttributeMap interaction, global_state;
  
  // Execute the code and test for the right answers:
  interaction.set_value("answer", "A");
  BOOST_CHECK_EQUAL(fn_a.next_state(interaction, global_state), State::ID(3));
  BOOST_CHECK_EQUAL(fn_b.next_state(interaction, global_state), State::ID(1));
  
  interaction.set_value("answer", "B");
  BOOST_CHECK_EQUAL(fn_a.next_state(interaction, global_state), State::ID(2));
  BOOST_CHECK_EQUAL(fn_b.next_state(interaction, global_state), State::ID(8));
  
  interaction.set_value("answer", "C");
  BOOST_CHECK_EQUAL(fn_a.next_state(interaction, global_state), State::ID());
  BOOST_CHECK_EQUAL(fn_b.next_state(interaction, global_state), State::ID(8));
  
  interaction.set_value("answer", "D");
  BOOST_CHECK_EQUAL(fn_a.next_state(interaction, global_state), State::ID(50));
  BOOST_CHECK_EQUAL(fn_b.next_state(interaction, global_state), State::ID(8));
}

BOOST_AUTO_TEST_CASE(bad_script_test) {
  // Create a transition function and add some states:
  TransitionFn fn;
  fn.add_state(State::ID(3));
  fn.add_state(State::ID(2));
  fn.add_state(State::ID());
  fn.add_state(State::ID(50));
  AttributeMap interaction, global_state;
  
  // Check that the proper exception is thrown;
  BOOST_CHECK_THROW(fn.next_state(interaction, global_state), MissingTransitionFnScriptError);
}
