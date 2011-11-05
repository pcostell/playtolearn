/*
 * File: TextResponse.cpp
 */

#include "TextResponse.hpp"

using namespace std;

namespace PlayToLearn {

////////////////////////////////////////////////
// TextResponse member implementation details //
////////////////////////////////////////////////

/** public */

TextResponse::TextResponse(const Backend::AttributeMap& data) :
  InteractionResponse(data) {
  // TODO: implement
  text_ = data.value<string>("text");
}

} // namespace PlayToLearn
