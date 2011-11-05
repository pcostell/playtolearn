/*
 * File: AttributeMap.cpp
 */

#include "AttributeMap.hpp"
#include <boost/lexical_cast.hpp>

using namespace std;

namespace PlayToLearn {
namespace Backend {

/////////////////////////////////////////////////////////
// AttributeMap member function implementation details //
/////////////////////////////////////////////////////////

/** public */

void AttributeMap::set_value(const string& attribute, const string& value) {
  assert(attribute.find('\n') == string::npos);
  assert(value.find('\n') == string::npos);
  attributes_[attribute] = value;
}

///////////////////////////////////////////////////////
// AttributeMap free function implementation details //
///////////////////////////////////////////////////////

/** public */

ostream& operator<<(ostream& output, const AttributeMap& attr_map) {
  output << attr_map.size() << '\n';
  for (AttributeMap::const_iterator itr = attr_map.begin(); itr != attr_map.end(); ++itr)
    output << itr->first << '\n' << itr->second << '\n';
  
  return output;
}

istream& operator>>(istream& input, AttributeMap& attr_map) {
  string line;
  getline(input, line);
  size_t num_pairs = boost::lexical_cast<size_t>(line);
  
  string new_attribute;
  string new_value;
  for (size_t i = 0; i < num_pairs; ++i) {
    getline(input, new_attribute);
    getline(input, new_value);
    attr_map.set_value(new_attribute, new_value);
  }
  
  assert(!input.fail());
  return input;
}

} // namespace Backend
} // namespace PlayToLearn
