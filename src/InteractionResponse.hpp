/*
 * File: InteractionResponse.hpp
 */

#pragma once

#include "UniqueID.hpp"
#include "backend/AttributeMap.hpp"
#include "backend/State.hpp"
#include "backend/Object.hpp"
#include <boost/shared_ptr.hpp>
#include <string>

namespace PlayToLearn {

/////////////////////////////////////////
// InteractionResponse class interface //
/////////////////////////////////////////

/**
 * InteractionResponse contains information needed to convey response
 * information after an interaction takes place. The backend represents this
 * information in a generic AttributeMap, and the InteractionResponse subclasses
 * know how to perform the proper translations.
 */
class InteractionResponse {
public:
  /**
   * The Ptr typedef allows us to refer to shared_ptr<InteractionResponse>
   * smart pointers as InteractionResponse::Ptr. A const version is provided as
   * well.
   */
  typedef boost::shared_ptr<InteractionResponse> Ptr;
  typedef boost::shared_ptr<const InteractionResponse> ConstPtr;
  
  /**
   * The type enum describes what kind of interaction this response represents.
   */
  enum Type {
    IR_TEXT,
    IR_FREE_RESPONSE,
    IR_MULTIPLE_CHOICE,
    IR_NEW_LEVEL,
  };
  
  /**
   * TODO: comment
   */
  explicit InteractionResponse(const Backend::AttributeMap& data);
  
  /**
   * The InteractionResponse destructor is declared virtual so that the class
   * may be used polymorphically.
   */
  virtual ~InteractionResponse();
  
  /**
   * type returns the specific subclass of InteractionResponse represented by
   * this object.
   */
  virtual Type type() const = 0;
  
  /**
   * state_id returns the ID of the state the player was in when the interaction
   * occurred. This is provided primarily for debugging purposes.
   */
  Backend::State::ID state_id() const;
  
  /**
   * object_id returns the ID of the interactive object which triggered the
   * interaction. This is provided primarily for debugging purposes.
   */
  Backend::Object::ID object_id() const;
  
  /**
   * forced_interaction returns the ID of the Object which this interaction
   * response wants the game logic to interact with next. If no such interaction
   * needs to occur, it will have the value kInvalid.
   */
  Backend::Object::ID forced_interaction() const;
  
private:
  //////////////////////
  // member variables //
  //////////////////////
  
  Backend::State::ID state_id_;
  Backend::Object::ID object_id_;
  Backend::Object::ID forced_interaction_id_;
};

///////////////////////////////////////////
// InteractionResponse inlined functions //
///////////////////////////////////////////

/** public */

inline Backend::State::ID InteractionResponse::state_id() const {
  return state_id_;
}

inline Backend::Object::ID InteractionResponse::object_id() const {
  return object_id_;
}

inline Backend::Object::ID InteractionResponse::forced_interaction() const {
  return forced_interaction_id_;
}

} // namespace PlayToLearn
