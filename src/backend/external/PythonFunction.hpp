/*
 * File: backend/external/PythonTransitionFunction.hpp
 */

#pragma once

#include <map>
#include <stdexcept>
#include <string>

#include <boost/python.hpp>

#include "backend/external/Python.hpp"

namespace PlayToLearn {
namespace Backend {

class PythonTransitionFunction : public ExternalTransitionFunction {
public:
  PythonTransitionFunction(const std::string & code);

  std::string execute(const std::string & function_name,
                      const AttributeMap & attributes,
                      AttributeMap & scriptGlobalState) const;
private:
  void throwError() const;

  boost::python::object mainModule;
};


PythonTransitionFunction::PythonTransitionFunction(const std::string& code) {

}


std::string PythonTransitionFunction::execute(const std::string & function_name, const AttributeMap & attributes, AttributeMap & scriptGlobalState) const{
  try {
    PythonMapConverter::script_type pyAttributes;
    PythonMapConverter.convert(attributes, pyAttributes);
    PythonMapConverter::script_type pyGlobalState;
    PythonMapConverter.convert(scriptGlobalState, pyGlobalState);
    boost::python::object processFunction = mainModule.attr(str(function_name));

    PythonStringConverter::script_type pyResult = processFunction(pyAttributes, pyGlobalState);
    string result;
    PythonStringConverter::convert(pyResult, result);
    return result;
  } catch (const error_already_set &) {
    throwError();
  }
  return string();
}

} // namespace Backend
} // namespace PlayToLearn
