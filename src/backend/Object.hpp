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
  
  /**
   * The kObjectIDAttribute constant represents the name of the attribute that
   * should be paired with the corresponding object ID involved in an
   * interaction.
   */
  static const std::string kObjectIDAttribute;
  
  /**
   * The kForcedInteractionIDAttribute constant represents the name of the
   * attribute that should be paired with the corresponding object ID with which
   * an interaction should occur.
   */
  static const std::string kForcedInteractionIDAttribute;
};

} // namespace Backend
} // namespace PlayToLearn
