project(roadrunner-core)

file(GLOB SOURCE_FILES
    *.cpp
    network/mcpi-packets/*.cpp
    network/raknet/misc/*.cpp
    network/raknet/packet/*.cpp
)

include_directories(.)
include_directories(${RAKNET_INCLUDE_DIRS})

add_executable(roadrunner-core ${SOURCE_FILES})
target_link_libraries(roadrunner-core RakNetLibStatic)
