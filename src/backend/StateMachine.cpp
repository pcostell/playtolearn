/*
 * File: backend/StateMachine.cpp
 */

#include "backend/StateMachine.hpp"
#include "util/ErrorTypes.hpp"
#include <sstream>

using namespace std;

namespace PlayToLearn {
namespace Backend {

////////////////////////////////////////////////
// StateMachine member implementation details //
////////////////////////////////////////////////

/** public */

const State& StateMachine::state(State::ID id) const {
  map<State::ID, State>::const_iterator itr = state_map_.find(id);
  if (itr == state_map_.end()) {
    stringstream err_ss;
    err_ss << "Invalid state ID requested: " << id.value();
    throw Util::InvalidStateError(err_ss.str(), id.value());
  }
  
  return itr->second;
}

const TransitionFn& StateMachine::transition_fn(TransitionFn::ID id) const {
  map<TransitionFn::ID, TransitionFn>::const_iterator itr = transition_fn_map_.find(id);
  if (itr == transition_fn_map_.end()) {
    stringstream err_ss;
    err_ss << "Invalid transition function ID requested: " << id.value();
    throw Util::InvalidTransitionFnError(err_ss.str(), id.value());
  }
  
  return itr->second;
}

} // namespace Backend
} // namespace PlayToLearn
