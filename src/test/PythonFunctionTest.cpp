#define BOOST_TEST_MODULE PythonFunction test
#include <boost/test/unit_test.hpp>

/* Good Boost Unit Test Tutorial:
http://www.boost.org/doc/libs/1_47_0/libs/test/doc/html/tutorials/new-year-resolution.html
*/
#include <string>
#include <map>
#include "../Backend/PythonFunction.hpp"

using namespace std;
using namespace PlayToLearn::Backend;

struct ValidSetup {
	map<string, string> data;
	PythonFunction func;

	static const string validFunctionString;

	ValidSetup() : func(validFunctionString){
		data["state"] = "11";
	}
};

const string ValidSetup::validFunctionString = "def translate(m):\n\tif m['state'] == '11':\n\t\treturn 2\n\treturn 25";

BOOST_FIXTURE_TEST_SUITE(ValidPython, ValidSetup)

/* Test normal usage. */
BOOST_AUTO_TEST_CASE( normal_use_test )
{
	BOOST_CHECK_EQUAL(data["state"], "11");
	string result = func.execute("translate", data);
	BOOST_CHECK_EQUAL(result, "2");
}

/* Test calling bad function name. */
BOOST_AUTO_TEST_CASE( bad_method_name)
{
	BOOST_CHECK_THROW(func.execute("garbage", data),
                    PythonFunction::PythonExecutionError);
}

/* Test accessing date that doesn't exist. */
BOOST_AUTO_TEST_CASE( bad_attr_access )
{
  data.clear();
  BOOST_CHECK_THROW(func.execute("translate", data),
                    PythonFunction::PythonExecutionError);
}

/* Test that multiple executions works. */
BOOST_AUTO_TEST_CASE ( multiple_function_call )
{
  string result = func.execute("translate", data);
  BOOST_CHECK_EQUAL(result, "2");
  data["state"] = 22;
  result = func.execute("translate", data);
  BOOST_CHECK_EQUAL(result, "25");
}

BOOST_AUTO_TEST_SUITE_END()

/* Test that error is thrown for invalid python. */
BOOST_AUTO_TEST_SUITE(InvalidPython)

BOOST_AUTO_TEST_CASE( invalid_python_code_outside_function ) {
  BOOST_CHECK_THROW(PythonFunction func("blahblahblah\ndef translate(m):\n\tprint m['state']"),
                    PythonFunction::PythonExecutionError);
}

/* Test that invalid code inside function throws error on execution. */
BOOST_AUTO_TEST_CASE( invalid_code_inside_function ) {
  PythonFunction func("def translate(m):\n\tBLAH\n\tprint m['state']");
  map<string, string> m;
  BOOST_CHECK_THROW(func.execute("translate", m),
                    PythonFunction::PythonExecutionError);
}

BOOST_AUTO_TEST_SUITE_END()
