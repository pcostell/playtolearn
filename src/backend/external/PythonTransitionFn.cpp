#include "boost/python/detail/wrap_python.hpp"

#include "backend/external/PythonTransitionFn.hpp"

using namespace boost::python;
using namespace std;

namespace PlayToLearn {
namespace Backend {

PythonTransitionFn::PythonTransitionFn(const string& code) : ExternalTransitionFn(code), python(code) {

}


string PythonTransitionFn::execute(const string & function_name, const AttributeMap & attributes, AttributeMap & scriptGlobalState) const{
  try {
    dict pyAttributes;
    Python::convert(attributes, pyAttributes);
    dict pyGlobalState;
    Python::convert(scriptGlobalState, pyGlobalState);
    object processFn = python.get_function(function_name);

    object pyResult = processFn(pyAttributes, pyGlobalState);
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