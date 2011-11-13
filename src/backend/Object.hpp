/*
 * File: backend/Object.hpp
 */

#pragma once

#include "util/UniqueID.hpp"
#include <string>

namespace PlayToLearn {
namespace Backend {

////////////////////////////
// Object class interface //
////////////////////////////

/**
 * The Object class represents an object in the game world with which the player
 * can engage in an interaction.
 */
class Object {
public:
  /**
   * The Object::ID type represents a uniquely identifier for a particular
   * interactive object.
   */
  typedef Util::UniqueID<Object> ID;
  
  /**
   * The Object constructor initializes an interactive object the specified
   * unique identifier.
   */
  explicit Object(ID id);
  
  /**
   * id returns the unique ID of this particular interactive object.
   */
  ID id() const;

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  ID id_;
};

//////////////////////////////
// Object inlined functions //
//////////////////////////////

/** public */

inline Object::ID Object::id() const {
  return id_;
}

} // namespace Backend
} // namespace PlayToLearn
