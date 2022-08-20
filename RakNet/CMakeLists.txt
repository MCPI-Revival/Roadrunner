project(RakNet)

file(GLOB CBINARYSTREAM cbinarystream/*.c)
file(GLOB CNBT cnbt/*.c)
file(GLOB CZLIBHELPER czlibhelper/*.c)
file(GLOB MINIZ miniz/*.c)
file(GLOB QUEUE queue/*.c)
file(GLOB RAKNET raknet/*.c)

include_directories(.)

add_library(RakNet
        ${CBINARYSTREAM}
        ${CNBT}
        ${CZLIBHELPER}
        ${QUEUE}
        ${MINIZ}
        ${RAKNET})

IF(NOT ("${CMAKE_SYSTEM}" MATCHES "Windows"))
	TARGET_LINK_LIBRARIES(RakNet pthread)
	TARGET_LINK_LIBRARIES(RakNet m)
endif()
