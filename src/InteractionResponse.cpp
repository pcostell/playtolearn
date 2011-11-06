/*
 * File: InteractionResponse.hpp
 */

#include "InteractionResponse.hpp"

using namespace std;

namespace PlayToLearn {

///////////////////////////////////////////////////////
// InteractionResponse member implementation details //
///////////////////////////////////////////////////////

/** public */

InteractionResponse::InteractionResponse(const Backend::AttributeMap& data) :
  state_id_(data.value<int>(Backend::State::kStateIDAttribute)),
  object_id_(data.value<int>(Backend::Object::kObjectIDAttribute)),
  forced_interaction_id_(data.value<int>(Backend::Object::kForcedInteractionIDAttribute))
{
  // empty body
}

InteractionResponse::~InteractionResponse() {
  // TODO: implement
}

} // namespace PlayToLearn
