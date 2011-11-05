/*
 * File: Object.hpp
 */

#pragma once

namespace PlayToLearn {
namespace Backend {

////////////////////////////
// Object class interface //
////////////////////////////

/**
 * TODO: comment
 */
class Object {
public:
  /**
   * The Object::ID type represents a uniquely identifier for a particular
   * interactive object.
   */
  typedef UniqueID<Object> ID;
};

} // namespace Backend
} // namespace PlayToLearn
