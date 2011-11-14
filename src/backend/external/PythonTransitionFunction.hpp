/*
 * File: backend/external/PythonTransitionFunction.hpp
 */

#pragma once

#include <map>
#include <stdexcept>
#include <string>

#include <boost/python.hpp>

#include "backend/external/ExternalTransitionFunction.hpp"
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

  Python python;
};

} // namespace Backend
} // namespace PlayToLearn
