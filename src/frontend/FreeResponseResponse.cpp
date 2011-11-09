/*
 * File: frontend/FreeResponseResponse.cpp
 */

#include "frontend/FreeResponseResponse.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

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

} // namespace Frontend
} // namespace PlayToLearn
