#include <Python.h>

#include "python_function.hpp"

#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include <iostream>

using namespace EduGame;

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
    PyRun_SimpleString("import cStringIO");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.stderr = cStringIO.StringIO()");
    PyRun_SimpleString("sys.stdout = cStringIO.StringIO()");

    object ignored = exec(str(pythonCode), mainNamespace);
    } catch ( error_already_set ) {
      handlePythonError();
    }
}


void PythonFunction::execute(string functionName, map<string, string> & state) const {

	try {

    dict pythonMap;

    for (map<string, string>::iterator it = state.begin(); it != state.end(); ++it) {
      pythonMap[it->first] = it->second;
    }

    object processFunction = mainModule.attr(str(functionName));

    processFunction(pythonMap);

    extractMapFromDict(state, pythonMap);
      
  } catch( error_already_set ) {
    handlePythonError();
  }
}

///////////////////////
// Private Functions //
///////////////////////

void PythonFunction::extractMapFromDict(map<string, string> & cppMap, 
                                        const boost::python::dict & pythonDict) const {
    size_t count = boost::python::extract<size_t>(pythonDict.attr("__len__")());
    object keys = pythonDict.iterkeys();
    cppMap.clear();
    for (size_t i = 0; i < count; ++i)
    {
      object key = keys.attr( "next" )();
      object value = pythonDict.get(key);
      string strKey = extract<string>(key);
      string strValue = extract<string>(value);
      cppMap[strKey] = strValue;
    }
}

void PythonFunction::handlePythonError() const {
  PyErr_Print();
  boost::python::object sys(boost::python::handle<>(PyImport_ImportModule("sys")));    
  boost::python::object err = sys.attr("stderr");    
  string err_text = boost::python::extract<string>(err.attr("getvalue")());
  throw PythonExecutionError(err_text);
  PyErr_Clear();
}
