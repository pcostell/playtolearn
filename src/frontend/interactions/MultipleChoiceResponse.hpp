/*
 * File: frontend/interactions/MultipleChoiceResponse.hpp
 */

#pragma once

#include <string>
#include <vector>

#include "frontend/interactions/InteractionResponse.hpp"

namespace PlayToLearn {

/** outside class declarations */

namespace Backend {
  class AttributeMap;
}

namespace Frontend {

/** class definitions */

// The MultipleChoiceResponse class represents the specific type of
// InteractionResponse object which correlates to a multiple choice question
// resulting from an interaction. It stores the text for the question and the
// available choices.
class MultipleChoiceResponse : public InteractionResponse {
public:
  // The Ptr typedef allows us to refer to shared_ptr<MultipleChoiceResponse>
  // smart pointers as MultipleChoiceResponse::Ptr. A const version is provided
  // as well.
  typedef boost::shared_ptr<MultipleChoiceResponse> Ptr;
  typedef boost::shared_ptr<const MultipleChoiceResponse> ConstPtr;
  
  // The MultipleChoiceResponse constructor creates an MultipleChoiceResponse
  // object populated with information supplied by the specified AttributeMap.
  explicit MultipleChoiceResponse(const Backend::AttributeMap& data);
  
  // type returns what kind of interaction this response represents. This
  // version always returns IR_MULTIPLE_CHOICE.
  Type type() const;
  
  // text returns the string which represents the question text for this free
  // response question.
  const std::string& text() const;
  
  // num_choices returns the number of available choices for this multiple
  // choice question.
  int num_choices() const;
  
  // choice returns the string text describing the choice at the given index.
  // The code will not check that the index is in bounds; instead, use
  // num_choices for proper bounds checking.
  const std::string& choice(int index) const;

private:
  // member variables
  std::string text_;
  std::vector<std::string> choices_;
};

/** MultipleChoiceResponse inlined member functions, public */

inline InteractionResponse::Type MultipleChoiceResponse::type() const {
  return IR_MULTIPLE_CHOICE;
}

inline const std::string& MultipleChoiceResponse::text() const {
  return text_;
}

inline int MultipleChoiceResponse::num_choices() const {
  return static_cast<int>(choices_.size());
}

inline const std::string& MultipleChoiceResponse::choice(int index) const {
  return choices_[index];
}

} // namespace Frontend
} // namespace PlayToLearn
