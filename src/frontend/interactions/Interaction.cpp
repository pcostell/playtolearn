/*
 * File: frontend/interactions/Interaction.cpp
 */

#include "frontend/interactions/Interaction.hpp"

#include "util/Constants.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** Interaction member functions, public */

Interaction::Interaction(Util::UniqueID<Backend::Object> object_id) :
  object_id_(object_id)
{
  // empty body
}

Interaction::~Interaction() {
  // empty body
}

} // namespace Frontend
} // namespace PlayToLearn
