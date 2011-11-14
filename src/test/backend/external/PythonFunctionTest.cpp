#define BOOST_TEST_MODULE PythonFunction test
#include <boost/test/unit_test.hpp>

/* Good Boost Unit Test Tutorial:
http://www.boost.org/doc/libs/1_47_0/libs/test/doc/html/tutorials/new-year-resolution.html
*/
#include <string>
#include <map>
#include "backend/external/ExternalFunction.hpp"
#include "backend/external/PythonExecutor.hpp"
#include "backend/external/PythonConverter.hpp"

using namespace std;
using namespace PlayToLearn::Backend;

struct ValidSetup {
	map<string, string> data;
	ExternalFunction<Python> func;

	static const string validFunctionString;

	ValidSetup() : func(validFunctionString){
		data["state"] = "11";
	}
};

const string ValidSetup::validFunctionString = "def translate(m):\n\tif m['state'] == '11':\n\t\treturn '2'\n\treturn '25'";


string callWithConstMap(const string & fnName, const map<string, string> & data, ExternalFunction<Python> & func) {
  return func.execute<string>(fnName, data);
}

BOOST_FIXTURE_TEST_SUITE(ValidPython, ValidSetup)

/* Test normal usage. */
BOOST_AUTO_TEST_CASE( normal_use_test )
{
	BOOST_CHECK_EQUAL(data["state"], "11");
	string result = func.execute<string>("translate", data);
	BOOST_CHECK_EQUAL(result, "2");
}

/* Test calling bad function name. */
BOOST_AUTO_TEST_CASE( bad_method_name)
{
  BOOST_CHECK_THROW(func.execute<string>("translabe", data),
                    Language::LanguageError);
}

/* Test accessing date that doesn't exist. */
BOOST_AUTO_TEST_CASE( bad_attr_access )
{
  data.clear();
  BOOST_CHECK_THROW(func.execute<string>("translate", data),
                    Language::LanguageError);
}

/* Test that multiple executions works. */
BOOST_AUTO_TEST_CASE ( multiple_function_call )
{
  string result = func.execute<string>("translate", data);
  BOOST_CHECK_EQUAL(result, "2");
  data["state"] = 22;
  result = func.execute<string>("translate", data);
  BOOST_CHECK_EQUAL(result, "25");
}

BOOST_AUTO_TEST_SUITE_END()

/* Test that error is thrown for invalid python. */
BOOST_AUTO_TEST_SUITE(InvalidPython)

BOOST_AUTO_TEST_CASE( invalid_python_code_outside_function ) {
  BOOST_CHECK_THROW(ExternalFunction<Python> func("blahblahblah\ndef translate(m):\n\tprint m['state']"),
                    Language::LanguageError);
}

/* Test that invalid code inside function throws error on execution. */
BOOST_AUTO_TEST_CASE( invalid_code_inside_function ) {
  ExternalFunction<Python> func("def translate(m):\n\tBLAH\n\tprint m['state']");
  map<string, string> m;
  BOOST_CHECK_THROW(func.execute<string>("translate", m),
                    Language::LanguageError);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_CASE( non_strings ) {
  ExternalFunction<Python> func("def translate(m):\n\treturn 12");
  map<string, string> m;
  BOOST_CHECK_EQUAL(func.execute<int>("translate", m), 12);
}

BOOST_AUTO_TEST_CASE( string_arg ) {
  ExternalFunction<Python> func("def translate(str):\n\treturn str + \" world!\"");
  string str = "hello";
  BOOST_CHECK_EQUAL(func.execute<string>("translate", str), "hello world!");

}

BOOST_AUTO_TEST_CASE( can_change_non_const_map ) {
  ExternalFunction<Python> func("def translate(m):\n\tm['hello'] = 'world'\n\treturn \"12\"");
  map<string, string> m;
  BOOST_CHECK_EQUAL(func.execute<string>("translate", m), "12");
  BOOST_CHECK_EQUAL(m["hello"], "world");;
}
