# Imu-GNSS Sensor Fusion
This repository Imu and GNSS based combined navigation using Iterative Error State Kalman Filter.


# How To Run
1. `process_gnss`: sparse (10hz) global prior observation 
    - After executing it, you can fine the result file at `data/gnss_output.txt`
2. `run_imu_integration`: imu only propagtations with no any measurements 
    - It would diverge so fast. 
3. `./run_eskf_gins --with_odom=false`: SE3-like loss from GNSS only 
    - It would generate a reasonable continous (100hz) poses more denser and smoother than the raw GNSS measurement.
    - However, you can see some diverging moments when GNSS signals are off. 
4. `./run_eskf_gins --with_odom=true`: SE3-like loss + Wheel-based Velocity loss 
    - This shows the best performance. It also would fix the failure points of the above experiment 3.

# TODO
1. Use Pre-integration and Graph Optimizaiton instead of Kalman filter.
2. Use this code as a base for Lidar-Inertial-GNSS-Wheel Odometry using IESKF and a Graph Optimization counterpart to it.
