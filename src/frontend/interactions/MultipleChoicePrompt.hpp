/*
 * File: frontend/interactions/MultipleChoicePrompt.hpp
 */

#pragma once

#include <string>
#include <vector>

#include "frontend/interactions/InteractionPrompt.hpp"

namespace PlayToLearn {

/** outside class declarations */

namespace Backend {
  class AttributeMap;
}

namespace Frontend {

/** class definitions */

// The MultipleChoicePrompt class represents the specific type of
// InteractionPrompt object which correlates to a multiple choice question
// resulting from an interaction. It stores the text for the question and the
// available choices.
class MultipleChoicePrompt : public InteractionPrompt {
public:
  // The Ptr typedef allows us to refer to shared_ptr<MultipleChoicePrompt>
  // smart pointers as MultipleChoicePrompt::Ptr. A const version is provided as
  // well.
  typedef boost::shared_ptr<MultipleChoicePrompt> Ptr;
  typedef boost::shared_ptr<const MultipleChoicePrompt> ConstPtr;
  
  // The MultipleChoicePrompt constructor creates an MultipleChoicePrompt object
  // populated with information supplied by the specified AttributeMap.
  explicit MultipleChoicePrompt(const Backend::AttributeMap& data);
  
  // type returns what kind of interaction this prompt represents. This
  // version always returns INTERACT_MULTIPLE_CHOICE_PROMPT.
  Type type() const;
  
  // text returns the string which represents the question text for this
  // multiple choice question.
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

/** MultipleChoicePrompt inlined member functions, public */

inline InteractionPrompt::Type MultipleChoicePrompt::type() const {
  return INTERACT_MULTIPLE_CHOICE_PROMPT;
}

inline const std::string& MultipleChoicePrompt::text() const {
  return text_;
}

inline int MultipleChoicePrompt::num_choices() const {
  return static_cast<int>(choices_.size());
}

inline const std::string& MultipleChoicePrompt::choice(int index) const {
  return choices_[index];
}

} // namespace Frontend
} // namespace PlayToLearn
