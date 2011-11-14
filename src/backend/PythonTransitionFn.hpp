/*
 * File: backend/PythonTransitionFn.hpp
 */

#pragma once

#include "backend/AttributeMap.hpp"
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
 * The PythonTransitionFn class represents an executable Python script used by
 * the state machine's transition operations to move game progress to a new
 * state.
 */
class PythonTransitionFn {
public:
  /**
   * Constructor
   * Args:
   * python_code: the python code to execute.
   * TODO: more descriptive comment
   */
  explicit PythonTransitionFn(const std::string& python_code);

  /**
   * Execute the python function.
   * Args:
   * function_name: The name of the python function to call.
   * attribute_map: The map to pass to the python function as a python dict.
   * Returns the return value of the python function.
   */
  std::string execute(const std::string& function_name, const AttributeMap& attribute_map) const;

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  boost::python::object main_module_;
  
  //////////////////////
  // member functions //
  //////////////////////
  
  void handle_python_error() const;
};

} // namespace Backend
} // namespace PlayToLearn
