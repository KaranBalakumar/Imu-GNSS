#ifndef MAPPING_ODOM_H
#define MAPPING_ODOM_H

namespace imu_gps {

struct Odom {
    Odom() {}
    Odom(double timestamp, double left_pulse, double right_pulse)
        : timestamp_(timestamp), left_pulse_(left_pulse), right_pulse_(right_pulse) {}

    double timestamp_ = 0.0;
    double left_pulse_ = 0.0;  // Number of pulses per unit time for the left and right wheels
    double right_pulse_ = 0.0;
};

}  // namespace imu_gps

#endif  // MAPPING_ODOM_H
