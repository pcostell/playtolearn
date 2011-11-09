// This must be the first #include
#include <boost/python/detail/wrap_python.hpp>
#include "backend/PythonFunction.hpp"
#include <boost/lexical_cast.hpp>
#include <boost/python/suite/indexing/map_indexing_suite.hpp>
#include <iostream>

using namespace PlayToLearn::Backend;

using namespace boost::python;
using namespace std;

//////////////////////
// Public Functions //
//////////////////////

PythonFunction::PythonExecutionError::PythonExecutionError(const string & what_arg) : runtime_error(what_arg) {

}

PythonFunction::PythonFunction(const string & pythonCode) {
  try {
    Py_Initialize();
    mainModule = import("__main__");
    object mainNamespace = mainModule.attr("__dict__");

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


    object ignored = exec(str(pythonCode), mainNamespace);
    } catch (const error_already_set&) {
      handlePythonError();
    }
}


string PythonFunction::execute(const string & functionName, const map<string, string> & state) const {

	try {

    dict pythonMap;

    for (map<string, string>::const_iterator it = state.begin(); it != state.end(); ++it) {
      pythonMap[it->first] = it->second;
    }

    object processFunction = mainModule.attr(str(functionName));

    object result = processFunction(pythonMap);

    extract<string> strRes(result);
    if (!strRes.check()) {
      extract<int> intRes(result);
      return boost::lexical_cast<string>(intRes);
    }
    return strRes;

  } catch (const error_already_set&) {
    handlePythonError();
  }
  return string();
}

///////////////////////
// Private Functions //
///////////////////////

void PythonFunction::handlePythonError() const {
  PyErr_Print();
  boost::python::object sys(boost::python::handle<>(PyImport_ImportModule("sys")));
  boost::python::object err = sys.attr("stderr");
  string err_text = boost::python::extract<string>(err.attr("getvalue")());
  PyErr_Clear();
  throw PythonExecutionError(err_text);
}
