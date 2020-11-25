cmake_minimum_required(VERSION 3.0.2)
project(qxwz_rtcm_service)

add_compile_options(-std=c++11)

find_package(catkin  REQUIRED
roscpp
message_generation
)


catkin_package(
 INCLUDE_DIRS include
#  LIBRARIES qxwz_rtcm_service
#  CATKIN_DEPENDS other_catkin_pkg
#  DEPENDS system_lib
)




link_directories(
${catkin_LIB_DIRS} lib)

include_directories(
include
${catkin_INCLUDE_DIRS}
)


add_executable(qxwz_service_core
  src/qxwz_service_core.cpp
)

target_link_libraries(qxwz_service_core
  ${catkin_LIBRARIES} rtcm
)

add_dependencies(qxwz_service_core ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(qxwz_service_core
  ${catkin_LIBRARIES}
)
