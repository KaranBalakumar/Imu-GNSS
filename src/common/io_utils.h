#ifndef IMU_GPS_IO_UTILS_H
#define IMU_GPS_IO_UTILS_H

#include <fstream>
#include <functional>
#include <utility>
#include <map>

#include "common/global_flags.h"
#include "common/gnss.h"
#include "common/imu.h"
#include "common/math_utils.h"
#include "common/odom.h"

#include "utm_convert.h"

namespace imu_gps {

/**
 * Reads the data text file provided by this book and calls the callback function.
 * The data text file mainly provides IMU/Odom/GNSS readings.
 */
class TxtIO {
public:
    TxtIO(const std::string &file_path) : fin(file_path) {}

    /// Define callback functions
    using IMUProcessFuncType = std::function<void(const IMU &)>;
    using OdomProcessFuncType = std::function<void(const Odom &)>;
    using GNSSProcessFuncType = std::function<void(const GNSS &)>;

    TxtIO &SetIMUProcessFunc(IMUProcessFuncType imu_proc) {
        imu_proc_ = std::move(imu_proc);
        return *this;
    }

    TxtIO &SetOdomProcessFunc(OdomProcessFuncType odom_proc) {
        odom_proc_ = std::move(odom_proc);
        return *this;
    }

    TxtIO &SetGNSSProcessFunc(GNSSProcessFuncType gnss_proc) {
        gnss_proc_ = std::move(gnss_proc);
        return *this;
    }

    // Traverse the file content and call the callback functions
    void Go();

private:
    std::ifstream fin;
    IMUProcessFuncType imu_proc_;
    OdomProcessFuncType odom_proc_;
    GNSSProcessFuncType gnss_proc_;
};

}  // namespace imu_gps

#endif  // IMU_GPS_IO_UTILS_H
