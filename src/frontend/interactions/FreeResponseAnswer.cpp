/*
 * File: frontend/interactions/FreeResponseAnswer.cpp
 */

#include "frontend/interactions/FreeResponseAnswer.hpp"

#include "util/Constants.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** FreeResponseAnswer member functions, public */

FreeResponseAnswer::FreeResponseAnswer(Util::UniqueID<Backend::Object> id, const string& answer) :
  Interaction(id)
{
  set_value(Util::kFreeResponseAnswerAttribute, answer);
}

} // namespace Frontend
} // namespace PlayToLearn
