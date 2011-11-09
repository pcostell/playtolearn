/*
 * File: frontend/MultipleChoiceResponse.cpp
 */

#include "util/Constants.hpp"
#include "frontend/MultipleChoiceResponse.hpp"
#include <boost/lexical_cast.hpp>

using namespace std;

namespace PlayToLearn {
namespace Frontend {

//////////////////////////////////////////////////////////
// MultipleChoiceResponse member implementation details //
//////////////////////////////////////////////////////////

/** public */

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
