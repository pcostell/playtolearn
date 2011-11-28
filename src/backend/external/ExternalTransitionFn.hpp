/*
 * File: backend/external/ExternalTransitionFn.hpp
 */

#pragma once

#include "backend/AttributeMap.hpp"
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

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
   * The Ptr typedef allows us to refer to shared_ptr<ExternalTransitionFn>
   * smart pointers as ExternalTransitionFn::Ptr. A const version is provided as 
   * well.
   */
  typedef boost::shared_ptr<ExternalTransitionFn> Ptr;
  typedef boost::shared_ptr<const ExternalTransitionFn> ConstPtr;
  
  /**
   * execute accepts the name of a function that may be executed, the map of
   * attributes describing the transition, and a global state which can be
   * modified by the script. It returns the index of the player's new state.
   */
  virtual int execute(const std::string& function_name,
                      const AttributeMap& interaction,
                      AttributeMap& global_state) const = 0;
};

} // namespace Backend
} // namespace PlayToLearn
