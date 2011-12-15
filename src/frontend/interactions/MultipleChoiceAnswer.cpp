/*
 * File: frontend/interactions/MultipleChoiceAnswer.cpp
 */

#include "frontend/interactions/MultipleChoiceAnswer.hpp"

#include "util/Constants.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** MultipleChoiceAnswer member functions, public */

MultipleChoiceAnswer::MultipleChoiceAnswer(Util::UniqueID<Backend::Object> id, int answer_index) :
  Interaction(id),
  answer_index_(answer_index)
{
  set_value(Util::kMCAnswerIndexAttribute, answer_index);
}

} // namespace Frontend
} // namespace PlayToLearn
