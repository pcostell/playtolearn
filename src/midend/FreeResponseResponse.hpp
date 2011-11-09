/*
 * File: midend/FreeResponseResponse.hpp
 */

#pragma once

#include "midend/InteractionResponse.hpp"
#include <string>

namespace PlayToLearn {
namespace Midend {

//////////////////////////////////////////
// FreeResponseResponse class interface //
//////////////////////////////////////////

/**
 * TODO: comment
 */
class FreeResponseResponse : public InteractionResponse {
public:
  /**
   * The Ptr typedef allows us to refer to shared_ptr<FreeResponseResponse>
   * smart pointers as FreeResponseResponse::Ptr. A const version is provided as
   * well.
   */
  typedef boost::shared_ptr<FreeResponseResponse> Ptr;
  typedef boost::shared_ptr<const FreeResponseResponse> ConstPtr;
  
  /**
   * The kFreeResponseAttribute constant represents the name of the attribute
   * that should be paired with the corresponding 
   */
  static const std::string kFreeResponseTextAttribute;
  
  /**
   * The FreeResponseResponse constructor creates an FreeResponseResponse object
   * populated with information supplied by the specified AttributeMap.
   */
  explicit FreeResponseResponse(const Backend::AttributeMap& data);
  
  /**
   * type returns what kind of interaction this response represents. This
   * version always returns IR_FREE_RESPONSE.
   */
  Type type() const;
  
  /**
   * text returns the string which represents the question text for this free
   * response question.
   */
  const std::string& text() const;

private:
  //////////////////////
  // member variables //
  //////////////////////
  
  std::string text_;
};

////////////////////////////////////////////
// FreeResponseResponse inlined functions //
////////////////////////////////////////////

/** public */

inline InteractionResponse::Type FreeResponseResponse::type() const {
  return IR_FREE_RESPONSE;
}

inline const std::string& FreeResponseResponse::text() const {
  return text_;
}

} // namespace Midend
} // namespace PlayToLearn
