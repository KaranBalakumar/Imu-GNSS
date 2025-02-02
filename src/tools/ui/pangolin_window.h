#ifndef IMU_GPS_UI_PANGOLIN_WINDOW_H
#define IMU_GPS_UI_PANGOLIN_WINDOW_H

#include "common/eigen_types.h"
#include "common/gnss.h"
#include "common/nav_state.h"

#include <map>
#include <memory>

namespace imu_gps::ui {

class PangolinWindowImpl;

/**
 * @note This class does not directly involve any OpenGL or Pangolin operations, 
 *       and should delegate these tasks to PangolinWindowImpl.
 */
class PangolinWindow {
   public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    PangolinWindow();
    ~PangolinWindow();

    /// @brief Initializes the window and starts the render thread in the background.
    /// @note Initialization unrelated to OpenGL/Pangolin should be handled here;
    ///       OpenGL/Pangolin-related tasks should be placed in PangolinWindowImpl::Init.
    bool Init();

    /// Update the Kalman filter state
    void UpdateNavState(const NavStated& state);

    /// Update the GPS positioning results
    void UpdateGps(const GNSS& gps);

    /// Wait for the display thread to finish and release resources
    void Quit();

    /// Check if the user has exited the UI
    bool ShouldQuit();

   private:
    std::shared_ptr<PangolinWindowImpl> impl_ = nullptr;
};
}  // namespace imu_gps::ui

#endif
