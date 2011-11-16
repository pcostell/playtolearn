/*
 * File: backend/external/ExternalTransitionFn.hpp
 */

#pragma once

#include "backend/AttributeMap.hpp"
#include <string>
#include <map>

namespace PlayToLearn {
namespace Backend {

//////////////////////////////////////////
// ExternalTransitionFn class interface //
//////////////////////////////////////////

/**
 * The ExternalTransitionFn represents a class hierarchy of script objects which
 * handle state transitions.
 */
class ExternalTransitionFn {
public:
  /**
   * execute accepts the name of a function that may be executed, the map of
   * attributes describing the transition, and a global state which can be
   * modified by the script.
   */
  virtual std::string execute(const std::string& function_name,
                              const AttributeMap& interaction_map,
                              AttributeMap& global_state) const = 0;
};

} // namespace Backend
} // namespace PlayToLearn
