/*
 * File: InteractionResponse.hpp
 */

#pragma once

#include "backend/AttributeMap.hpp"
#include <boost/shared_ptr.hpp>
#include <string>

namespace PlayToLearn {

/////////////////////////////////////////
// InteractionResponse class interface //
/////////////////////////////////////////

/**
 * InteractionResponse contains information needed to convey response
 * information after an interaction takes place. The backend represents this
 * information in a generic AttributeMap, and the InteractionResponse subclasses
 * know how to perform the proper translations.
 */
class InteractionResponse {
public:
  /**
   * The Ptr typedef allows us to refer to shared_ptr<InteractionResponse>
   * smart pointers as InteractionResponse::Ptr. A const version is provided as
   * well.
   */
  typedef boost::shared_ptr<InteractionResponse> Ptr;
  typedef boost::shared_ptr<const InteractionResponse> ConstPtr;
  
  /**
   * The type enum describes what kind of interaction this response represents.
   */
  enum Type {
    IR_TEXT,
    IR_FREE_RESPONSE,
    IR_MULTIPLE_CHOICE,
    IR_NEW_LEVEL,
  };
  
  /**
   * TODO: comment
   */
  explicit InteractionResponse(const Backend::AttributeMap& data);
  
  /**
   * The InteractionResponse destructor is declared virtual so that the class
   * may be used polymorphically.
   */
  virtual ~InteractionResponse();
  
  /**
   * type returns the specific subclass of InteractionResponse represented by
   * this object.
   */
  virtual Type type() const = 0;
};

} // namespace PlayToLearn
