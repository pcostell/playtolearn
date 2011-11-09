#define BOOST_TEST_MODULE AttributeMap test
#include <boost/test/unit_test.hpp>

#include <string>
#include <map>

#include "backend/AttributeMap.hpp"

#include <csignal>

using namespace std;
using namespace PlayToLearn::Backend;

BOOST_AUTO_TEST_CASE( normal_use_test ) {
  AttributeMap m;

  m.set_value("key_string", "value");
  m.set_value("key_int", 32);

  BOOST_CHECK_EQUAL(m.value<string>("key_string"), "value");
  BOOST_CHECK_EQUAL(m.value<int>("key_int"), 32);
}

BOOST_AUTO_TEST_CASE( bad_lookup ) {
  AttributeMap m;
  m.set_value("key", "value");

  BOOST_CHECK(m.contains("key"));

  BOOST_CHECK(!m.contains("key2"));

  // hmm, can't check for assertions
  //BOOST_REQUIRE_THROW(m.value<string>("key2"), boost::execution_exception);
}