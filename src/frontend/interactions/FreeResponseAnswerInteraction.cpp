/*
 * File: frontend/interactions/FreeResponseAnswerInteraction.cpp
 */

#include "frontend/interactions/FreeResponseAnswerInteraction.hpp"

#include "util/Constants.hpp"
#include "backend/Object.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** FreeResponseAnswerInteraction member functions, public */

FreeResponseAnswerInteraction::FreeResponseAnswerInteraction(Backend::Object::ID object_id, const string& answer) :
  Interaction(object_id)
{
  set_value(Util::kFreeResponseAnswerAttribute, answer);
}

} // namespace Frontend
} // namespace PlayToLearn
