/*
 * File: backend/StateMachine.cpp
 */

#include "backend/StateMachine.hpp"
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
    throw InvalidStateError(err_ss.str(), id);
  }
  
  return itr->second;
}

const TransitionFn& StateMachine::transition_fn(TransitionFn::ID id) const {
  map<TransitionFn::ID, TransitionFn>::const_iterator itr = transition_fn_map_.find(id);
  if (itr == transition_fn_map_.end()) {
    stringstream err_ss;
    err_ss << "Invalid transition function ID requested: " << id.value();
    throw InvalidTransitionFnError(err_ss.str(), id);
  }
  
  return itr->second;
}

/////////////////////////////////////////////////////
// InvalidStateError member implementation details //
/////////////////////////////////////////////////////

/** public */

InvalidStateError::InvalidStateError(const string& what_arg, State::ID id) :
  runtime_error(what_arg), state_id_(id)
{
  // empty body
}

////////////////////////////////////////////////////////////
// InvalidTransitionFnError member implementation details //
////////////////////////////////////////////////////////////

/** public */

InvalidTransitionFnError::InvalidTransitionFnError(const string& what_arg, TransitionFn::ID id) :
  runtime_error(what_arg), transition_fn_id_(id)
{
  // empty body
}

} // namespace Backend
} // namespace PlayToLearn
