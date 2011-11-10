/*
 * File: frontend/interactions/FreeResponseResponse.cpp
 */

#include "util/Constants.hpp"
#include "frontend/interactions/FreeResponseResponse.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

////////////////////////////////////////////////////////
// FreeResponseResponse member implementation details //
////////////////////////////////////////////////////////

/** public */

FreeResponseResponse::FreeResponseResponse(const Backend::AttributeMap& data) :
  InteractionResponse(data),
  text_(data.value<string>(Util::kTextAttribute))
{
  // empty body
}

} // namespace Frontend
} // namespace PlayToLearn
