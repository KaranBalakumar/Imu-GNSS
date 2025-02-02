#ifndef IMU_GPS_NAV_STATE_H
#define IMU_GPS_NAV_STATE_H

#include <sophus/so3.hpp>
#include "common/eigen_types.h"

namespace imu_gps {

/**
 * Navigation state variables
 * @tparam T    Scalar type
 *
 * This is a wrapped class. Some programs use this structure, while other programs use individual pvq components, both of which are valid.
 */
template <typename T>
struct NavState {
    using Vec3 = Eigen::Matrix<T, 3, 1>;
    using SO3 = Sophus::SO3<T>;

    NavState() = default;

    // from time, R, p, v, bg, ba
    explicit NavState(double time, const SO3& R = SO3(), const Vec3& t = Vec3::Zero(), const Vec3& v = Vec3::Zero(),
                      const Vec3& bg = Vec3::Zero(), const Vec3& ba = Vec3::Zero())
        : timestamp_(time), R_(R), p_(t), v_(v), bg_(bg), ba_(ba) {}

    // from pose and vel
    NavState(double time, const SE3& pose, const Vec3& vel = Vec3::Zero())
        : timestamp_(time), R_(pose.so3()), p_(pose.translation()), v_(vel) {}

    /// Convert to Sophus
    Sophus::SE3<T> GetSE3() const { return SE3(R_, p_); }

    friend std::ostream& operator<<(std::ostream& os, const NavState<T>& s) {
        os << "p: " << s.p_.transpose() << ", v: " << s.v_.transpose()
           << ", q: " << s.R_.unit_quaternion().coeffs().transpose() << ", bg: " << s.bg_.transpose()
           << ", ba: " << s.ba_.transpose();
        return os;
    }

    double timestamp_ = 0;    // Time
    SO3 R_;                   // Rotation
    Vec3 p_ = Vec3::Zero();   // Translation
    Vec3 v_ = Vec3::Zero();   // Velocity
    Vec3 bg_ = Vec3::Zero();  // Gyro bias
    Vec3 ba_ = Vec3::Zero();  // Accelerometer bias
};

using NavStated = NavState<double>;
using NavStatef = NavState<float>;

}  // namespace imu_gps

#endif
