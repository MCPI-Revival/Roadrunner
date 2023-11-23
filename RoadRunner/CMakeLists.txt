project(roadrunner-core)

file(GLOB_RECURSE SOURCE_FILES *.cpp)

include_directories(${RakNet_SOURCE_DIR}/Source) 

add_executable(roadrunner-core ${SOURCE_FILES})
target_include_directories(roadrunner-core PUBLIC ".")
target_link_libraries(roadrunner-core RakNetLibStatic)
