/*
 * File: backend/Engine.cpp
 */

#include "backend/Engine.hpp"

using namespace std;

namespace PlayToLearn {
namespace Backend {

///////////////////////////////////////////////////
// Engine member function implementation details //
///////////////////////////////////////////////////

/** public */

const AttributeMap& Engine::register_interaction(const AttributeMap& interaction) {
  const State& current_state = state_machine_.current_state();
}

} // namespace Backend
} // namespace PlayToLearn
