/*
 * File: frontend/interactions/InteractionResponse.hpp
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

// InteractionResponse contains information needed to convey response
// information after an interaction takes place. The backend represents this
// information in a generic AttributeMap, and the InteractionResponse subclasses
// know how to perform the proper translations.
class InteractionResponse {
public:
  // The Ptr typedef allows us to refer to shared_ptr<InteractionResponse>
  // smart pointers as InteractionResponse::Ptr. A const version is provided as
  // well.
  typedef boost::shared_ptr<InteractionResponse> Ptr;
  typedef boost::shared_ptr<const InteractionResponse> ConstPtr;

  // The Type enum describes what kind of interaction this response represents.
  enum Type {
    IR_TEXT,
    IR_FREE_RESPONSE,
    IR_MULTIPLE_CHOICE,
    //IR_NEW_LEVEL,
  };

  // The InteractionResponse constructor creates an InteractionResponse object
  // populated with information supplied by the specified AttributeMap.
  explicit InteractionResponse(const Backend::AttributeMap& data);

  // The InteractionResponse destructor is declared virtual so that the class
  // may be used polymorphically.
  virtual ~InteractionResponse();

  // type returns the specific subclass of InteractionResponse represented by
  // this object.
  virtual Type type() const = 0;

  // state_id returns the ID of the state the player was in when the interaction
  // occurred. This is provided primarily for debugging purposes.
  Util::UniqueID<Backend::State> state_id() const;

  // object_id returns the ID of the interactive object which triggered the
  // interaction. This is provided primarily for debugging purposes.
  Util::UniqueID<Backend::Object> object_id() const;
  
  // create is a factory function for the InteractionResponse class. It accepts
  // a single AttributeMap as its argument and, depending on the
  // interaction_response_type attribute, creates and returns the proper
  // InteractionResponse object.
  static Ptr create(const Backend::AttributeMap& data);

private:
  // member variables
  Util::UniqueID<Backend::State> state_id_;
  Util::UniqueID<Backend::Object> object_id_;
};

/** InteractionResponse inlined member functions, public */

inline Util::UniqueID<Backend::State> InteractionResponse::state_id() const {
  return state_id_;
}

inline Util::UniqueID<Backend::Object> InteractionResponse::object_id() const {
  return object_id_;
}

} // namespace Frontend
} // namespace PlayToLearn
