/*
 * File: frontend/interactions/TextPrompt.hpp
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

// The TextPrompt class represents a specific type of InteractionPrompt where
// the interaction data is simply text to be printed for the user to read.
class TextPrompt : public InteractionPrompt {
public:
  // The Ptr typedef allows us to refer to shared_ptr<TextPrompt> smart pointers
  // as TextPrompt::Ptr. A const version is provided as well.
  typedef boost::shared_ptr<TextPrompt> Ptr;
  typedef boost::shared_ptr<const TextPrompt> ConstPtr;
  
  // The TextPrompt constructor creates an TextPrompt object populated with
  // information supplied by the specified AttributeMap.
  explicit TextPrompt(const Backend::AttributeMap& data);
  
  // type returns what kind of interaction this prompt represents. This
  // version always returns INTERACT_TEXT_PROMPT.
  Type type() const;
  
  // text returns the string which represents the text that should be printed
  // for this particular prompt.
  const std::string& text() const;

private:
  // member variables
  std::string text_;
};

/** TextPrompt inlined member functions, public */

inline InteractionPrompt::Type TextPrompt::type() const {
  return INTERACT_TEXT_PROMPT;
}

inline const std::string& TextPrompt::text() const {
  return text_;
}

} // namespace Frontend
} // namespace PlayToLearn
