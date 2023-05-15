
//* stl header
#include <string>

//* pcl header
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

class PcdIoHandler {

public:
  PcdIoHandler() {}
  ~PcdIoHandler() {}

public:
  pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr readPcd(std::string file_path);

  void savePcd(pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr save_pcd, std::string file_path);
  
};