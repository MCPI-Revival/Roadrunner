project(roadrunner-core)

file(GLOB_RECURSE SOURCE_FILES *.cpp)

include_directories(.)
include_directories(${RAKNET_INCLUDE_DIRS})

add_executable(roadrunner-core ${SOURCE_FILES})
target_link_libraries(roadrunner-core RakNetLibStatic)
