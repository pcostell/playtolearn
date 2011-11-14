/*
 * File: backend/PythonTransitionFn.cpp
 */

// This must be the first #include
#include <boost/python/detail/wrap_python.hpp>
#include "util/ErrorTypes.hpp"
#include "backend/PythonTransitionFn.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>

using namespace std;
using boost::python::object;

namespace PlayToLearn {
namespace Backend {

//////////////////////////////////////////////////////
// PythonTransitionFn member implementation details //
//////////////////////////////////////////////////////

/** public */

PythonTransitionFn::PythonTransitionFn(const string& python_code) {
  try {
    Py_Initialize();
    main_module_ = boost::python::import("__main__");
    object main_namespace = main_module_.attr("__dict__");
    
    // redirect stdout and stderr output.
    #ifdef PYTHON_VERSION_3
      PyRun_SimpleString("import io");
      PyRun_SimpleString("import sys");
      PyRun_SimpleString("sys.stderr = io.StringIO()");
      PyRun_SimpleString("sys.stdout = io.StringIO()");
    #else
      PyRun_SimpleString("import cStringIO");
      PyRun_SimpleString("import sys");
      PyRun_SimpleString("sys.stderr = cStringIO.StringIO()");
      PyRun_SimpleString("sys.stdout = cStringIO.StringIO()");
    #endif
    
    object ignored = exec(boost::python::str(python_code), main_namespace);
    } catch (const boost::python::error_already_set&) {
      handle_python_error();
    }
}

string PythonTransitionFn::execute(const string& function_name, const AttributeMap& attribute_map) const {
  try {
    boost::python::dict python_map;
    for (AttributeMap::iterator itr = attribute_map.begin(); itr != attribute_map.end(); ++itr)
      python_map[itr->first] = itr->second;
    
    object process_function = main_module_.attr(boost::python::str(function_name));
    object result = process_function(python_map);
    
    boost::python::extract<string> str_res(result);
    if (!str_res.check()) {
      boost::python::extract<int> int_res(result);
      return boost::lexical_cast<string>(int_res);
    }
    
    return str_res;
  } catch (const boost::python::error_already_set&) {
    handle_python_error();
  }
  
  return string();
}

/** private */

void PythonTransitionFn::handle_python_error() const {
  PyErr_Print();
  object sys(boost::python::handle<>(PyImport_ImportModule("sys")));
  object err = sys.attr("stderr");
  string err_text = boost::python::extract<string>(err.attr("getvalue")());
  PyErr_Clear();
  throw Util::PythonExecutionError(err_text);
}

} // namespace Backend
} // namespace PlayToLearn
