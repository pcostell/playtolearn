/*
 * File: frontend/interactions/MultipleChoicePrompt.cpp
 */

#include "frontend/interactions/MultipleChoicePrompt.hpp"

#include <boost/lexical_cast.hpp>

#include "util/Constants.hpp"
#include "backend/AttributeMap.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** MultipleChoicePrompt member functions, public */

MultipleChoicePrompt::MultipleChoicePrompt(const Backend::AttributeMap& data) :
  InteractionPrompt(data),
  text_(data.value<string>(Util::kTextAttribute)),
  choices_(data.value<int>(Util::kNumMCChoicesAttribute))
{
  for (size_t i = 0; i < choices_.size(); ++i)
    choices_[i] = data.value<string>(Util::kMCChoiceAttribute + boost::lexical_cast<string>(i));
}

} // namespace Frontend
} // namespace PlayToLearn
