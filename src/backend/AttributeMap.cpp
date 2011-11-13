/*
 * File: backend/AttributeMap.cpp
 */

#include "util/ErrorTypes.hpp"
#include "backend/AttributeMap.hpp"
#include <sstream>

using namespace std;

namespace PlayToLearn {
namespace Backend {

////////////////////////////////////////////////
// AttributeMap member implementation details //
////////////////////////////////////////////////

/** public */

template <>
string AttributeMap::value<string>(const string& attribute) const {
  // Check that the attribute name is in the map. If it isn't, this is a
  // programming error that can't be recovered.
  map<string, string>::const_iterator itr = attributes_.find(attribute);
  if (itr == attributes_.end()) {
    stringstream err_ss;
    err_ss << "Requested attribute not in map: " << attribute;
    throw Util::MissingAttributeError(err_ss.str());
  }
  
  return itr->second;
}

} // namespace Backend
} // namespace PlayToLearn
