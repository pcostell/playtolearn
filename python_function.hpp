#pragma once

#include <map>
#include <string>

#include <Python.h>
#include <boost/python.hpp>

namespace EduGame {

class PythonFunction {
public:
	PythonFunction(const std::string & pythonCode);
	
	void execute(std::string functionName, std::map<std::string, std::string> & state);

private:

  void extractMapFromDict(std::map<std::string, std::string> & cppMap, const boost::python::dict & pythonDict);


	std::string pythonCode;
};

} /* namespace EduGame */