#ifndef FUSION_UI_PANGOLIN_WINDOW_IMPL_H
#define FUSION_UI_PANGOLIN_WINDOW_IMPL_H

// Include pangolin
#include <pangolin/pangolin.h>

#include "tools/ui/pangolin_window.h"
#include "tools/ui/ui_car.h"
#include "tools/ui/ui_trajectory.h"

#include <atomic>
#include <mutex>
#include <string>
#include <thread>

namespace imu_gps::ui {

struct UiFrame;

/**
 * Pangolin window implementation for displaying information.
 */
class PangolinWindowImpl {
   public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    PangolinWindowImpl() = default;
    ~PangolinWindowImpl() = default;

    PangolinWindowImpl(const PangolinWindowImpl &) = delete;
    PangolinWindowImpl &operator=(const PangolinWindowImpl &) = delete;
    PangolinWindowImpl(PangolinWindowImpl &&) = delete;
    PangolinWindowImpl &operator=(PangolinWindowImpl &&) = delete;

    /// Initialize, create various point clouds and car entities
    bool Init();

    /// De-initialize
    bool DeInit();

    /// Render all information
    void Render();

   public:
    /// Background rendering thread
    std::thread render_thread_;

    /// Some auxiliary locks and atomic variables
    std::mutex mtx_nav_state_;
    std::mutex mtx_gps_pose_;

    std::atomic<bool> exit_flag_;

    std::atomic<bool> kf_result_need_update_;
    std::atomic<bool> gps_need_update_;

    /// GPS pose
    SE3 gps_pose_;

    SE3 current_pose_;                 // Current pose

    /// Filter state
    SE3 pose_;
    Vec3d vel_;
    Vec3d bias_acc_;
    Vec3d bias_gyr_;
    Vec3d grav_;

    //////////////////////////////// Below are related to rendering ///////////////////////////
   private:
    /// Create OpenGL Buffers
    void AllocateBuffer();
    void ReleaseBuffer();

    void CreateDisplayLayout();

    void DrawAll();  // Plot: Draw the localization window

    /// Render point clouds, call various Update functions
    bool UpdateGps();
    bool UpdateState();

    void RenderLabels();

   private:
    /// Window layout-related parameters
    int win_width_ = 1920;
    int win_height_ = 1080;
    static constexpr float cam_focus_ = 5000;
    static constexpr float cam_z_near_ = 1.0;
    static constexpr float cam_z_far_ = 1e10;
    static constexpr int menu_width_ = 200;
    const std::string win_name_ = "imu_gps.UI";
    const std::string dis_main_name_ = "main";
    const std::string dis_3d_name_ = "Cam 3D";
    const std::string dis_3d_main_name_ = "Cam 3D Main";  // main
    const std::string dis_plot_name_ = "Plot";
    const std::string dis_imgs_name = "Images";

    bool following_loc_ = true;  // Whether the camera tracks the localization result

    // Text rendering
    pangolin::GlText gltext_label_global_;

    // Camera rendering state
    pangolin::OpenGlRenderState s_cam_main_;

    /// Cloud rendering (e.g., car object)
    ui::UiCar car_{Vec3f(0.2, 0.2, 0.8)};                                      // White car

    // Trajectory
    std::shared_ptr<ui::UiTrajectory> traj_gps_ui_ = nullptr;
    std::shared_ptr<ui::UiTrajectory> poses_ui = nullptr;

    // Filter state-related Data logger object
    pangolin::DataLog log_vel_;           // Velocity in odom frame
    pangolin::DataLog log_vel_baselink_;  // Velocity in baselink frame
    pangolin::DataLog log_bias_acc_;      //
    pangolin::DataLog log_bias_gyr_;      //

    std::unique_ptr<pangolin::Plotter> plotter_vel_ = nullptr;
    std::unique_ptr<pangolin::Plotter> plotter_vel_baselink_ = nullptr;
    std::unique_ptr<pangolin::Plotter> plotter_bias_acc_ = nullptr;
    std::unique_ptr<pangolin::Plotter> plotter_bias_gyr_ = nullptr;
};

}  // namespace imu_gps::ui

#endif
