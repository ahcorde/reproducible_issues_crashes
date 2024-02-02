cmake_minimum_required(VERSION 3.5)
project(geometry2_issues)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2_ros REQUIRED)

add_executable(geometry2_issues1
    src/main.cpp
)

target_link_libraries(geometry2_issues1
    rclcpp::rclcpp
    tf2_ros::tf2_ros
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

install(TARGETS
    geometry2_issues1
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
