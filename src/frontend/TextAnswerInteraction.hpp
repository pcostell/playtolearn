/*
 * File: frontend/TextAnswerInteraction.hpp
 */

#pragma once

#include "frontend/Interaction.hpp"

namespace PlayToLearn {
namespace Frontend {

///////////////////////////////////////////
// TextAnswerInteraction class interface //
///////////////////////////////////////////

/**
 * The TextAnswerInteraction class represents the specific type of Interaction
 * object generated when the user finishes reading a text interaction response.
 * There is no actual data associated with the TextAnswerInteraction object that
 * is created, but it stands as a separate type of interaction in order to allow
 * for chained interactions.
 */
class TextAnswerInteraction : public Interaction {
public:
  /**
   * The Ptr typedef allows us to refer to shared_ptr<TextAnswerInteraction>
   * smart pointers as TextAnswerInteraction::Ptr. A const version is provided
   * as well.
   */
  typedef boost::shared_ptr<TextAnswerInteraction> Ptr;
  typedef boost::shared_ptr<const TextAnswerInteraction> ConstPtr;
  
  /**
   * The TextAnswerInteraction constructor simply forwards the specified
   * object_id to the superclass, Interaction.
   */
  explicit TextAnswerInteraction(Backend::Object::ID object_id);
  
  /**
   * type returns what kind of interaction this object represents. This version
   * always returns INTERACT_TEXT_ANSWER.
   */
  Type type() const;
};

/////////////////////////////////////////////
// TextAnswerInteraction inlined functions //
/////////////////////////////////////////////

/** public */

Interaction::Type TextAnswerInteraction::type() const {
  return INTERACT_TEXT_ANSWER;
}

} // namespace Frontend
} // namespace PlayToLearn
