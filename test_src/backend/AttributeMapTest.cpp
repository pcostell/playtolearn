#define BOOST_TEST_MODULE AttributeMap test

#include "util/ErrorTypes.hpp"
#include "backend/AttributeMap.hpp"
#include <csignal>
#include <string>
#include <map>
#include <fstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/test/unit_test.hpp>

using namespace std;
using PlayToLearn::Util::MissingAttributeError;
using PlayToLearn::Backend::AttributeMap;

BOOST_AUTO_TEST_CASE(normal_use_test) {
  AttributeMap m;
  m.set_value("key_string", "value");
  m.set_value("key_int", 32);

  BOOST_CHECK_EQUAL(m.value<string>("key_string"), "value");
  BOOST_CHECK_EQUAL(m.value<int>("key_int"), 32);
}

BOOST_AUTO_TEST_CASE(bad_lookup) {
  AttributeMap m;
  m.set_value("key", "value");

  BOOST_CHECK(m.contains("key"));

  BOOST_CHECK(!m.contains("key2"));

  BOOST_CHECK_THROW(m.value<string>("key2"), MissingAttributeError);
}

void save(const AttributeMap& m) {
  ofstream out("test.xml");
  boost::archive::xml_oarchive oa(out);
  oa << boost::serialization::make_nvp("AttributeMap", m);
}

void restore(AttributeMap& m) {
  ifstream in("test.xml");
  boost::archive::xml_iarchive ia(in);
  ia >> boost::serialization::make_nvp("AttributeMap", m);
}

void save_text(const AttributeMap& m) {
  ofstream out("test.txt");
  boost::archive::text_oarchive oa(out);
  oa << boost::serialization::make_nvp("AttributeMap", m);
}

void restore_text(AttributeMap& m) {
  ifstream in("test.txt");
  boost::archive::text_iarchive ia(in);
  ia >> boost::serialization::make_nvp("AttributeMap", m);
}

BOOST_AUTO_TEST_CASE(input_output) {
  AttributeMap m1, m2;
  m1.set_value("key", "value");
  save(m1);
  restore(m2);

  BOOST_CHECK(m2.contains("key"));
}

BOOST_AUTO_TEST_CASE(io_xml_escape_chars) {
  AttributeMap m1, m2;
  m1.set_value("key<", "value>");
  save(m1);
  restore(m2);

  BOOST_CHECK(m2.contains("key<"));
  BOOST_CHECK_EQUAL(m2.value<string>("key<"), "value>");
}

BOOST_AUTO_TEST_CASE(io_xml_problem_chars) {
  string problem_key = "<>\\/-=\n_";
  string problem_value = "<_\n=-/\\>";
  AttributeMap m1, m2;
  m1.set_value(problem_key, problem_value);
  save(m1);
  restore(m2);
  
  BOOST_CHECK(m2.contains(problem_key));
  BOOST_CHECK_EQUAL(m2.value<string>(problem_key), problem_value);
}

BOOST_AUTO_TEST_CASE(io_text_archive) {
  AttributeMap m1, m2;
  m1.set_value("key", "value");
  save_text(m1);
  restore_text(m2);

  BOOST_CHECK(m2.contains("key"));
  BOOST_CHECK_EQUAL(m2.value<string>("key"), "value");
}
