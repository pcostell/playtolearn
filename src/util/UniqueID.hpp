/*
 * File: util/UniqueID.hpp
 */

#pragma once

#include "Constants.hpp"
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/lexical_cast.hpp>

namespace PlayToLearn {
namespace Util {

///////////////////////////////////////
// UniqueID template class interface //
///////////////////////////////////////

/**
 * UniqueID is a template class which represents a uniquely identifying integer
 * for the specified class.
 */
template <typename T>
class UniqueID {
public:
  /**
   * This UniqueID constructor takes a single argument representing the
   * underlying integer value that should represent this particular ID. If no ID
   * is specified, the underlying value is the constant, kInvalidID. For a new
   * unique ID, the create class function should be used.
   */
  explicit UniqueID(int value = kInvalidID);
  
  /**
   * value returns the identifying integer so that it may be displayed.
   */
  int value() const;
  
  /**
   * Two UniqueIDs can be compared for equality or inequality.
   */
  bool operator==(const UniqueID& other) const;
  bool operator!=(const UniqueID& other) const;
  
  /**
   * Comparison of UniqueIDs using the < operator is only provided so that they
   * may be stored in set and map structures. It provides no meaningful insight.
   */
  bool operator<(const UniqueID& other) const;
  
  /**
   * serialize reads or writes the underlying integer value using Boost's
   * serialization library.
   */
  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version);
  
  /**
   * create is a factory function which generates a unique identifying ID.
   */
  static const UniqueID create();

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  int value_;
  
  /////////////////////
  // class variables //
  /////////////////////
  
  static int next_available_id_;
};

////////////////////////////////
// UniqueID inlined functions //
////////////////////////////////

/** public */

template <typename T>
inline int UniqueID<T>::value() const {
  return value_;
}

template <typename T>
inline bool UniqueID<T>::operator==(const UniqueID& other) const {
  return value() == other.value();
}

template <typename T>
inline bool UniqueID<T>::operator!=(const UniqueID& other) const {
  return value() != other.value();
}

template <typename T>
inline bool UniqueID<T>::operator<(const UniqueID& other) const {
  return value() < other.value();
}

////////////////////////////////////////
// UniqueID template member functions //
////////////////////////////////////////

/** public */

template <typename T>
UniqueID<T>::UniqueID(int value) : value_(value)
{
  // empty body
}

template <typename T>
template <typename Archive>
void UniqueID<T>::serialize(Archive& ar, const unsigned int version) {
  ar & boost::serialization::make_nvp("value", value_);
}

///////////////////////////////////////
// UniqueID template class functions //
///////////////////////////////////////

/** public */

template <typename T>
const UniqueID<T> UniqueID<T>::create() {
  return UniqueID(next_available_id_++);
}

/** private */

template <typename T>
int UniqueID<T>::next_available_id_ = 0;

} // namespace Util
} // namespace PlayToLearn
