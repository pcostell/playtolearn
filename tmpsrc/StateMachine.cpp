/*
 * File: StateMachine.cpp
 */

#include "StateMachine.hpp"
#include <cassert>

using namespace std;

namespace PlayToLearn {
namespace Backend {

////////////////////////////////////////////////
// StateMachine member implementation details //
////////////////////////////////////////////////

/** public */

const State& StateMachine::state(State::ID id) const {
  map<State::ID, State>::const_iterator itr = state_map_.find(id);
  assert(itr != state_map_.end());
  return itr->second;
}

const TransitionFn& StateMachine::transition_fn(TransitionFn::ID id) const {
  map<TransitionFn::ID, TransitionFn>::const_iterator itr = transition_fn_map_.find(id);
  assert(itr != transition_fn_map_.end());
  return itr->second;
}

} // namespace Backend
} // namespace PlayToLearn
