#include <Python.h>

#include "python_function.hpp"

#include <boost/python/suite/indexing/map_indexing_suite.hpp>

#include <iostream>

using namespace EduGame;

using namespace boost::python;

//////////////////////
// Public Functions //
//////////////////////

/* TODO: THIS IS STILL VERY FINICKY. MUST MANAGE ERRORS BETTER. */

PythonFunction::PythonExecutionError::PythonExecutionError(const std::string & what_arg) : runtime_error(what_arg) {}

PythonFunction::PythonFunction(const std::string & pythonCode) : pythonCode(pythonCode) {}


void PythonFunction::execute(std::string functionName, std::map<std::string, std::string> & state) {

	try {

    Py_Initialize();

    object mainModule = import("__main__");
    object mainNamespace = mainModule.attr("__dict__");

  dict pythonMap;
    for (std::map<std::string, std::string>::iterator it = state.begin(); it != state.end(); ++it) {
      pythonMap[it->first] = it->second;
    }

    PyRun_SimpleString("import cStringIO");
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.stderr = cStringIO.StringIO()");

    object ignored = exec(str(pythonCode), mainNamespace);

    for (std::map<std::string, std::string>::iterator it = state.begin(); it != state.end(); ++it) {
      pythonMap[it->first] = it->second;
    }
    object processFunction = mainModule.attr(str(functionName));

    processFunction(pythonMap);

    extractMapFromDict(state, pythonMap);
      
  } catch( error_already_set ) {
    PyErr_Print();
    boost::python::object sys(boost::python::handle<>(PyImport_ImportModule("sys")));    
    boost::python::object err = sys.attr("stderr");    
    std::string err_text = boost::python::extract<std::string>(err.attr("getvalue")());
    throw PythonExecutionError(err_text);
  }
}

///////////////////////
// Private Functions //
///////////////////////

void PythonFunction::extractMapFromDict(std::map<std::string, std::string> & cppMap, 
                                        const boost::python::dict & pythonDict) {
      size_t count = boost::python::extract<size_t>(pythonDict.attr("__len__")());
    object keys = pythonDict.iterkeys();
    cppMap.clear();
    for (size_t i = 0; i < count; ++i)
    {
      object key = keys.attr( "next" )();
      object value = pythonDict.get(key);
      std::string strKey = extract<std::string>(key);
      std::string strValue = extract<std::string>(value);
      cppMap[strKey] = strValue;
    }
}
