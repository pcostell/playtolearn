/*
 * File: midend/FreeResponseResponse.cpp
 */

#include "midend/FreeResponseResponse.hpp"

using namespace std;

namespace PlayToLearn {
namespace Midend {

////////////////////////////////////
// FreeResponseResponse constants //
////////////////////////////////////

/** public */

const string FreeResponseResponse::kFreeResponseTextAttribute("ir_free_response_text");

////////////////////////////////////////////////////////
// FreeResponseResponse member implementation details //
////////////////////////////////////////////////////////

/** public */

FreeResponseResponse::FreeResponseResponse(const Backend::AttributeMap& data) :
  InteractionResponse(data),
  text_(data.value<string>(kFreeResponseTextAttribute))
{
  // empty body
}

} // namespace Midend
} // namespace PlayToLearn
