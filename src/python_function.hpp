#pragma once

#include <map>
#include <string>

#include <boost/python.hpp>
#include <stdexcept>

namespace EduGame {

/**
 * Allows for the execution of a python function from c++. Passes a map
 * from string->string for passing data between the two languages.
 **/
class PythonFunction {
public:

  class PythonExecutionError : public std::runtime_error {
  public:
    explicit PythonExecutionError (const std::string& what_arg);
  };

  /**
   * Constructor
   * Args:
   * pythonCode: the python code to execute.
   */
	PythonFunction(const std::string & pythonCode);

  /**
   * Execute the python function.
   * Args:
   * functionName: The name of the python function to call.
   * state: The map to pass to the python function as a python dict.
   * Returns the return value of the python function.
   */
	int execute(const std::string & functionName,
               const std::map<std::string, std::string> & state) const;

private:

  void handlePythonError() const;

	boost::python::object mainModule;
};


} /* namespace EduGame */
