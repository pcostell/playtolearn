/*
 * File: backend/external/Python.hpp
 */
 
#pragma once

#include "backend/AttributeMap.hpp"
#include <stdexcept>
#include <string>
#include <boost/python.hpp>

namespace PlayToLearn {
namespace Backend {

////////////////////////////
// Python class interface //
////////////////////////////

/**
 * The Python class handles language specific operations for all Python scripts.
 */
class Python {
public:
  /**
   * The Python constructor stores the executable Python code represented as a
   * string.
   */
  explicit Python(const std::string& code);
  
  /**
   * get_function returns the Python function with the specified name,
   * represented as a boost::python::object.
   */
  boost::python::object get_function(const std::string& function_name) const;
  
  /**
   * This overload of convert is templatized to convert a boost::python::object
   * to any primitive C++ type.
   */
  template <typename DestType>
  static void convert(const boost::python::object& source, DestType& dest);
  
  /**
   * These overloads of convert provide conversions between C++ AttributeMap
   * objects and Python dict objects.
   */
  static void convert(const AttributeMap& source, boost::python::dict& dest);
  static void convert(const boost::python::dict& source, AttributeMap& dest);
  
  /**
   * throw_error throws a PythonExecutionError with relevant information.
   */
  void throw_error() const;

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  boost::python::object main_module_;
};

///////////////////////////////////////////////////
// Python template member implementation details //
///////////////////////////////////////////////////

/** public */

template <typename DestType>
void Python::convert(const boost::python::object& source, DestType& dest) {
  dest = boost::python::extract<DestType>(source);
}

} // namespace Backend
} // namespace PlayToLearn
