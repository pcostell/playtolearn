/*
 * File: backend/Engine.cpp
 */

#include "util/Constants.hpp"
#include "util/ErrorTypes.hpp"
#include "backend/Engine.hpp"
#include <fstream>
#include <sstream>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>

using namespace std;

namespace PlayToLearn {
namespace Backend {

///////////////////////////////////////////////////
// Engine member function implementation details //
///////////////////////////////////////////////////

/** public */

void Engine::load_level(int level_index) {
  // Locate the directory with the level's information:
  stringstream level_name_ss;
  level_name_ss << Util::kLevelDirectoryPrefix << level_index << "/";
  string level_name = level_name_ss.str();
  
  // Load data:
  load_state_machine(level_name);
  load_transition_fns(level_name);
}

Frontend::InteractionResponse::Ptr Engine::register_interaction(Frontend::Interaction::Ptr interaction) {
  // Check if the object has an interaction available for this state:
  const State& current_state = state_machine_.current_state();
  if (!current_state.object_exists(interaction->object_id()))
    return Frontend::InteractionResponse::Ptr();
  
  // This is the transition function associated with this object/state pair:
  TransitionFn::ID fn_id = current_state.transition_fn_id(interaction->object_id());
  
  // Check if the frontend is simply asking for the data needed to set up an
  // interaction:
  if (interaction->requesting_data())
    return Frontend::InteractionResponse::create(transition_data_.find(fn_id)->second);
  
  // Move to the new state:
  const TransitionFn& transition_fn = state_machine_.transition_fn(fn_id);
  State::ID new_state_id = transition_fn.next_state(interaction->attribute_map(), global_state_);
  state_machine_.set_current_state(new_state_id);
  
  // Return the proper interaction response:
  const State& new_state = state_machine_.current_state();
  if (!interaction->requesting_data() || !new_state.object_exists(interaction->object_id()))
    return Frontend::InteractionResponse::Ptr();
  
  fn_id = new_state.transition_fn_id(interaction->object_id());
  return Frontend::InteractionResponse::create(transition_data_.find(fn_id)->second);
}

/** private */

/*
 * load_state_machine uses Boost serialization to load the StateMachine data for
 * the level with the specified name.
 */
void Engine::load_state_machine(const string& level_name) {
  // Open the file with the level's information:
  stringstream file_name_ss;
  file_name_ss << level_name << Util::kLevelStateMachineFile;
  ifstream input_file(file_name_ss.str().c_str());
  
  // Read the XML data into the StateMachine object:
  boost::archive::xml_iarchive input_archive(input_file);
  input_archive >> boost::serialization::make_nvp("StateMachine", state_machine_);
}

/*
 * load_transition_fns loads the scripting data for all of the TransitionFn
 * objects associated with the level with the specified name.
 */
void Engine::load_transition_fns(const string& level_name) {
  // Read the transition function data:
  stringstream file_name_ss;
  file_name_ss << level_name << Util::kLevelTransitionFnFile;
  ifstream input_file(file_name_ss.str().c_str());
  
  // Determine the name of the transition function script directory:
  stringstream script_directory_ss;
  script_directory_ss << level_name << Util::kLevelTransitionFnScriptDirectory;
  string script_directory = script_directory_ss.str();
  
  // Process each transition function:
  int transition_fn_id;
  string line;
  while (getline(input_file, line)) {
    // Parse out the transition function's ID:
    size_t split_index = line.find(' ');
    stringstream converter(line.substr(0, split_index));
    converter >> transition_fn_id;
    
    // Parse out the script itself:
    string script_type = line.substr(split_index + 1);
    stringstream script_name_ss;
    script_name_ss << script_directory << transition_fn_id << '.' << script_type;
    string script_name = script_name_ss.str();
    
    if (script_type == Util::kPythonExtension) {
      load_python_transition_fn_script(transition_fn_id, script_name);
    } else {
      throw Util::InvalidScriptTypeError(script_type);
    }
  }
}

/*
 * load_python_transition_fn_script reads the file for a specific transition
 * function script written in Python and assigns it to the appropriate
 * TransitionFn object.
 */
void Engine::load_python_transition_fn_script(int transition_fn_id, const string& script_name) {
  // Read the individual transition function script data:
  ifstream input_file(script_name.c_str());
  if (!input_file.is_open())
    throw Util::MissingScriptError(script_name);
  
  string line, code;
  while (getline(input_file, line)) {
    code += line;
    code += '\n';
  }
  
  TransitionFn& fn = state_machine_.transition_fn(TransitionFn::ID(transition_fn_id));
  fn.set_python_function(code);
}

} // namespace Backend
} // namespace PlayToLearn
