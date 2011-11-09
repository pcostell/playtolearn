/*
 * File: frontend/FreeResponseAnswerInteraction.hpp
 */

#pragma once

#include "frontend/Interaction.hpp"

namespace PlayToLearn {
namespace Frontend {

///////////////////////////////////////////////////
// FreeResponseAnswerInteraction class interface //
///////////////////////////////////////////////////

/**
 * The FreeResponseAnswerInteraction class represents the specific type of
 * Interaction object generated when the user answers a free response question.
 * It stores the answer provided internally.
 */
class FreeResponseAnswerInteraction : public Interaction {
public:
  /**
   * The Ptr typedef allows us to refer to
   * shared_ptr<FreeResponseAnswerInteraction> smart pointers as
   * FreeResponseAnswerInteraction::Ptr. A const version is provided as well.
   */
  typedef boost::shared_ptr<FreeResponseAnswerInteraction> Ptr;
  typedef boost::shared_ptr<const FreeResponseAnswerInteraction> ConstPtr;

  /**
   * The FreeResponseAnswerInteraction constructor forwards the specified
   * object_id to the superclass, Interaction. It also stores the answer
   * provided by the user internally.
   */
  explicit FreeResponseAnswerInteraction(Backend::Object::ID object_id, const std::string& answer);

  /**
   * type returns what kind of interaction this object represents. This version
   * always returns INTERACT_FREE_RESPONSE_ANSWER.
   */
  Type type() const;
  
  /**
   * This version of requesting_data returns false, since a
   * FreeResponseAnswerInteraction is created in response to a free response
   * interaction and is expecting a state transition in return.
   */
  bool requesting_data() const;
  
  /**
   * answer returns the free response answer given by the user which this
   * FreeResponseAnswerInteraction object stores.
   */
  const std::string& answer() const;

private:
  //////////////////////
  // member variables //
  //////////////////////

  std::string answer_;
};


/////////////////////////////////////////////////////
// FreeResponseAnswerINteraction inlined functions //
/////////////////////////////////////////////////////

/** public */

inline Interaction::Type FreeResponseAnswerInteraction::type() const {
  return INTERACT_FREE_RESPONSE_ANSWER;
}

inline bool FreeResponseAnswerInteraction::requesting_data() const {
  return false;
}

inline const std::string& FreeResponseAnswerInteraction::answer() const {
  return answer_;
}

} // namespace Frontend
} // namespace PlayToLearn
