/*
 * File: backend/external/PythonTransitionFn.hpp
 */

#pragma once

#include "backend/external/ExternalTransitionFn.hpp"
#include "backend/external/Python.hpp"
#include <stdexcept>
#include <string>
#include <map>
#include <boost/python.hpp>

namespace PlayToLearn {
namespace Backend {

////////////////////////////////////////
// PythonTransitionFn class interface //
////////////////////////////////////////

/**
 * The PythonTransitionFn class represents an executable Python script which
 * describes state transitions.
 */
class PythonTransitionFn : public ExternalTransitionFn {
public:
  /**
   * The PythonTransitionFn accepts the Python code which should be executed.
   */
  explicit PythonTransitionFn(const std::string & code);
  
  /**
   * See the corresponding comment in ExternalTransitionFn.hpp.
   */
  std::string execute(const std::string& function_name,
                      const AttributeMap& interaction_map,
                      AttributeMap& global_state) const;
private:
  //////////////////////
  // member variables //
  //////////////////////
  
  Python python_;
};

} // namespace Backend
} // namespace PlayToLearn
