
#include <iostream>

#include "map_transformator.hpp"
#include "parameter_manager.hpp"
#include "pcd_io_handler.hpp"

int main() {
  //* generate objects
  ParameterManager parameter_manager(
    "/home/a/workspace/personal_project/localization/package/src/map_tool/"
    "map_refine_tool/rotate_map/config/config.yaml");
  PcdIoHandler pcd_io_handler;
  MapTransformator map_transformator;

  //* read param
  auto t = Translation(parameter_manager.getParam<double>("x"),
              parameter_manager.getParam<double>("y"),
              parameter_manager.getParam<double>("z"));
  auto r = Rotation(parameter_manager.getParam<double>("roll") * M_PI / 180.,
           parameter_manager.getParam<double>("pitch") * M_PI / 180.,
           (parameter_manager.getParam<double>("yaw")) * M_PI / 180.);

  //* convert map
  auto map =
    pcd_io_handler.readPcd(parameter_manager.getParam<std::string>("input_file_path"));
  auto convert_map = map_transformator.transformateMap(map, t, r);

  pcd_io_handler.savePcd(convert_map, parameter_manager.getParam<std::string>("output_file_path"));

  std::cout << "succecss map convert: " << parameter_manager.getParam<std::string>("output_file_path") << "\n";

  return 0;
}