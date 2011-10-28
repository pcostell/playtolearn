#define BOOST_TEST_MODULE PythonFunction test
#include <boost/test/unit_test.hpp>

/* Good Boost Unit Test Tutorial:
http://www.boost.org/doc/libs/1_47_0/libs/test/doc/html/tutorials/new-year-resolution.html
*/
#include <string>
#include <map>
#include "python_function.hpp"

using namespace std;
using namespace EduGame;

struct ValidSetup {
	map<string, string> data;
	PythonFunction func;

	static const string validFunctionString;

	ValidSetup() : func(validFunctionString){
		data["state"] = "11";
	}
};

const string ValidSetup::validFunctionString = "def translate(m):\n\treturn 2";

BOOST_FIXTURE_TEST_SUITE(ValidPython, ValidSetup)

BOOST_AUTO_TEST_CASE( normal_use_test )
{
	BOOST_CHECK_EQUAL(data["state"], "11");
	//func.execute("translate", data);
	BOOST_CHECK_EQUAL(data["state"], "14");
}
/*
BOOST_AUTO_TEST_CASE( bad_method_name)
{
	BOOST_CHECK_THROW(func.execute("garbage", data),
                    PythonFunction::PythonExecutionError);
}

BOOST_AUTO_TEST_CASE( bad_attr_access )
{
  data.clear();
  BOOST_CHECK_THROW(func.execute("translate", data),
                    PythonFunction::PythonExecutionError);
}

BOOST_AUTO_TEST_CASE ( multiple_function_call )
{
  func.execute("translate", data);
  BOOST_CHECK_EQUAL(data["state"], "14");
  data["state"] = 22;
  func.execute("translate", data);
  BOOST_CHECK_EQUAL(data["state"], "14");
}
*/
BOOST_AUTO_TEST_SUITE_END()
/*
BOOST_AUTO_TEST_SUITE(InvalidPython)

BOOST_AUTO_TEST_CASE( invalid_python_code_outside_function ) {
  BOOST_CHECK_THROW(PythonFunction func("blahblahblah\ndef translate(m):\n\tprint m['state']"),
                    PythonFunction::PythonExecutionError);
}

BOOST_AUTO_TEST_CASE( invalid_code_inside_function ) {
  PythonFunction func("def translate(m):\n\tBLAH\n\tprint m['state']");
  map<string, string> m;
  BOOST_CHECK_THROW(func.execute("translate", m),
                    PythonFunction::PythonExecutionError);
}

BOOST_AUTO_TEST_SUITE_END()*/
