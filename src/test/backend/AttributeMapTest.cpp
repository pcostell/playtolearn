#define BOOST_TEST_MODULE AttributeMap test

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>

#include <boost/test/unit_test.hpp>


#include <string>
#include <map>

#include <fstream>

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

void save(const AttributeMap & m, const string & name) {
  ofstream out("test.xml");
  boost::archive::xml_oarchive oa(out);
  oa << boost::serialization::make_nvp("AttributeMap", m);
}

void restore(AttributeMap & m, const string & name) {
  ifstream in("test.xml");
  boost::archive::xml_iarchive ia(in);
  ia >> boost::serialization::make_nvp("AttributeMap", m);
}

BOOST_AUTO_TEST_CASE( input_output ) {
  AttributeMap m, m2;
  m.set_value("key", "value");
  save(m, "object1");
  restore(m2, "object1");

  BOOST_CHECK(m2.contains("key"));
}

BOOST_AUTO_TEST_CASE( io_xml_escape_chars ) {
  AttributeMap m, m2;
  m.set_value("key<", "value>");
  save(m, "object1");
  restore(m2, "object1");

  BOOST_CHECK(m2.contains("key<"));
  BOOST_CHECK_EQUAL(m2.value<string>("key<"), "value>");
}