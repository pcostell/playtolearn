/*
 * File: frontend/interactions/FreeResponseAnswer.hpp
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

// The FreeResponseAnswer class represents the specific type of Interaction
// object generated when the user answers a free response question. It stores
// the answer provided internally.
class FreeResponseAnswer : public Interaction {
public:
  // The Ptr typedef allows us to refer to shared_ptr<FreeResponseAnswer> smart
  // pointers as FreeResponseAnswer::Ptr. A const version is provided as well.
  typedef boost::shared_ptr<FreeResponseAnswer> Ptr;
  typedef boost::shared_ptr<const FreeResponseAnswer> ConstPtr;

  // The FreeResponseAnswer constructor stores the answer provided by the user
  // internally.
  FreeResponseAnswer(Util::UniqueID<Backend::Object> object_id, const std::string& answer);

  // type returns what kind of interaction this object represents. This version
  // always returns INTERACT_FREE_RESPONSE_ANSWER.
  Type type() const;
  
  // answer returns the free response answer given by the user which this
  // FreeResponseAnswer object stores.
  const std::string& answer() const;

private:
  // member variables
  std::string answer_;
};

/** FreeResponseAnswer inlined member functions, public */

inline Interaction::Type FreeResponseAnswer::type() const {
  return INTERACT_FREE_RESPONSE_ANSWER;
}

inline const std::string& FreeResponseAnswer::answer() const {
  return answer_;
}

} // namespace Frontend
} // namespace PlayToLearn
