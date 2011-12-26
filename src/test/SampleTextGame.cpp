/*
 * File: test/SampleTextGame.cpp
 */

#include <string>
#include <map>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>

#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/map.hpp>
#include <boost/test/unit_test.hpp>

#include "util/Constants.hpp"
#include "backend/AttributeMap.hpp"
#include "backend/StateMachine.hpp"
#include "backend/State.hpp"
#include "backend/Object.hpp"
#include "backend/TransitionFn.hpp"
#include "frontend/Interactions.hpp"
#include "frontend/InteractionPrompts.hpp"

using namespace std;
namespace Util = PlayToLearn::Util;
namespace Backend = PlayToLearn::Backend;
namespace Frontend = PlayToLearn::Frontend;

/** free function declarations */

void WriteScript(const string& level_name, Backend::TransitionFn::ID transition_fn_id, const string& code);

/** program entry point */

int main(int argc, char** argv) {
  map<Backend::TransitionFn::ID, Backend::AttributeMap> transition_fn_data;
  Backend::StateMachine sm;
  Backend::State state_0(Backend::State::ID(0));
  Backend::State state_1(Backend::State::ID(1));
  Backend::State state_2(Backend::State::ID(2));
  Backend::TransitionFn tfn_0(Backend::TransitionFn::ID(0));
  Backend::TransitionFn tfn_1(Backend::TransitionFn::ID(1));
  
  state_0.insert_object(Util::kDefaultObject, tfn_0.id());
  sm.add_state(state_0);
  
  state_1.insert_object(Util::kDefaultObject, tfn_1.id());
  sm.add_state(state_1);
  
  sm.add_state(state_2);
  
  // TransitionFn #0
  stringstream python_ss_0;
  python_ss_0 << "def " << Util::kTransitionFnScriptFunctionName << "0(am, gs):\n"
              << "  if am['" << Util::kFreeResponseAnswerAttribute << "'] == 'red':\n"
              << "    gs['" << Util::kInteractionResponseText << "'] = 'Correct! You chose red!'\n"
              << "    return 0\n"
              << "  else:\n"
              << "    gs['" << Util::kInteractionResponseText << "'] = 'Wrong color!'\n"
              << "    return 1\n";
  
  tfn_0.add_state(state_1.id());
  tfn_0.add_state(state_2.id());
  sm.add_transition_fn(tfn_0);
  
  Backend::AttributeMap tfn_data_0;
  tfn_data_0.set_value(Util::kInteractionPromptTypeAttribute, Util::kFreeResponsePromptTypeValue);
  tfn_data_0.set_value(Util::kTextAttribute, "What is your favorite color? ");
  transition_fn_data.insert(make_pair(tfn_0.id(), tfn_data_0));
  
  // TransitionFn #1
  stringstream python_ss_1;
  python_ss_1 << "def " << Util::kTransitionFnScriptFunctionName << "1(am, gs):\n"
              << "  if am['" << Util::kMCAnswerIndexAttribute << "'] == '0':\n"
              << "    gs['" << Util::kInteractionResponseText << "'] = 'Not fat enough!'\n"
              << "  else:\n"
              << "    gs['" << Util::kInteractionResponseText << "'] = 'Correct again!'\n"
              << "  return 0\n";
  
  tfn_1.add_state(state_2.id());
  sm.add_transition_fn(tfn_1);
  
  Backend::AttributeMap tfn_data_1;
  tfn_data_1.set_value(Util::kInteractionPromptTypeAttribute, Util::kMultipleChoicePromptTypeValue);
  tfn_data_1.set_value(Util::kTextAttribute, "How fat is Patrick?");
  tfn_data_1.set_value(Util::kNumMCChoicesAttribute, 2);
  tfn_data_1.set_value(Util::kMCChoiceAttribute + "0", "fat");
  tfn_data_1.set_value(Util::kMCChoiceAttribute + "1", "extremely fat");
  transition_fn_data.insert(make_pair(tfn_1.id(), tfn_data_1));
  
  // File output:
  stringstream level_name_ss;
  level_name_ss << Util::kLevelDirectoryPrefix << "0/";
  string level_name = level_name_ss.str();
  
  WriteScript(level_name, tfn_0.id(), python_ss_0.str());
  WriteScript(level_name, tfn_1.id(), python_ss_1.str());
  
  stringstream tfn_file_name_ss;
  tfn_file_name_ss << level_name << Util::kLevelTransitionFnFile;
  ofstream tfn_output_file(tfn_file_name_ss.str().c_str());
  
  tfn_output_file << tfn_0.id() << " py\n";
  tfn_output_file << tfn_1.id() << " py\n";
  
  stringstream sm_file_name_ss;
  sm_file_name_ss << level_name << Util::kLevelStateMachineFile;
  ofstream sm_output_file(sm_file_name_ss.str().c_str());
  boost::archive::xml_oarchive sm_output_archive(sm_output_file);
  sm_output_archive << boost::serialization::make_nvp("StateMachine", sm);
  
  stringstream tfn_data_file_name_ss;
  tfn_data_file_name_ss << level_name << Util::kLevelTransitionDataFile;
  ofstream tfn_data_output_file(tfn_data_file_name_ss.str().c_str());
  boost::archive::xml_oarchive tfn_data_output_archive(tfn_data_output_file);
  tfn_data_output_archive << boost::serialization::make_nvp("transition_data", transition_fn_data);
  
  return 0;
}

void WriteScript(const string& level_name, Backend::TransitionFn::ID transition_fn_id, const string& code) {
  stringstream file_name_ss;
  file_name_ss << level_name << Util::kLevelTransitionFnScriptDirectory << transition_fn_id << ".py";
  ofstream output_file(file_name_ss.str().c_str());
  output_file << code;
}
