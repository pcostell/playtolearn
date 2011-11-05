/*
 * File: UniqueID.hpp
 */

#pragma once

namespace PlayToLearn {
namespace Backend {

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
   * The UniqueID default constructor initializes a UniqueID with the invalid
   * ID as its underlying value. If the client wants a new ID, use the create
   * factory function instead.
   */
  UniqueID();
  
  /**
   * This UniqueID constructor takes a single argument representing the
   * underlying integer value that should represent this particular ID. No
   * default constructor is offered because the create class function should be
   * used instead.
   */
  explicit UniqueID(int value);
  
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
   * create is a factory function which generates a unique identifying ID.
   */
  static const UniqueID create();
  
  /**
   * kInvalid is a constant which represents an invalid ID's integer.
   */
  static const int kInvalid = -1;
  
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
UniqueID<T>::UniqueID() : value_(kInvalid)
{ /* empty body */ }

template <typename T>
UniqueID<T>::UniqueID(int value) : value_(value)
{ /* empty body */ }

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

} // namespace Backend
} // namespace PlayToLearn
