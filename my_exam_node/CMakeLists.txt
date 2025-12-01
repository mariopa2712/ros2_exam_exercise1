cmake_minimum_required(VERSION 3.8)
project(my_exam_node)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Trova le dipendenze
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sysmonitor_interfaces REQUIRED) # Il pacchetto custom

# Crea l'eseguibile
add_executable(exam_node src/exam_node.cpp)

# Collega le librerie
ament_target_dependencies(exam_node rclcpp std_msgs sysmonitor_interfaces)

# Installa l'eseguibile in modo che ros2 run lo trovi
install(TARGETS
  exam_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
