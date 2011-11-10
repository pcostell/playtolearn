/*
 * File: frontend/interactions/MultipleChoiceAnswerInteraction.cpp
 */

#include "util/Constants.hpp"
#include "frontend/interactions/MultipleChoiceAnswerInteraction.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

///////////////////////////////////////////////////////////////////
// MultipleChoiceAnswerInteraction member implementation details //
///////////////////////////////////////////////////////////////////

/** public */

MultipleChoiceAnswerInteraction::MultipleChoiceAnswerInteraction(Backend::Object::ID object_id, int answer_index) :
  Interaction(object_id),
  answer_index_(answer_index)
{
  set_value(Util::kMCAnswerIndexAttribute, answer_index);
}

} // namespace Frontend
} // namespace PlayToLearn
