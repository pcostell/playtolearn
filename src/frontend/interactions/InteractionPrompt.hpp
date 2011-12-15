/*
 * File: frontend/interactions/InteractionPrompt.hpp
 */

#pragma once

#include <boost/shared_ptr.hpp>

#include "util/UniqueID.hpp"

namespace PlayToLearn {

/** outside class declarations */

namespace Backend {
  class AttributeMap;
  class State;
  class Object;
}

namespace Frontend {

/** class definitions */

// InteractionPrompt contains information needed to convey response information
// after an interaction takes place. The backend represents this information in
// a generic AttributeMap, and the InteractionPrompt subclasses know how to
// perform the proper translations.
class InteractionPrompt {
public:
  // The Ptr typedef allows us to refer to shared_ptr<InteractionPrompt> smart
  // pointers as InteractionPrompt::Ptr. A const version is provided as well.
  typedef boost::shared_ptr<InteractionPrompt> Ptr;
  typedef boost::shared_ptr<const InteractionPrompt> ConstPtr;

  // The Type enum describes what kind of interaction this prompt represents.
  enum Type {
    INTERACT_TEXT_PROMPT,
    INTERACT_FREE_RESPONSE_PROMPT,
    INTERACT_MULTIPLE_CHOICE_PROMPT,
    //IR_NEW_LEVEL,
  };

  // The InteractionPrompt constructor creates an InteractionPrompt object
  // populated with information supplied by the specified AttributeMap.
  explicit InteractionPrompt(const Backend::AttributeMap& data);

  // The InteractionPrompt destructor is declared virtual so that the class may
  // be used polymorphically.
  virtual ~InteractionPrompt();

  // type returns the specific subclass of InteractionPrompt represented by this
  // object.
  virtual Type type() const = 0;

  // state_id returns the ID of the state the player was in when the interaction
  // occurred. This is provided primarily for debugging purposes.
  Util::UniqueID<Backend::State> state_id() const;

  // object_id returns the ID of the interactive object which triggered the
  // interaction. This is provided primarily for debugging purposes.
  Util::UniqueID<Backend::Object> object_id() const;
  
  // create is a factory function for the InteractionPrompt class. It accepts a
  // single AttributeMap as its argument and, depending on the
  // interaction_prompt_type attribute, creates and returns the proper
  // InteractionPrompt object.
  static Ptr create(const Backend::AttributeMap& data);

private:
  // member variables
  Util::UniqueID<Backend::State> state_id_;
  Util::UniqueID<Backend::Object> object_id_;
};

/** InteractionPrompt inlined member functions, public */

inline Util::UniqueID<Backend::State> InteractionPrompt::state_id() const {
  return state_id_;
}

inline Util::UniqueID<Backend::Object> InteractionPrompt::object_id() const {
  return object_id_;
}

} // namespace Frontend
} // namespace PlayToLearn
