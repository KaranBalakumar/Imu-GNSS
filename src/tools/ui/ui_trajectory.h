#ifndef IMU_GPS_UI_TRAJECTORY_H
#define IMU_GPS_UI_TRAJECTORY_H

#include "common/eigen_types.h"

#include <pangolin/gl/glvbo.h>

namespace imu_gps::ui {

/// Trajectory drawing in the UI
class UiTrajectory {
   public:
    UiTrajectory(const Vec3f& color) : color_(color) { pos_.reserve(max_size_); }

    /// Add a trajectory point
    void AddPt(const SE3& pose);

    /// Render the trajectory
    void Render();

    /// Clear the trajectory data
    void Clear() {
        pos_.clear();
        pos_.reserve(max_size_);
        vbo_.Free();
    }

   private:
    int max_size_ = 1e6;           // Maximum number of points recorded
    std::vector<Vec3f> pos_;       // Trajectory data
    Vec3f color_ = Vec3f::Zero();  // Color for the trajectory
    pangolin::GlBuffer vbo_;       // GPU vertex buffer information
};

}  // namespace imu_gps::ui

#endif  // IMU_GPS_UI_TRAJECTORY_H
