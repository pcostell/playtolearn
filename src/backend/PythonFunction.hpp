/*
 * File: backend/PythonFunction.hpp
 */

#pragma once

#include "backend/AttributeMap.hpp"
#include <stdexcept>
#include <string>
#include <map>
#include <boost/python.hpp>

namespace PlayToLearn {
namespace Backend {

////////////////////////////////////
// PythonFunction class interface //
////////////////////////////////////

/**
 * Allows for the execution of a python function from c++. Passes a map
 * from string->string for passing data between the two languages.
 **/
class PythonFunction {
public:
  /**
   * Constructor
   * Args:
   * python_code: the python code to execute.
   * TODO: more descriptive comment
   */
  explicit PythonFunction(const std::string& python_code);

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

//////////////////////////////////////////
// PythonExecutionError class interface //
//////////////////////////////////////////

/**
 * The PythonExecutionError class represents the type of exception thrown when
 * an error occurs in the execution of a Python script.
 */
class PythonExecutionError : public std::runtime_error {
public:
  /**
   * The PythonExecutionError contructor creates the error object with the
   * specified description string.
   */
  explicit PythonExecutionError(const std::string& what_arg);
};

} // namespace Backend
} // namespace PlayToLearn
