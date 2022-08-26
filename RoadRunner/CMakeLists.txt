project(roadrunner-core)

file(GLOB SOURCE_FILES
    *.cpp
    network/mcpi-packets/*.cpp
    network/raknet/misc/*.cpp
    network/raknet/packet/*.cpp
)

include_directories(.)

add_executable(roadrunner-core ${SOURCE_FILES})
