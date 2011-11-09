/*
 * File: frontend/Interaction.cpp
 */

#include "util/Constants.hpp"
#include "frontend/Interaction.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

///////////////////////////////////////////////
// Interaction member implementation details //
///////////////////////////////////////////////

/** public */

Interaction::Interaction(Backend::Object::ID object_id) : object_id_(object_id)
{
  set_value(Util::kObjectIDAttribute, object_id.value());
}

Interaction::~Interaction() {
  // empty bodied
}

} // namespace Frontend
} // namespace PlayToLearn
