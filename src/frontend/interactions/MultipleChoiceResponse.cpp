/*
 * File: frontend/interactions/MultipleChoiceResponse.cpp
 */

#include "frontend/interactions/MultipleChoiceResponse.hpp"

#include <boost/lexical_cast.hpp>

#include "util/Constants.hpp"
#include "backend/AttributeMap.hpp"

using namespace std;

namespace PlayToLearn {
namespace Frontend {

/** MultipleChoiceResponse member functions, public */

MultipleChoiceResponse::MultipleChoiceResponse(const Backend::AttributeMap& data) :
  InteractionResponse(data),
  text_(data.value<string>(Util::kTextAttribute)),
  choices_(data.value<int>(Util::kNumMCChoicesAttribute))
{
  for (size_t i = 0; i < choices_.size(); ++i)
    choices_[i] = data.value<int>(Util::kMCChoiceAttribute + boost::lexical_cast<string>(i));
}

} // namespace Frontend
} // namespace PlayToLearn
