/*
 * File: TransitionFn.hpp
 */

#pragma once

#include "../UniqueID.hpp"
#include "AttributeMap.hpp"

namespace PlayToLearn {
namespace Backend {

////////////////////////
// class declarations //
////////////////////////

class State;

//////////////////////////////////
// TransitionFn class interface //
//////////////////////////////////

/**
 * The TransitionFn class represents a transition function which describes how
 * to go from one state to another given some interaction.
 */
class TransitionFn {
public:
  /**
   * The TransitionFn::ID type represents a uniquely identifier for a particular
   * transition function.
   */
  typedef UniqueID<TransitionFn> ID;
  
  /**
   * The TransitionFn constructor initializes a TransitionFn object with a
   * unique identifier. If no such identifier is specified, the ID chosen will
   * simply be the next available one.
   */
  explicit TransitionFn(const AttributeMap& response, ID id = ID::create());
  
  /**
   * id returns the unique ID of this particular transition function object.
   */
  ID id() const;
  
  /**
   * next_state returns the ID of the next state based on the given interaction
   * elements and environmental status. interaction is an map of attributes
   * containing all of the data which describes the transition action.
   */
  UniqueID<State> next_state(const AttributeMap& interaction) const;
  
  /**
   * response returns the response map associated with this transition by
   * reference-to-const. It is used to describe the action that should follow
   * this state transition.
   */
  const AttributeMap& response() const;
  
private:
  //////////////////////
  // member variables //
  //////////////////////
  
  ID id_;
  
  AttributeMap response_;
};

////////////////////////////////////
// TransitionFn inlined functions //
////////////////////////////////////

/** public */

inline TransitionFn::ID TransitionFn::id() const {
  return id_;
}

inline const AttributeMap& TransitionFn::response() const {
  return response_;
}

} // namespace Backend
} // namespace PlayToLearn
