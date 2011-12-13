/*
 * File: frontend/interactions/GenericInteraction.cpp
 */

#include "frontend/interactions/GenericInteraction.hpp"

#include "backend/Object.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** GenericInteraction member functions, public */

GenericInteraction::GenericInteraction(Backend::Object::ID object_id) :
  Interaction(object_id)
{
  // empty body
}

} // namespace Frontend
} // namespace PlayToLearn
