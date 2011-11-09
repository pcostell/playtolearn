/*
 * File: backend/AttributeMap.cpp
 */

#include "backend/AttributeMap.hpp"

using namespace std;

namespace PlayToLearn {
namespace Backend {

///////////////////////////////////////////////////////
// AttributeMap free function implementation details //
///////////////////////////////////////////////////////

/** public */

ostream& operator<<(ostream& output, const AttributeMap& attribute_map) {
  output << attribute_map.size() << '\n';
  for (AttributeMap::const_iterator itr = attribute_map.begin(); itr != attribute_map.end(); ++itr)
    output << itr->first << '\n' << itr->second << '\n';
  
  return output;
}

istream& operator>>(istream& input, AttributeMap& attribute_map) {
  string line;
  getline(input, line);
  size_t num_pairs = boost::lexical_cast<size_t>(line);
  
  string new_attribute;
  string new_value;
  for (size_t i = 0; i < num_pairs; ++i) {
    getline(input, new_attribute);
    getline(input, new_value);
    attribute_map.set_value(new_attribute, new_value);
  }
  
  assert(!input.fail());
  return input;
}

} // namespace Backend
} // namespace PlayToLearn
