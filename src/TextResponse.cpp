/*
 * File: TextResponse.cpp
 */

#include "TextResponse.hpp"

using namespace std;

namespace PlayToLearn {

////////////////////////////
// TextResponse constants //
////////////////////////////

/** public */

const string TextResponse::kTextAttribute("ir_text");

////////////////////////////////////////////////
// TextResponse member implementation details //
////////////////////////////////////////////////

/** public */

TextResponse::TextResponse(const Backend::AttributeMap& data) :
  InteractionResponse(data),
  text_(data.value<string>(kTextAttribute))
{
  // TODO: implement
  text_ = data.value<string>("text");
}

} // namespace PlayToLearn
