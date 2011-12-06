/*
 * File: frontend/interactions/Interaction.cpp
 */

#include "frontend/interactions/Interaction.hpp"

#include "util/Constants.hpp"
#include "backend/Object.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** Interaction member functions, public */

Interaction::Interaction(Backend::Object::ID object_id) : object_id_(object_id)
{
  set_value(Util::kObjectIDAttribute, object_id.value());
}

Interaction::~Interaction() {
  // empty body
}

} // namespace Frontend
} // namespace PlayToLearn
