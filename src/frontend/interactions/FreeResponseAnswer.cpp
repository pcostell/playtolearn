/*
 * File: frontend/interactions/FreeResponseAnswer.cpp
 */

#include "frontend/interactions/FreeResponseAnswer.hpp"

#include "util/Constants.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** FreeResponseAnswer member functions, public */

FreeResponseAnswer::FreeResponseAnswer(Util::UniqueID<Backend::Object> object_id, const string& answer) :
  Interaction(object_id)
{
  set_value(Util::kFreeResponseAnswerAttribute, answer);
}

} // namespace Frontend
} // namespace PlayToLearn
