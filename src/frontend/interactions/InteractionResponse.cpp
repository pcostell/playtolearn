/*
 * File: frontend/interactions/InteractionResponse.cpp
 */

#include "frontend/interactions/InteractionResponse.hpp"

#include <stdexcept>
#include <sstream>

#include <boost/make_shared.hpp>

#include "util/Constants.hpp"
#include "frontend/interactions/TextResponse.hpp"
#include "frontend/interactions/FreeResponseResponse.hpp"
#include "frontend/interactions/MultipleChoiceResponse.hpp"
#include "backend/AttributeMap.hpp"
#include "backend/State.hpp"
#include "backend/Object.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** InteractionResponse member functions, public */

InteractionResponse::InteractionResponse(const Backend::AttributeMap& data) :
  state_id_(data.value<int>(Util::kStateIDAttribute)),
  object_id_(data.value<int>(Util::kObjectIDAttribute))
{
  // empty body
}

InteractionResponse::~InteractionResponse() {
  // empty body
}

/** InteractionResponse class functions, public */

InteractionResponse::Ptr InteractionResponse::create(const Backend::AttributeMap& data) {
  // Extract the response type as a string and check to see if it's a valid
  // value:
  string response_type = data.value<string>(Util::kInteractionResponseTypeAttribute);
  if (response_type == Util::kTextResponseTypeValue) {
    return boost::make_shared<TextResponse>(data);
  } else if (response_type == Util::kFreeResponseResponseTypeValue) {
    return boost::make_shared<FreeResponseResponse>(data);
  } else if (response_type == Util::kMultipleChoiceResponseTypeValue) {
    return boost::make_shared<MultipleChoiceResponse>(data);
  } else {
    stringstream err_ss;
    err_ss << "Invalid value for interaction response type attribute: " << response_type;
    throw runtime_error(err_ss.str());
  }
}

} // namespace Frontend
} // namespace PlayToLearn
