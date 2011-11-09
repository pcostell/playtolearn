/*
 * File: frontend/Interaction.cpp
 */

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
  set_value(Backend::Object::kObjectIDAttribute, object_id.value());
}

} // namespace Frontend
} // namespace PlayToLearn
