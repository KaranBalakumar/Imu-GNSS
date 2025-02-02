#include "ui_car.h"

namespace imu_gps::ui {

std::vector<Vec3f> UiCar::car_vertices_ = {
    // clang-format off
     { 0, 0, 0}, { 5, 0, 0},
     { 0, 0, 0}, { 0, 5, 0},
     { 0, 0, 0}, { 0, 0, 5},
    // clang-format on
};

void UiCar::SetPose(const SE3& pose) {
    std::vector<Vec3f> pts;
    for (auto& p : car_vertices_) {
        pts.emplace_back(p);
    }

    // Convert to world coordinate system
    auto pose_f = pose.cast<float>();
    for (auto& pt : pts) {
        pt = pose_f * pt;
    }

    /// Upload to GPU memory
    vbo_ = pangolin::GlBuffer(pangolin::GlArrayBuffer, pts);
}

void UiCar::Render() {
    if (vbo_.IsValid()) {
        glColor3f(color_[0], color_[1], color_[2]);
        glLineWidth(3.0);
        pangolin::RenderVbo(vbo_, GL_LINES);
        glLineWidth(1.0);
    }
}

}  // namespace imu_gps::ui
