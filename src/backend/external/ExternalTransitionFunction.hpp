
#pragma once

#include <string>
#include <map>


namespace PlayToLearn {
namespace Backend {

class ExternalTransitionFunction {
public:
  ExternalTransitionFunction(const std::string & code);

  virtual std::string execute(const std::string & function_name,
                              const AttributeMap & attributes,
                              AttributeMap & scriptGlobalState) const = 0;
};


} // namespace Backend
} // namespace PlayToLearn