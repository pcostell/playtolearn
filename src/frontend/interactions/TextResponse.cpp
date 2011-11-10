/*
 * File: frontend/interactions/TextResponse.cpp
 */

#include "util/Constants.hpp"
#include "frontend/interactions/TextResponse.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

////////////////////////////////////////////////
// TextResponse member implementation details //
////////////////////////////////////////////////

/** public */

TextResponse::TextResponse(const Backend::AttributeMap& data) :
  InteractionResponse(data),
  text_(data.value<string>(Util::kTextAttribute))
{
  // empty body
}

} // namespace Frontend
} // namespace PlayToLearn
