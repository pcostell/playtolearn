/*
 * File: frontend/FreeResponseAnswerInteraction.cpp
 */

#include "util/Constants.hpp"
#include "frontend/FreeResponseAnswerInteraction.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/////////////////////////////////////////////////////////////////
// FreeResponseAnswerInteraction member implementation details //
/////////////////////////////////////////////////////////////////

/** public */

FreeResponseAnswerInteraction::FreeResponseAnswerInteraction(Backend::Object::ID object_id, const string& answer) :
  Interaction(object_id)
{
  set_value(Util::kFreeResponseAnswerAttribute, answer);
}

} // namespace Frontend
} // namespace PlayToLearn
