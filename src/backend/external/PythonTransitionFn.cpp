/*
 * File: backend/external/PythonTransitionFn.cpp
 */

#include <boost/python/detail/wrap_python.hpp> // must be included first
#include "backend/external/PythonTransitionFn.hpp"

using namespace std;
using boost::python::object;

namespace PlayToLearn {
namespace Backend {

//////////////////////////////////////////////////////
// PythonTransitionFn member implementation details //
//////////////////////////////////////////////////////

/** public */

PythonTransitionFn::PythonTransitionFn(const string& code) :
  python_(code)
{
  // empty body
}

int PythonTransitionFn::execute(const string& function_name, const AttributeMap& interaction, AttributeMap& global_state) const {
  try {
    boost::python::dict py_interaction;
    Python::convert(interaction, py_interaction);
    
    boost::python::dict py_global_state;
    Python::convert(global_state, py_global_state);
    
    object py_function = python_.get_function(function_name);
    object py_result = py_function(py_interaction, py_global_state);
    Python::convert(py_global_state, global_state);
    
    int result;
    Python::convert(py_result, result);
    return result;
  } catch (boost::python::error_already_set&) {
    python_.throw_error();
  }
  
  // This point should never be reached, but we put this code here to appease
  // the compiler's warnings:
  return -1;
}

} // namespace Backend
} // namespace PlayToLearn
