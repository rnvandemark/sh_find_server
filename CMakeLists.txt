cmake_minimum_required(VERSION 3.5)
project(sh_find_server)

find_package(rclcpp REQUIRED)
find_package(sh_find_common REQUIRED)

include_directories(include)

add_executable(find_server src/find_server.cpp)
ament_target_dependencies(find_server
    rclcpp
    sh_find_common
)

install(
    DIRECTORY include/
    DESTINATION include
)

install(
    TARGETS find_server
    RUNTIME DESTINATION lib/${PROJECT_NAME}
    INCLUDES DESTINATION include
)

install(
    DIRECTORY bin/
    DESTINATION bin
    FILES_MATCHING PATTERN "*.sh"
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

install(
    DIRECTORY config
    DESTINATION share/${PROJECT_NAME}
)

install(
    DIRECTORY launch
    DESTINATION share/${PROJECT_NAME}
)

ament_package()
