/*
 * File: frontend/Interaction.hpp
 */

#pragma once

#include "backend/AttributeMap.hpp"
#include "backend/Object.hpp"
#include <string>
#include <boost/shared_ptr.hpp>

namespace PlayToLearn {
namespace Frontend {

/////////////////////////////////
// Interaction class interface //
/////////////////////////////////

/**
 * The Interaction class hierarchy provides the frontend engine a means of
 * storing user interactions with the game in a way that can be passed on to the
 * backend engine.
 */
class Interaction {
public:
  /**
   * The Ptr typedef allows us to refer to shared_ptr<Interaction> smart
   * pointers as Interaction::Ptr. A const version is provided as well.
   */
  typedef boost::shared_ptr<Interaction> Ptr;
  typedef boost::shared_ptr<const Interaction> ConstPtr;

  /**
   * The Type enum describes what kind of interaction this object represents.
   */
  enum Type {
    INTERACT_GENERIC,
    INTERACT_TEXT_ANSWER,
    INTERACT_FREE_RESPONSE_ANSWER,
    //INTERACT_MULTIPLE_CHOICE_ANSWER,
  };

  /**
   * The Interaction constructor initializes an Interaction object with the
   * specified target of the interaction.
   */
  explicit Interaction(Backend::Object::ID object_id);

  /**
   * The Interaction destructor is declared virtual so that the class may be
   * used polymorphically.
   */
  virtual ~Interaction();

  /**
   * type returns the specific subclass of Interaction represented by this
   * object.
   */
  virtual Type type() const = 0;

  /**
   * object_id returns the ID of the interactive object with which the user
   * wants to interact.
   */
  Backend::Object::ID object_id() const;

  /**
   * attribute_map converts this particular Interaction object into an
   * AttributeMap object that can be passed to the backend.
   */
  const Backend::AttributeMap& attribute_map() const;

protected:
  //////////////////////
  // member functions //
  //////////////////////

  template <typename T>
  void set_value(const std::string& attribute, const T& value);

private:
  //////////////////////
  // member variables //
  //////////////////////

  Backend::Object::ID object_id_;
  Backend::AttributeMap attribute_map_;
};

///////////////////////////////////
// Interaction inlined functions //
///////////////////////////////////

/** public */

inline Backend::Object::ID Interaction::object_id() const {
  return object_id_;
}

inline const Backend::AttributeMap& Interaction::attribute_map() const {
  return attribute_map_;
}

////////////////////////////////////
// Interaction template functions //
////////////////////////////////////

/** protected */

/*
 * set_value is used by Interaction's subclasses as a means of modifying the
 * data in the AttributeMap which the Interaction superclass stores.
 */
template <typename T>
inline void Interaction::set_value(const std::string& attribute, const T& value) {
  attribute_map_.set_value(attribute, value);
}

} // namespace Frontend
} // namespace PlayToLearn
