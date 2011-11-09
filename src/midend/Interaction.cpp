/*
 * File: midend/Interaction.cpp
 */

#include "midend/Interaction.hpp"

using namespace std;

namespace PlayToLearn {
namespace Midend {

///////////////////////////////////////////////
// Interaction member implementation details //
///////////////////////////////////////////////

/** public */

Interaction::Interaction(Backend::Object::ID object_id) : object_id_(object_id)
{
  set_value(Backend::Object::kObjectIDAttribute, object_id.value());
}

} // namespace Midend
} // namespace PlayToLearn
