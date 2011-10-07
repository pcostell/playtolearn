#pragma once

#include <map>
#include <string>

#include <Python.h>
#include <boost/python.hpp>
#include <stdexcept>

namespace EduGame {

class PythonFunction {
public:

  class PythonExecutionError : public std::runtime_error {
  public:
    explicit PythonExecutionError (const std::string& what_arg);
  };

	PythonFunction(const std::string & pythonCode);
	
	void execute(std::string functionName, std::map<std::string, std::string> & state) const;

private:

  void extractMapFromDict(std::map<std::string, std::string> & cppMap, const boost::python::dict & pythonDict) const;
  void handlePythonError() const;

	boost::python::object mainModule;
};


} /* namespace EduGame */