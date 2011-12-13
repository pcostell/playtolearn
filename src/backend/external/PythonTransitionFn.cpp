/*
 * File: backend/external/PythonTransitionFn.cpp
 */

#include <boost/python/detail/wrap_python.hpp> // must be included first

#include "backend/external/PythonTransitionFn.hpp"

#include "backend/AttributeMap.hpp"

using namespace std;
namespace python = boost::python;

namespace PlayToLearn {
namespace Backend {

/** PythonTransitionFn member functions, public */

PythonTransitionFn::PythonTransitionFn(const string& code) :
  python_(code)
{
  // empty body
}

int PythonTransitionFn::execute(const string& function_name, const AttributeMap& interaction, AttributeMap& global_state) const {
  try {
    python::dict py_interaction;
    Python::convert(interaction, py_interaction);
    
    python::dict py_global_state;
    Python::convert(global_state, py_global_state);
    
    python::object py_function = python_.get_function(function_name);
    python::object py_result = py_function(py_interaction, py_global_state);
    Python::convert(py_global_state, global_state);
    
    int result;
    Python::convert(py_result, result);
    return result;
  } catch (python::error_already_set&) {
    python_.throw_error();
  }
  
  // This point should never be reached, but we put this code here to appease
  // the compiler's warnings:
  return -1;
}

} // namespace Backend
} // namespace PlayToLearn
