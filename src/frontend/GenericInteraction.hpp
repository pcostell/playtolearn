/*
 * File: frontend/GenericInteraction.hpp
 */

#pragma once

#include "frontend/Interaction.hpp"

namespace PlayToLearn {
namespace Frontend {

////////////////////////////////////////
// GenericInteraction class interface //
////////////////////////////////////////

/**
 * The GenericInteraction class represents a specific type of Interaction for
 * generic interactions with no special attributes. As a result, it holds no
 * additional data members of its own.
 */
class GenericInteraction : public Interaction {
public:
  /**
   * The Ptr typedef allows us to refer to shared_ptr<GenericInteraction> smart
   * pointers as GenericInteraction::Ptr. A const version is provided as well.
   */
  typedef boost::shared_ptr<GenericInteraction> Ptr;
  typedef boost::shared_ptr<const GenericInteraction> ConstPtr;
  
  /**
   * The GenericInteraction constructor simply forwards the specified object_id
   * to the superclass, Interaction.
   */
  explicit GenericInteraction(Backend::Object::ID object_id);
  
  /**
   * type returns what kind of interaction this object represents. This version
   * always returns INTERACT_GENERIC.
   */
  Type type() const;
};

//////////////////////////////////////////
// GenericInteraction inlined functions //
//////////////////////////////////////////

/** public */

Interaction::Type GenericInteraction::type() const {
  return INTERACT_GENERIC;
}

} // namespace Frontend
} // namespace PlayToLearn
