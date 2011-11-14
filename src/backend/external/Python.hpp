
#pragma once

#include <string>
#include <stdexcept>

#include <boost/python.hpp>

#include "backend/AttributeMap.hpp"

namespace PlayToLearn {
namespace Backend {

class Python {
public:
  Python(const std::string& code);
  boost::python::object get_function(const std::string & function_name);

  template<typename SourceType, typename DestType>
  static ReturnType convert(const ArgType & source, DestType & dest);
private:
  boost::python::object mainModule;
};

template<typename DestType>
void convert(const boost::python::object & source, DestType & dest) {
  dest = extract<DestType>(source);
}

} // namespace Backend
} // namespace PlayToLearn