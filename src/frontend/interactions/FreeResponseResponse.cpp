/*
 * File: frontend/interactions/FreeResponseResponse.cpp
 */

#include "frontend/interactions/FreeResponseResponse.hpp"

#include "util/Constants.hpp"
#include "backend/AttributeMap.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** FreeResponseResponse member functions, public */

FreeResponseResponse::FreeResponseResponse(const Backend::AttributeMap& data) :
  InteractionResponse(data),
  text_(data.value<string>(Util::kTextAttribute))
{
  // empty body
}

} // namespace Frontend
} // namespace PlayToLearn
