/*
 * File: Engine.cpp
 */

#include "Engine.hpp"

using namespace std;

namespace PlayToLearn {
namespace Backend {

///////////////////////////////////////////////////
// Engine member function implementation details //
///////////////////////////////////////////////////

/** public */

const AttributeMap& Engine::register_interaction(const AttributeMap& interaction) {
  const State& current_state = state_machine.current_state();
  //if (current_state
}

} // namespace Backend
} // namespace PlayToLearn
