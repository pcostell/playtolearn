
#include "backend/external/Python.hpp"
#include "util/ErrorTypes.hpp"

#include <sstream>
#include <string>

namespace PlayToLearn {
namespace Backend {

Python::Python(const std::string& code) {
  try {
    Py_Initialize();
    mainModule = import("__main__");
    boost::python::object mainNamespace = mainModule.attr("__dict__");

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


    boost::python::object ignored = exec(str(code), mainNamespace);
  } catch (const error_already_set&) {
    throwError();
  }
}

boost::python::object Python::get_function(const std::string& function_name) {
  return mainModule.attr(str(function_name));
}

void Python::throwError() const {
  PyErr_Print();
  object sys(boost::python::handle<>(PyImport_ImportModule("sys")));
  object err = sys.attr("stderr");
  std::string err_text = extract<std::string>(err.attr("getvalue")());
  PyErr_Clear();
  throw PythonExecutionError(err_text);
}

template<>
void convert(const AttributeMap & source, boost::python::dict & dest) {
  for (CPPType::const_iterator it = source.begin(); it != source.end(); ++it)
    dest[it->first] = it->second;
}

template<>
void convert(const boost::python::dict & source, AttributeMap & dest) {
  size_t count = extract<size_t>(source.attr("__len__")());
  object keys = source.iterkeys();
  dest.clear();
  for (size_t i = 0; i < count; ++i) {
    object pythonKey = keys.attr("next")();
    object pythonValue = source.get(pythonKey);
    KeyType key = extract<KeyType>(pythonKey);
    ValueType value = extract<ValueType>(pythonValue);
    dest[key] = value;
  }
}

} // namespace Backend
} // namespace PlayToLearn