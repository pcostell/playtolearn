/*
 * File: backend/external/PythonTransitionFn.hpp
 */

#pragma once

#include <stdexcept>
#include <string>
#include <map>

#include <boost/python.hpp>

#include "backend/external/ExternalTransitionFn.hpp"
#include "backend/external/Python.hpp"

namespace PlayToLearn {
namespace Backend {

/** class declarations */

class AttributeMap;

/** class definitions */

// The PythonTransitionFn class represents an executable Python script which
// describes state transitions.
class PythonTransitionFn : public ExternalTransitionFn {
public:
  // The Ptr typedef allows us to refer to shared_ptr<PythonTransitionFn> smart
  // pointers as PythonTransitionFn::Ptr. A const version is provided as well.
  typedef boost::shared_ptr<PythonTransitionFn> Ptr;
  typedef boost::shared_ptr<const PythonTransitionFn> ConstPtr;
  
  // The PythonTransitionFn accepts the Python code which should be executed.
  explicit PythonTransitionFn(const std::string& code);
  
  // See the corresponding comment in ExternalTransitionFn.hpp.
  int execute(const std::string& function_name,
              const AttributeMap& interaction_map,
              AttributeMap& global_state) const;

private:
  // member variables
  Python python_;
};

} // namespace Backend
} // namespace PlayToLearn
