/*
 * File: AttributeMap.hpp
 */

#pragma once

#include <cassert>
#include <string>
#include <map>
#include <ostream>
#include <istream>
#include <boost/lexical_cast.hpp>

namespace PlayToLearn {
namespace Backend {

//////////////////////////////////
// AttributeMap class interface //
//////////////////////////////////

/**
 * The AttributeMap represents a pairing of string attributes with corresponding
 * string values.
 */
class AttributeMap {
public:
  /**
   * iterator represents a read-only iterator over attribute/value pairs in this
   * map. const_iterator is the same type, but is provided for consistency.
   */
  typedef std::map<std::string, std::string>::const_iterator iterator;
  typedef std::map<std::string, std::string>::const_iterator const_iterator;
  
  /**
   * size returns the number of attribute/value pairs in this map.
   */
  std::size_t size() const;
  
  /**
   * begin returns an iterator to the first attribute/value pair in the map. It
   * is made read-only in order to control what can be modified.
   */
  iterator begin() const;
  
  /**
   * end returns an iterator to the end of the internal attribute/value map. It
   * is read-only for the same reason stated for begin.
   */
  iterator end() const;

  /**
   * contains returns true if and only if the attribute with the specified
   * name exists in the map.
   */
  bool contains(const std::string& attribute) const;

  /**
   * get_value returns the value associated with the particular attribute name
   * specified, converted to the specified data type.
   */
  template <typename T>
  T value(const std::string& attribute) const;

  /**
   * set_value sets the value associated with the given attribute name. If the
   * attribute doesn't already exist in the map, it will be inserted.
   */
  void set_value(const std::string& attribute, const std::string& value);

private:
  //////////////////////
  // member variables //
  //////////////////////

  std::map<std::string, std::string> attributes_;
};

/////////////////////////////////
// AttributeMap free functions //
/////////////////////////////////

/**
 * operator<< describes how to serialize an AttributeMap and write it to an
 * output stream.
 */
std::ostream& operator<<(std::ostream& output, const AttributeMap& attr_map);

/**
 * operator>> describes how to re-hydrate an AttributeMap from an input stream.
 */
std::istream& operator>>(std::istream& input, AttributeMap& attr_map);

////////////////////////////////////
// AttributeMap inlined functions //
////////////////////////////////////

/** public */

inline std::size_t AttributeMap::size() const {
  return attributes_.size();
}

inline AttributeMap::iterator AttributeMap::begin() const {
  return attributes_.begin();
}

inline AttributeMap::iterator AttributeMap::end() const {
  return attributes_.end();
}

inline bool AttributeMap::contains(const std::string& attribute) const {
  return attributes_.count(attribute);
}

////////////////////////////////////////////
// AttributeMap template member functions //
////////////////////////////////////////////

/** public */

template <typename T>
inline T AttributeMap::value(const std::string& attribute) const {
  // We perform the conversion using lexical_cast. If the attribute's value is
  // invalid, the operation will throw a bad_lexical_cast exception.
  return boost::lexical_cast<T>(value<std::string>(attribute));
}

template <>
inline std::string AttributeMap::value<std::string>(const std::string& attribute) const {
  // Check that the attribute name is in the map. If it isn't, this is a
  // programming error that can't be recovered.
  std::map<std::string, std::string>::const_iterator itr = attributes_.find(attribute);
  assert(itr != attributes_.end());
  return itr->second;
}

} // namespace Backend
} // namespace PlayToLearn