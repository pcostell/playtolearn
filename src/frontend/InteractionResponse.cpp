/*
 * File: frontend/InteractionResponse.hpp
 */

#include "util/Constants.hpp"
#include "frontend/InteractionResponse.hpp"
#include "frontend/TextResponse.hpp"
#include "frontend/FreeResponseResponse.hpp"
#include "frontend/MultipleChoiceResponse.hpp"
#include <stdexcept>
#include <sstream>
#include <boost/make_shared.hpp>

using namespace std;

namespace PlayToLearn {
namespace Frontend {

///////////////////////////////////////////////////////
// InteractionResponse member implementation details //
///////////////////////////////////////////////////////

/** public */

InteractionResponse::InteractionResponse(const Backend::AttributeMap& data) :
  state_id_(data.value<int>(Util::kStateIDAttribute)),
  object_id_(data.value<int>(Util::kObjectIDAttribute))
{
  // empty body
}

InteractionResponse::~InteractionResponse() {
  // empty body
}

//////////////////////////////////////////////////////
// InteractionResponse class implementation details //
//////////////////////////////////////////////////////

/** public */

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
