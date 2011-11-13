/*
 * File: backend/TransitionFn.cpp
 */

#include "backend/TransitionFn.hpp"
#include "backend/State.hpp"

using namespace std;

namespace PlayToLearn {
namespace Backend {

////////////////////////////////////////////////
// TransitionFn member implementation details //
////////////////////////////////////////////////

/** public */

TransitionFn::TransitionFn(ID id) : id_(id) {
  // empty body
}

State::ID TransitionFn::next_state(const AttributeMap& interaction) const {
  return State::ID();
  // TODO: provide actual implementation
}

} // namespace Backend
} // namespace PlayToLearn
