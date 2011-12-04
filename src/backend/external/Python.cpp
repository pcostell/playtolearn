/*
 * File: backend/external/Python.cpp
 */

#include <boost/python/detail/wrap_python.hpp> // must be included first

#include "backend/external/Python.hpp"

#include <sstream>
#include <string>

#include "util/ErrorTypes.hpp"
#include "backend/AttributeMap.hpp"

using namespace std;
namespace python = boost::python;

namespace PlayToLearn {
namespace Backend {

/** Python member functions, public */

Python::Python(const string& code) {
  try {
    Py_Initialize();
    main_module_ = python::import("__main__");
    python::object main_namespace = main_module_.attr("__dict__");
    
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
    
    python::exec(python::str(code), main_namespace);
  } catch (python::error_already_set&) {
    throw_error();
  }
}

python::object Python::get_function(const string& function_name) const {
  return main_module_.attr(python::str(function_name));
}

void Python::throw_error() const {
  PyErr_Print();
  python::object sys(python::handle<>(PyImport_ImportModule("sys")));
  python::object err = sys.attr("stderr");
  string err_text = python::extract<string>(err.attr("getvalue")());
  PyErr_Clear();
  
  throw Util::PythonExecutionError(err_text);
}

/** Python class functions, public */

void Python::convert(const AttributeMap& source, boost::python::dict& dest) {
  for (AttributeMap::const_iterator itr = source.begin(); itr != source.end(); ++itr)
    dest[itr->first] = itr->second;
}

void Python::convert(const python::dict& source, AttributeMap& dest) {
  size_t count = python::extract<size_t>(source.attr("__len__")());
  python::object keys = source.iterkeys();
  dest.clear();
  for (size_t i = 0; i < count; ++i) {
    python::object python_key = keys.attr("next")();
    dest.set_value(
      string(python::extract<string>(python_key)),
      string(python::extract<string>(source.get(python_key)))
    );
  }
}

} // namespace Backend
} // namespace PlayToLearn
