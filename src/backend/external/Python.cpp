/*
 * File: backend/external/Python.cpp
 */

#include <boost/python/detail/wrap_python.hpp> // must be included first
#include "backend/external/Python.hpp"
#include "util/ErrorTypes.hpp"
#include <sstream>
#include <string>

using namespace std;
using boost::python::object;

namespace PlayToLearn {
namespace Backend {

//////////////////////////////////////////
// Python member implementation details //
//////////////////////////////////////////

/** public */

Python::Python(const std::string& code) {
  try {
    Py_Initialize();
    main_module_ = boost::python::import("__main__");
    boost::python::object main_namespace = main_module_.attr("__dict__");
    
    // Redirect stdout and stderr output:
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
    
    boost::python::exec(boost::python::str(code), main_namespace);
  } catch (const boost::python::error_already_set&) {
    throw_error();
  }
}

object Python::get_function(const std::string& function_name) const {
  return main_module_.attr(boost::python::str(function_name));
}

void Python::throw_error() const {
  PyErr_Print();
  object sys(boost::python::handle<>(PyImport_ImportModule("sys")));
  object err = sys.attr("stderr");
  std::string err_text = boost::python::extract<std::string>(err.attr("getvalue")());
  PyErr_Clear();
  
  throw Util::PythonExecutionError(err_text);
}

//////////////////////////////////////////////////
// Python class function implementation details //
//////////////////////////////////////////////////

/** public */

void Python::convert(const AttributeMap& source, boost::python::dict& dest) {
  for (AttributeMap::const_iterator itr = source.begin(); itr != source.end(); ++itr)
    dest[itr->first] = itr->second;
}

void Python::convert(const boost::python::dict& source, AttributeMap& dest) {
  size_t count = boost::python::extract<size_t>(source.attr("__len__")());
  object keys = source.iterkeys();
  dest.clear();
  for (size_t i = 0; i < count; ++i) {
    object python_key = keys.attr("next")();
    dest.set_value(
      string(boost::python::extract<string>(python_key)),
      string(boost::python::extract<string>(source.get(python_key)))
    );
  }
}

} // namespace Backend
} // namespace PlayToLearn
