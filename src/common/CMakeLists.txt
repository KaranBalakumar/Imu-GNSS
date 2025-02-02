add_library(${PROJECT_NAME}.common
        io_utils.cc
        timer/timer.cc
        global_flags.cc
        )

target_link_libraries(${PROJECT_NAME}.common
        ${PROJECT_NAME}.tools
        )
