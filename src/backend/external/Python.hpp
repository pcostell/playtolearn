
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
  boost::python::object get_function(const std::string & function_name) const;

  template<typename SourceType, typename DestType>
  static void convert(const SourceType & source, DestType & dest);

  template<typename DestType>
  static void convert(const boost::python::object & source, DestType & dest);

  void throwError() const;
private:
  boost::python::object mainModule;
};

template<typename DestType>
void Python::convert(const boost::python::object & source, DestType & dest) {
  dest = boost::python::extract<DestType>(source);
}

} // namespace Backend
} // namespace PlayToLearn