#pragma once

#include <map>
#include <string>

#include <Python.h>
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
   */
	void execute(std::string functionName, 
               std::map<std::string, std::string> & state) const;

private:

  void extractMapFromDict(std::map<std::string, std::string> & cppMap, 
                          const boost::python::dict & pythonDict) const;
  void handlePythonError() const;

	boost::python::object mainModule;
};


} /* namespace EduGame */