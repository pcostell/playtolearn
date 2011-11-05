/*
 * File: InteractionResponse.hpp
 */

#pragma once

#include "../backend/AttributeMap.hpp"
#include <string>

namespace PlayToLearn {

/////////////////////////////////////////
// InteractionResponse class interface //
/////////////////////////////////////////

/**
 * TODO: comment
 */
class InteractionResponse {
public:
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
   * TODO: comment
   */
  virtual ~InteractionResponse();
  
  /**
   * TODO: comment
   */
  virtual Type type() const = 0;
};

} // namespace PlayToLearn
