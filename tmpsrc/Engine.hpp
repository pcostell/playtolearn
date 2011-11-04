/*
 * File: Engine.hpp
 */

#pragma once

#include "StateMachine.hpp"

namespace PlayToLearn {
namespace Backend {

////////////////////////////
// Engine class interface //
////////////////////////////

/**
 * The Engine class drives the entire backend portion of the program.
 */
class Engine {
public:
  /**
   * TODO: comment
   */
  const AttributeMap& register_interaction(Interaction::ID const AttributeMap& interaction);
  
private:
  //////////////////////
  // member variables //
  //////////////////////
  
  StateMachine state_machine;
};

} // namespace Backend
} // namespace PlayToLearn
