/*
 * Good Boost Unit Test Tutorial:
 * http://www.boost.org/doc/libs/1_47_0/libs/test/doc/html/tutorials/new-year-resolution.html
 */

#define BOOST_TEST_MODULE PythonTransitionFn test

#include <string>
#include <map>

#include <boost/test/unit_test.hpp>

#include "util/ErrorTypes.hpp"
#include "backend/AttributeMap.hpp"
#include "backend/external/PythonTransitionFn.hpp"

using namespace std;
using PlayToLearn::Backend::AttributeMap;
using PlayToLearn::Backend::PythonTransitionFn;

struct ValidSetup {
	AttributeMap data;
  AttributeMap globalState;
	PythonTransitionFn func;

	static const string validFnString;

	ValidSetup() : func(validFnString){
		data.set_value("state", "11");
	}
};

const string ValidSetup::validFnString = "def translate(m, g):\n\tif m['state'] == '11':\n\t\treturn 2\n\treturn 25";

BOOST_FIXTURE_TEST_SUITE(ValidPython, ValidSetup)

/* Test normal usage. */
BOOST_AUTO_TEST_CASE( normal_use_test )
{
	BOOST_CHECK_EQUAL(data.value<string>("state"), "11");
	int result = func.execute("translate", data, globalState);
	BOOST_CHECK_EQUAL(result, 2);
}

/* Test calling bad function name. */
BOOST_AUTO_TEST_CASE( bad_method_name)
{
  BOOST_CHECK_THROW(func.execute("translabe", data, globalState),
                    PlayToLearn::Util::PythonExecutionError);
}

/* Test accessing data that doesn't exist. */
BOOST_AUTO_TEST_CASE( bad_attr_access )
{
  data.clear();
  BOOST_CHECK_THROW(func.execute("translate", data, globalState),
                    PlayToLearn::Util::PythonExecutionError);
}

/* Test that multiple executions works. */
BOOST_AUTO_TEST_CASE ( multiple_function_call )
{
  int result = func.execute("translate", data, globalState);
  BOOST_CHECK_EQUAL(result, 2);
  data.set_value("state", ":22");
  result = func.execute("translate", data, globalState);
  BOOST_CHECK_EQUAL(result, 25);
}

BOOST_AUTO_TEST_SUITE_END()

/* Test that error is thrown for invalid python. */
BOOST_AUTO_TEST_SUITE(InvalidPython)

BOOST_AUTO_TEST_CASE( invalid_python_code_outside_function ) {
  BOOST_CHECK_THROW(PythonTransitionFn func("blahblahblah\ndef translate(m, n):\n\ta = m['state']"),
                    PlayToLearn::Util::PythonExecutionError);
}

/* Test that invalid code inside function throws error on execution. */
BOOST_AUTO_TEST_CASE( invalid_code_inside_function ) {
  PythonTransitionFn func("def translate(m, n):\n\tBLAH\n\ta = m['state']");
  AttributeMap m, n;
  BOOST_CHECK_THROW(func.execute("translate", m, n),
                    PlayToLearn::Util::PythonExecutionError);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE( can_change_global_state ) {
  PythonTransitionFn func("def translate(m, n):\n\tn['hello'] = 'world'\n\treturn 12");
  AttributeMap m, n;
  BOOST_CHECK_EQUAL(func.execute("translate", m, n), 12);
  BOOST_CHECK_EQUAL(n.value<string>("hello"), "world");;
}
