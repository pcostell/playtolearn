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
  // Check if the object has an interaction available for this state:
  const State& current_state = state_machine_.current_state();
  if (!current_state.object_exists(interaction->object_id()))
    return Frontend::InteractionResponse::Ptr();
  
  // This is the transition function associated with this object/state pair:
  TransitionFn::ID fn_id = current_state.transition_fn_id(interaction->object_id());
  
  // Check if the frontend is simply asking for the data needed to set up an
  // interaction:
  if (interaction->requesting_data())
    return Frontend::InteractionResponse::create(transition_data_.find(fn_id)->second);
  
  // Move to the new state:
  const TransitionFn& transition_fn = state_machine_.transition_fn(fn_id);
  State::ID new_state_id = transition_fn.next_state(interaction->attribute_map(), global_state_);
  state_machine_.set_current_state(new_state_id);
  
  // Return the proper interaction response:
  const State& new_state = state_machine_.current_state();
  if (!interaction->requesting_data() || !new_state.object_exists(interaction->object_id()))
    return Frontend::InteractionResponse::Ptr();
  
  fn_id = new_state.transition_fn_id(interaction->object_id());
  return Frontend::InteractionResponse::create(transition_data_.find(fn_id)->second);
}

} // namespace Backend
} // namespace PlayToLearn
