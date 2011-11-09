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
 * TODO: comment
 */
class Object {
public:
  /**
   * The Object::ID type represents a uniquely identifier for a particular
   * interactive object.
   */
  typedef Util::UniqueID<Object> ID;
};

} // namespace Backend
} // namespace PlayToLearn
