/*
 * File: frontend/interactions/FreeResponsePrompt.cpp
 */

#include "frontend/interactions/FreeResponsePrompt.hpp"

#include "util/Constants.hpp"
#include "backend/AttributeMap.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** FreeResponsePrompt member functions, public */

FreeResponsePrompt::FreeResponsePrompt(const Backend::AttributeMap& data) :
  text_(data.value<string>(Util::kTextAttribute))
{
  // empty body
}

} // namespace Frontend
} // namespace PlayToLearn
