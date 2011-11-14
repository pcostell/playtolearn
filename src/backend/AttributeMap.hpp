/*
 * File: backend/AttributeMap.hpp
 */

#pragma once

#include <string>
#include <map>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>
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
   * attribute doesn't already exist in the map, it will be inserted. The type
   * of value inserted into the map is templatized so that any data type may
   * be converted into a string.
   */
  template <typename T>
  void set_value(const std::string& attribute, const T& value);
  
  /**
   * clear erases all elements in the AttributeMap so that afterward, it is
   * completely empty.
   */
  void clear();

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  std::map<std::string, std::string> attributes_;
  
  /////////////////////
  // private methods //
  /////////////////////
  
  friend class boost::serialization::access;
  
  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version);
};

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

inline void AttributeMap::clear() {
  attributes_.clear();
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

template <typename T>
inline void AttributeMap::set_value(const std::string& attribute, const T& value) {
  // We perform the conversion using lexical_cast. The given value cannot be
  // converted to a string, the operation will throw a bad_lexcial_cast
  // exception.
  set_value(attribute, boost::lexical_cast<std::string>(value));
}

template <>
inline void AttributeMap::set_value(const std::string& attribute, const std::string& value) {
  attributes_[attribute] = value;
}

template <>
inline void AttributeMap::set_value(const std::string& attribute, const char* const& value) {
  // Convert from C style string to C++ style string:
  set_value(attribute, std::string(value));
}

/** private */

template <typename Archive>
void AttributeMap::serialize(Archive& ar, const unsigned int version) {
  ar & boost::serialization::make_nvp("attributes", attributes_);
}

} // namespace Backend
} // namespace PlayToLearn
