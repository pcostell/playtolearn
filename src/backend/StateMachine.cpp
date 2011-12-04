/*
 * File: backend/StateMachine.cpp
 */

#include "backend/StateMachine.hpp"

#include <sstream>

#include "util/ErrorTypes.hpp"

using namespace std;

namespace PlayToLearn {
namespace Backend {

/** StateMachine member functions, public */

const State& StateMachine::state(State::ID id) const {
  map<State::ID, State>::const_iterator itr = state_map_.find(id);
  if (itr == state_map_.end())
    throw Util::InvalidStateError(id.value());
  
  return itr->second;
}

bool StateMachine::contains_state(State::ID id) const {
  return state_map_.count(id);
}

void StateMachine::add_state(const State& state) {
  state_map_.insert(make_pair(state.id(), state));
}

void StateMachine::remove_state(State::ID id) {
  state_map_.erase(id);
}

const TransitionFn& StateMachine::transition_fn(TransitionFn::ID id) const {
  map<TransitionFn::ID, TransitionFn>::const_iterator itr = transition_fn_map_.find(id);
  if (itr == transition_fn_map_.end())
    throw Util::InvalidTransitionFnError(id.value());
  
  return itr->second;
}

bool StateMachine::contains_transition_fn(TransitionFn::ID id) const {
  return transition_fn_map_.count(id);
}

void StateMachine::add_transition_fn(const TransitionFn& transition_fn) {
  transition_fn_map_.insert(make_pair(transition_fn.id(), transition_fn));
}

void StateMachine::remove_transition_fn(TransitionFn::ID id) {
  transition_fn_map_.erase(id);
}

} // namespace Backend
} // namespace PlayToLearn
