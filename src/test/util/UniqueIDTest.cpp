#define BOOST_TEST_MODULE UniqueID test
#include <boost/test/unit_test.hpp>

#include <string>
#include <map>
#include "util/UniqueID.hpp"
#include "util/Constants.hpp"

class MyType1 {};
class MyType2 {};
class MyType3 {};

using namespace PlayToLearn::Util;

BOOST_AUTO_TEST_CASE( normal_use_test ) {
  UniqueID<MyType1> uid(UniqueID<MyType1>::create());
  UniqueID<MyType1> uid2(UniqueID<MyType1>::create());

  BOOST_CHECK(uid != uid2);
}

/* Test that two different type IDs don't affect each other. */
BOOST_AUTO_TEST_CASE( different_type_ids ) {
  UniqueID<MyType2> uid(UniqueID<MyType2>::create());
  UniqueID<MyType3> uid2(UniqueID<MyType3>::create());

  BOOST_CHECK_EQUAL(uid.value(), uid2.value());
}

BOOST_AUTO_TEST_CASE( default_value_invalid ) {
  UniqueID<MyType1> uid;

  BOOST_CHECK_EQUAL(uid.value(), kInvalidID);
}