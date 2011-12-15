/*
 * File: frontend/interactions/TextAnswer.hpp
 */

#pragma once

#include "frontend/interactions/Interaction.hpp"

namespace PlayToLearn {

/** outside class declarations */

namespace Backend {
  class Object;
}

namespace Frontend {

/** class definitions */

// The TextAnswer class represents the specific type of Interaction object
// generated when the user finishes reading a text interaction response. There
// is no actual data associated with the TextAnswer object that is but it stands
// as a separate type of interaction in order to allow for chained interactions.
class TextAnswer : public Interaction {
public:
  // The Ptr typedef allows us to refer to shared_ptr<TextAnswer> smart pointers
  // as TextAnswer::Ptr. A const version is provided as well.
  typedef boost::shared_ptr<TextAnswer> Ptr;
  typedef boost::shared_ptr<const TextAnswer> ConstPtr;

  // The TextAnswer constructor simply forwards the specified object ID to the
  // superclass, Interaction.
  explicit TextAnswer(Util::UniqueID<Backend::Object> id);

  // type returns what kind of interaction this object represents. This version
  // always returns INTERACT_TEXT_ANSWER.
  Type type() const;
};

/** TextAnswer inlined member functions, public */

inline Interaction::Type TextAnswer::type() const {
  return INTERACT_TEXT_ANSWER;
}

} // namespace Frontend
} // namespace PlayToLearn
