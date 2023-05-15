
//* stl header
#include <iostream>
#include <vector>

//* lib header
#include <yaml-cpp/yaml.h>

class ParameterManager {

public:
  explicit ParameterManager(std::string parameter_file_path) {
    try{
      node_ = YAML::LoadFile(parameter_file_path);
    } catch (YAML::Exception &e) {
      std::cout << "Failed to load file: {}";
      std::cout << e.what() << "\n";
    }
  };
  ~ParameterManager() {};

public:

  template<typename DataType> 
  DataType getParam(std::string parameter_name){
    DataType param;

    try {
      param = node_[parameter_name].as<DataType>();
    } catch (const YAML::Exception& e) {
      std::cout << "paramter not vaild: " << e.what() << "\n";
    }

    return param;
  }

private:
  YAML::Node node_;
};