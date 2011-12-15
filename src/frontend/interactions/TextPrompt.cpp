/*
 * File: frontend/interactions/TextPrompt.cpp
 */

#include "frontend/interactions/TextPrompt.hpp"

#include "util/Constants.hpp"
#include "backend/AttributeMap.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** TextPrompt member functions, public */

TextPrompt::TextPrompt(const Backend::AttributeMap& data) :
  InteractionPrompt(data),
  text_(data.value<string>(Util::kTextAttribute))
{
  // empty body
}

} // namespace Frontend
} // namespace PlayToLearn
