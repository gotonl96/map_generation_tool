#include "map_transformator.hpp"

PcdType::Ptr MapTransformator::transformateMap(PcdType::ConstPtr input, Translation t, Rotation r){
  Eigen::Affine3d translation = Eigen::Affine3d::Identity();
  translation.translation() << t.x, t.y, t.z;
  translation.rotate(Eigen::AngleAxisd(r.yaw, Eigen::Vector3d::UnitZ()));
  translation.rotate(Eigen::AngleAxisd(r.pitch, Eigen::Vector3d::UnitY()));
  translation.rotate(Eigen::AngleAxisd(r.roll, Eigen::Vector3d::UnitX()));

  PcdType::Ptr convert (new PcdType);
  pcl::transformPointCloud(*input, *convert, translation);

  return convert;
}
