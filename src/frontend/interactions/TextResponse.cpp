/*
 * File: frontend/interactions/TextResponse.cpp
 */

#include "frontend/interactions/TextResponse.hpp"

#include "util/Constants.hpp"
#include "backend/AttributeMap.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** TextResponse member functions, public */

TextResponse::TextResponse(const Backend::AttributeMap& data) :
  InteractionResponse(data),
  text_(data.value<string>(Util::kTextAttribute))
{
  // empty body
}

} // namespace Frontend
} // namespace PlayToLearn
