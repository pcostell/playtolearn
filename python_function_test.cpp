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

BOOST_AUTO_TEST_CASE( normal_use_test )
{
	std::map<std::string, std::string> data;
	data["state"] = "11";
	std::string pythonFunction("def translate(m):\n\tm['state'] = '14'");
	EduGame::PythonFunction func(pythonFunction);
	func.execute("translate", data);
	BOOST_CHECK_EQUAL(data["state"], "14");
}

// EOF