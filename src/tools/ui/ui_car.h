#ifndef IMU_GPS_UI_CAR_H
#define IMU_GPS_UI_CAR_H

#include <pangolin/gl/glvbo.h>

#include "common/eigen_types.h"

namespace imu_gps::ui {

/// The car displayed in the UI
class UiCar {
   public:
    UiCar(const Vec3f& color) : color_(color) {}

    /// Set the car's pose and reset the vertices in the GPU memory
    void SetPose(const SE3& pose);

    /// Render the car
    void Render();

   private:
    Vec3f color_;
    pangolin::GlBuffer vbo_;  // buffer data

    static std::vector<Vec3f> car_vertices_;  // Vertices of the car
};

}  // namespace imu_gps::ui

#endif
