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

Frontend::InteractionResponse::Ptr Engine::register_interaction(Frontend::Interaction::Ptr interaction) {
  const State& current_state = state_machine_.current_state();
  if (!current_state.object_exists(interaction->object_id())) {
    // TODO: handle default interaction, perhaps?
    return Frontend::InteractionResponse::Ptr();
  }
  
  // Check if the frontend is simply asking for the data needed to set up an
  // interaction:
  if (interaction->requesting_data()) {
    // TODO: find the AttributeMap associated with this particular Object/State
    // combination and use that to construct InteractionResponse.
  }
  
  // TODO: implement
  AttributeMap data;
  return Frontend::InteractionResponse::create(data);
}

} // namespace Backend
} // namespace PlayToLearn
