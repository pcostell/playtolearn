/*
 * File: frontend/InteractionResponse.hpp
 */

#include "frontend/InteractionResponse.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

///////////////////////////////////////////////////////
// InteractionResponse member implementation details //
///////////////////////////////////////////////////////

/** public */

InteractionResponse::InteractionResponse(const Backend::AttributeMap& data) :
  state_id_(data.value<int>(Backend::State::kStateIDAttribute)),
  object_id_(data.value<int>(Backend::Object::kObjectIDAttribute))
{
  // empty body
}

InteractionResponse::~InteractionResponse() {
  // empty body
}

} // namespace Frontend
} // namespace PlayToLearn
