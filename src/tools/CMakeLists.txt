add_library(${PROJECT_NAME}.tools
        ui/pangolin_window.cc
        ui/pangolin_window_impl.cc
        ui/ui_car.cc
        ui/ui_trajectory.cc
        )

target_link_libraries(${PROJECT_NAME}.tools
        ${third_party_libs}
        )
