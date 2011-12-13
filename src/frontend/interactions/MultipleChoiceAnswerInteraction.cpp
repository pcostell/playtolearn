/*
 * File: frontend/interactions/MultipleChoiceAnswerInteraction.cpp
 */

#include "frontend/interactions/MultipleChoiceAnswerInteraction.hpp"

#include "util/Constants.hpp"
#include "backend/Object.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** MultipleChoiceAnswerInteraction member functions, public */

MultipleChoiceAnswerInteraction::MultipleChoiceAnswerInteraction(Backend::Object::ID object_id, int answer_index) :
  Interaction(object_id),
  answer_index_(answer_index)
{
  set_value(Util::kMCAnswerIndexAttribute, answer_index);
}

} // namespace Frontend
} // namespace PlayToLearn
