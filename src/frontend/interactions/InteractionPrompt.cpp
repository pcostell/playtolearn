/*
 * File: frontend/interactions/InteractionPrompt.cpp
 */

#include "frontend/interactions/InteractionPrompt.hpp"

#include <stdexcept>
#include <sstream>

#include <boost/make_shared.hpp>

#include "util/Constants.hpp"
#include "util/ErrorTypes.hpp"
#include "frontend/interactions/TextPrompt.hpp"
#include "frontend/interactions/FreeResponsePrompt.hpp"
#include "frontend/interactions/MultipleChoicePrompt.hpp"
#include "backend/AttributeMap.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** InteractionPrompt member functions, public */

InteractionPrompt::InteractionPrompt(const Backend::AttributeMap& data) :
  state_id_(data.value<int>(Util::kStateIDAttribute)),
  object_id_(data.value<int>(Util::kObjectIDAttribute))
{
  // empty body
}

InteractionPrompt::~InteractionPrompt() {
  // empty body
}

/** InteractionPrompt class functions, public */

InteractionPrompt::Ptr InteractionPrompt::create(const Backend::AttributeMap& data) {
  // Extract the prompt type as a string and check to see if it's a valid value:
  string prompt_type = data.value<string>(Util::kInteractionPromptTypeAttribute);
  if (prompt_type == Util::kTextPromptTypeValue) {
    return boost::make_shared<TextPrompt>(data);
  } else if (prompt_type == Util::kFreeResponsePromptTypeValue) {
    return boost::make_shared<FreeResponsePrompt>(data);
  } else if (prompt_type == Util::kMultipleChoicePromptTypeValue) {
    return boost::make_shared<MultipleChoicePrompt>(data);
  } else {
    throw Util::InvalidInteractionPromptTypeError(prompt_type);
  }
  
  // This will never execute due to the throw in the else clause, but we will
  // put this here to appease the compiler.
  return InteractionPrompt::Ptr();
}

} // namespace Frontend
} // namespace PlayToLearn
