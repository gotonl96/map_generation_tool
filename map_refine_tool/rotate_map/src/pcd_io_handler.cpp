#include "pcd_io_handler.hpp"

pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr PcdIoHandler::readPcd(std::string file_path){
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::io::loadPCDFile<pcl::PointXYZRGB> (file_path, *cloud);
  return cloud;
}

void PcdIoHandler::savePcd(pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr save_pcd, std::string file_path){
  pcl::io::savePCDFile<pcl::PointXYZRGB>(file_path, *save_pcd);
}
  