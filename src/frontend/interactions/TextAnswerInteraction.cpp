/*
 * File: frontend/interactions/TextAnswerInteraction.cpp
 */

#include "frontend/interactions/TextAnswerInteraction.hpp"

#include "backend/Object.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** TextAnswerInteraction member functions, public */

TextAnswerInteraction::TextAnswerInteraction(Backend::Object::ID object_id) :
  Interaction(object_id)
{
  // empty body
}

} // namespace Frontend
} // namespace PlayToLearn
