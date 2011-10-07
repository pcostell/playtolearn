#define BOOST_TEST_MODULE PythonFunction test
#include <boost/test/unit_test.hpp> 
// Using the /included directory as a hack b/c we couldn't get the library linked properly.
// See: http://www.boost.org/doc/libs/1_35_0/libs/test/doc/components/utf/compilation.html

/* Good Boost Unit Test Tutorial:
http://www.boost.org/doc/libs/1_47_0/libs/test/doc/html/tutorials/new-year-resolution.html
*/
#include <string>
#include <map>
#include "python_function.hpp"



struct ValidSetup {
	std::map<std::string, std::string> data;
	EduGame::PythonFunction func;

	static const std::string validFunctionString;

	ValidSetup() : func(validFunctionString){
		data["state"] = "11";
	}
};

const std::string ValidSetup::validFunctionString = "def translate(m):\n\tm['state'] = '14'";

BOOST_FIXTURE_TEST_SUITE(ValidPython, ValidSetup)

BOOST_AUTO_TEST_CASE( normal_use_test )
{
	BOOST_CHECK_EQUAL(data["state"], "11");
	func.execute("translate", data);
	BOOST_CHECK_EQUAL(data["state"], "14");
}

BOOST_AUTO_TEST_CASE( bad_method_name) {
	BOOST_CHECK_THROW(func.execute("garbage", data), EduGame::PythonFunction::PythonExecutionError);
}

BOOST_AUTO_TEST_SUITE_END()
