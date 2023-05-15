
//* std header
#include <memory>

//* pcl header
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/common/transforms.h>

using PcdType = pcl::PointCloud<pcl::PointXYZRGB>;

struct Translation{
  double x;
  double y;
  double z;

  Translation() : x(0.), y(0.), z(0.) {}
  Translation(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
};

struct Rotation{
  double roll; //* [rad]
  double pitch; //* [rad]
  double yaw; //* [rad]

  Rotation() : roll(0.0), pitch(0.0), yaw(0.0) {}
  Rotation(double _roll, double _pitch, double _yaw) : roll(_roll), pitch(_pitch), yaw(_yaw) {}
  Rotation(double qw, double qx, double qy, double qz) {
    roll = atan2(2 * (qw * qx + qy * qz),
                           1 - 2 * (pow(qx, 2) + pow(qy, 2)));
    pitch = asin(2 * (qw * qy - qz * qx));

    yaw = atan2(2 * (qw * qz + qx * qy),
                           1 - 2 * (pow(qy, 2) + pow(qz, 2)));
  }
};

class MapTransformator {

public:
  MapTransformator() {}
  ~MapTransformator() {}

public:

  PcdType::Ptr transformateMap(PcdType::ConstPtr input, Translation t, Rotation r);

};