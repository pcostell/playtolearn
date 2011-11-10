/*
 * File: frontend/interactions/MultipleChoiceAnswerInteraction.hpp
 */

#pragma once

#include "frontend/interactions/Interaction.hpp"

namespace PlayToLearn {
namespace Frontend {

/////////////////////////////////////////////////////
// MultipleChoiceAnswerInteraction class interface //
/////////////////////////////////////////////////////

/**
 * The MultipleChoiceAnswerInteraction class represents the specific type of
 * Interaction object generated when the user answers a multiple choice
 * question. It stores the answer selected internally.
 */
class MultipleChoiceAnswerInteraction : public Interaction {
public:
  /**
   * The Ptr typedef allows us to refer to
   * shared_ptr<MultipleChoiceAnswerInteraction> smart pointers as
   * MultipleChoiceAnswerInteraction::Ptr. A const version is provided as well.
   */
  typedef boost::shared_ptr<MultipleChoiceAnswerInteraction> Ptr;
  typedef boost::shared_ptr<const MultipleChoiceAnswerInteraction> ConstPtr;

  /**
   * The MultipleChoiceAnswerInteraction constructor forwards the specified
   * object_id to the superclass, Interaction. It also stores the answer
   * provided by the user internally, represented as an index in the range
   * [0, number of answers).
   */
  explicit MultipleChoiceAnswerInteraction(Backend::Object::ID object_id, int answer_index);

  /**
   * type returns what kind of interaction this object represents. This version
   * always returns INTERACT_MULTIPLE_CHOICE_ANSWER.
   */
  Type type() const;
  
  /**
   * This version of requesting_data returns false, since a
   * MultipleChoiceAnswerInteraction is created in response to a multiple choice
   * interaction and is expecting a state transition in return.
   */
  bool requesting_data() const;
  
  /**
   * answer_index returns the multiple choice answer given by the user which
   * this MultipleChoiceAnswerInteraction object stores. The integer returned
   * represents an index in the range [0, number of answers).
   */
  int answer_index() const;

private:
  //////////////////////
  // member variables //
  //////////////////////

  int answer_index_;
};

///////////////////////////////////////////////////////
// MultipleChoiceAnswerInteraction inlined functions //
///////////////////////////////////////////////////////

/** public */

inline Interaction::Type MultipleChoiceAnswerInteraction::type() const {
  return INTERACT_MULTIPLE_CHOICE_ANSWER;
}

inline bool MultipleChoiceAnswerInteraction::requesting_data() const {
  return false;
}

inline int MultipleChoiceAnswerInteraction::answer_index() const {
  return answer_index_;
}

} // namespace Frontend
} // namespace PlayToLearn
