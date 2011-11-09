/*
 * File: backend/PythonFunction.hpp
 */

#pragma once

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
   * TODO: comment
   */
  class PythonExecutionError : public std::runtime_error {
  public:
    explicit PythonExecutionError(const std::string& what_arg);
  };

  /**
   * Constructor
   * Args:
   * python_code: the python code to execute.
   * TODO: more descriptive comment
   */
	PythonFunction(const std::string& python_code);

  /**
   * Execute the python function.
   * Args:
   * function_name: The name of the python function to call.
   * state: The map to pass to the python function as a python dict.
   * Returns the return value of the python function.
   */
	std::string execute(const std::string& function_name, const std::map<std::string, std::string>& state) const;

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  boost::python::object mainModule;
  
  //////////////////////
  // member functions //
  //////////////////////
  
  void handlePythonError() const;
};

} // namespace Backend
} // namespace PlayToLearn
