#include "boost/python/detail/wrap_python.hpp"

#include "backend/external/PythonTransitionFunction.hpp"

using namespace boost::python;
using namespace std;

namespace PlayToLearn {
namespace Backend {

PythonTransitionFunction::PythonTransitionFunction(const string& code) : ExternalTransitionFunction(code), python(code) {

}


string PythonTransitionFunction::execute(const string & function_name, const AttributeMap & attributes, AttributeMap & scriptGlobalState) const{
  try {
    dict pyAttributes;
    Python::convert(attributes, pyAttributes);
    dict pyGlobalState;
    Python::convert(scriptGlobalState, pyGlobalState);
    object processFunction = python.get_function(function_name);

    object pyResult = processFunction(pyAttributes, pyGlobalState);
    string result;
    Python::convert(pyResult, result);
    return result;
  } catch (const error_already_set &) {
    python.throwError();
  }
  return string();
}

} // namespace Backend
} // namespace PlayToLearn