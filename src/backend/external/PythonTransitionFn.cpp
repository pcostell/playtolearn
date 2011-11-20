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

string PythonTransitionFn::execute(const string& function_name, const AttributeMap& interaction_map, AttributeMap& global_state) const {
  try {
    boost::python::dict py_interaction_map;
    Python::convert(interaction_map, py_interaction_map);
    
    boost::python::dict py_global_state;
    Python::convert(global_state, py_global_state);
    
    object py_function = python_.get_function(function_name);
    object py_result = py_function(py_interaction_map, py_global_state);
    Python::convert(py_global_state, global_state);
    
    string result;
    Python::convert(py_result, result);
    return result;
  } catch (boost::python::error_already_set&) {
    python_.throw_error();
  }
  
  return string();
}

} // namespace Backend
} // namespace PlayToLearn
