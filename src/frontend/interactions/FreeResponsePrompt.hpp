/*
 * File: frontend/interactions/FreeResponsePrompt.hpp
 */

#pragma once

#include <string>

#include "frontend/interactions/InteractionPrompt.hpp"

namespace PlayToLearn {

/** outside class declarations */

namespace Backend {
  class AttributeMap;
}

namespace Frontend {

/** class definitions */

// The FreeResponsePrompt class represents the specific type of
// InteractionPrompt object which correlates to a free response question
// resulting from an interaction. It stores the text for the question.
class FreeResponsePrompt : public InteractionPrompt {
public:
  // The Ptr typedef allows us to refer to shared_ptr<FreeResponsePrompt> smart
  // pointers as FreeResponsePrompt::Ptr. A const version is provided as well.
  typedef boost::shared_ptr<FreeResponsePrompt> Ptr;
  typedef boost::shared_ptr<const FreeResponsePrompt> ConstPtr;
  
  // The FreeResponsePrompt constructor creates an FreeResponsePrompt object
  // populated with information supplied by the specified AttributeMap.
  explicit FreeResponsePrompt(const Backend::AttributeMap& data);
  
  // type returns what kind of interaction this prompt represents. This
  // version always returns INTERACT_FREE_RESPONSE_PROMPT.
  Type type() const;
  
  // text returns the string which represents the question text for this free
  // response question.
  const std::string& text() const;

private:
  // member variables
  std::string text_;
};

/** FreeResponsePrompt inlined member functions, public */

inline InteractionPrompt::Type FreeResponsePrompt::type() const {
  return INTERACT_FREE_RESPONSE_PROMPT;
}

inline const std::string& FreeResponsePrompt::text() const {
  return text_;
}

} // namespace Frontend
} // namespace PlayToLearn
