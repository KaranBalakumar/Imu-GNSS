# 引入该目录下的.cmake文件
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# eigen 3
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIRS})

# sophus
find_package(Sophus REQUIRED)

# glog
find_package(Glog REQUIRED)
include_directories(${Glog_INCLUDE_DIRS})

# csparse
find_package(CSparse REQUIRED)
include_directories(${CSPARSE_INCLUDE_DIR})

# cholmod
find_package(Cholmod REQUIRED)
include_directories(${CHOLMOD_INCLUDE_DIRS})

# pcl
find_package(PCL REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})

# opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Pangolin REQUIRED)
include_directories(${Pangolin_INCLUDE_DIRS})

# yaml-cpp
find_package(yaml-cpp REQUIRED)
include_directories(${yaml-cpp_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR}/thirdparty)

set(third_party_libs
    ${rclcpp_LIBRARIES}
    ${OpenCV_LIBS}
    ${Pangolin_LIBRARIES}
    glog gflags
    ${yaml-cpp_LIBRARIES}
    yaml-cpp
    )