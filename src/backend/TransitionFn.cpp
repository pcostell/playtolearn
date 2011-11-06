/*
 * File: TransitionFn.cpp
 */

#include "TransitionFn.hpp"
#include "State.hpp"

using namespace std;

namespace PlayToLearn {
namespace Backend {

////////////////////////////////////////////////
// TransitionFn member implementation details //
////////////////////////////////////////////////

/** public */

TransitionFn::TransitionFn(const AttributeMap& response, ID id) :
  id_(id),
  response_(response)
{
  // empty body
}

State::ID TransitionFn::next_state(const AttributeMap& interaction) const {
  return State::ID();
}

} // namespace Backend
} // namespace PlayToLearn
