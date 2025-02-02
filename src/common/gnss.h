#ifndef IMU_GPS_GNSS_H
#define IMU_GPS_GNSS_H

#include "eigen_types.h"
#include <memory>

namespace imu_gps {

/// GNSS status flag information
/// Usually provided by GNSS manufacturers, here using the status flags provided by Qianxun
enum class GpsStatusType {
    GNSS_FLOAT_SOLUTION = 5,         // Float solution (cm to dm level)
    GNSS_FIXED_SOLUTION = 4,         // Fixed solution (cm level)
    GNSS_PSEUDO_SOLUTION = 2,        // Pseudo-range differential solution (dm level)
    GNSS_SINGLE_POINT_SOLUTION = 1,  // Single point solution (10m level)
    GNSS_NOT_EXIST = 0,              // No GPS signal
    GNSS_OTHER = -1,                 // Other
};

/// UTM coordinates
struct UTMCoordinate {
    UTMCoordinate() = default;
    explicit UTMCoordinate(int zone, const Vec2d& xy = Vec2d::Zero(), bool north = true)
        : zone_(zone), xy_(xy), north_(north) {}

    int zone_ = 0;              // UTM zone
    Vec2d xy_ = Vec2d::Zero();  // UTM xy coordinates
    double z_ = 0;              // z height (directly from GPS)
    bool north_ = true;         // Whether in the northern hemisphere
};

/// A structure representing a GNSS reading
struct GNSS {
    GNSS() = default;
    GNSS(double unix_time, int status, const Vec3d& lat_lon_alt, double heading, bool heading_valid)
        : unix_time_(unix_time), lat_lon_alt_(lat_lon_alt), heading_(heading), heading_valid_(heading_valid) {
        status_ = GpsStatusType(status);
    }

    double unix_time_ = 0;                                  // Unix time
    GpsStatusType status_ = GpsStatusType::GNSS_NOT_EXIST;  // GNSS status flag
    Vec3d lat_lon_alt_ = Vec3d::Zero();                     // Latitude, longitude, altitude; the first two in degrees
    double heading_ = 0.0;                                  // Heading from dual-antenna, in degrees
    bool heading_valid_ = false;                            // Whether the heading is valid

    UTMCoordinate utm_;       // UTM coordinates (including zone and other info)
    bool utm_valid_ = false;  // Whether the UTM coordinates have been computed (false if the lat/lon values are incorrect)

    SE3 utm_pose_;  // 6DoF Pose for post-processing
};

}  // namespace imu_gps

using GNSSPtr = std::shared_ptr<imu_gps::GNSS>;

#endif  // IMU_GPS_GNSS_H
