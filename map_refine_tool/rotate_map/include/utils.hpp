
#include <math.h>

// constant define
static const double geod_a = 6378137.0;  // SemiMajorAxis
static const double geod_e2 = 0.00669437999014;  // FirstEccentricitySquard, e ^ 2

namespace utils {

struct Pose {
  double x;
  double y;
  double z;
};

struct GpsPose {
  double latitude;
  double longitude;
  double height;
};

double convertdeg2rad(const double& degree) {
  double radian;
  radian = degree * M_PI / 180;
  return radian;
}

double normalizeRad(const double& radian) {
  double norm_radian = radian;
  while (norm_radian > M_PI * 2.) norm_radian -= M_PI * 2.;
  while (norm_radian < 0.) norm_radian += M_PI * 2.;
  return norm_radian;
}

double convertrad2deg(const double& radian) {
  double degree;
  degree = radian * 180 / M_PI;
  return degree;
}

double normalizeDeg(const double& degree) {
  double norm_degree = degree;
  while (norm_degree > 360.) norm_degree -= 360.;
  while (norm_degree < 0.) norm_degree += 360.;
  return norm_degree;
}

double kappaLat(double ref_latitude, double height) {
  double kappa_lat = 0;
  double denominator = 0;
  double m = 0;

  // estimate the meridional radius
  denominator = sqrt(1 - geod_e2 * pow(sin(convertdeg2rad(ref_latitude)), 2));
  m = geod_a * (1 - geod_e2) / pow(denominator, 3);

  // Curvature for the meridian
  kappa_lat = convertrad2deg(1 / (m + height));

  return kappa_lat;
}

double kappaLon(double ref_latitude, double height) {
  double kappa_lon = 0;
  double denominator = 0;
  double n = 0;

  // estimate the normal radius
  denominator = sqrt(1 - geod_e2 * pow(sin(convertdeg2rad(ref_latitude)), 2));
  n = geod_a / denominator;

  // Curvature for the meridian
  kappa_lon =
    convertrad2deg(1 / ((n + height) * cos(convertdeg2rad(ref_latitude))));

  return kappa_lon;
}

Pose convertEnu(const GpsPose& reference, const GpsPose& gps) {
  Pose Enu;

  double kappa_lat = 0;
  double kappa_lon = 0;

  kappa_lat = kappaLat(reference.latitude, gps.height);
  kappa_lon = kappaLon(reference.latitude, gps.height);

  // return ENU coordinate point
  Enu.x = (gps.longitude - reference.longitude) / kappa_lon;
  Enu.y = (gps.latitude - reference.latitude) / kappa_lat;
  Enu.z = (gps.height - reference.height);

  return Enu;
}

// Optional<Point3d> convertUtm(const GpsPoint& reference, const GpsPoint& gps) {
//   geometry::UtmProjector projector(reference, true);
//   //* exception for GeographicLib
//   try {
//     return Optional<Point3d>(projector.forward(gps));
//   } catch (...) {
//     std::cout << "\033[031mGeographicLib Error: cannot convert ("
//               << gps.latitude() << ", " << gps.longitude()
//               << ") where the reference is (" << reference.latitude() << ", "
//               << reference.longitude() << ")\033[0m" << std::endl;
//     return Optional<Point3d>();
//   }
// }

}