cmake_minimum_required(VERSION 3.10.2)

project(player)
set(CMAKE_CXX_STANDARD 11)

set(GCC_COVERAGE_LINK_FLAGS "-lboost_system -lboost_filesystem -lfmod -lsfml-system -lsfml-audio")

# fmod Lib
set(FMOD_INC  ${CMAKE_SOURCE_DIR}/inc/)
set(FMOD_LIB  ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmod.so
              ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmod.so.12
              ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmod.so.12.0
              ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmodL.so
              ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmodL.so.12
              ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmodL.so.12.0 )
message("FMOD included")

include_directories(${FMOD_INC})
link_directories(${FMOD_LIB})
# SFML
find_package(SFML 2.5.1 COMPONENTS system audio )

set(SFML_INCLUDE_DIR  "${CMAKE_SOURCE_DIR}/inc/")
set(SFML_LIBRARY_DIR
        ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-audio.so         ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-graphics.so.2.5.1  ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-system.so.2.5
        ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-audio.so.2.5     ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-network.so         ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-system.so.2.5.1
        ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-audio.so.2.5.1   ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-network.so.2.5     ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-window.so
        ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-graphics.so      ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-network.so.2.5.1   ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-window.so.2.5
        ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-graphics.so.2.5  ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-system.so          ${CMAKE_SOURCE_DIR}/lib/sfml_lib/libsfml-window.so.2.5.1
        )

if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    link_directories(${SFML_LIBRARY_DIR})
    message("SFML included")
endif()
# Boost 1.72
find_package(Boost REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARIES})
    message("Boost included")
endif()

# source files
set(SOURCE_FILES play.cpp player.cpp)

add_executable(playerV2 ${SOURCE_FILES})

target_link_libraries(playerV2 ${GCC_COVERAGE_LINK_FLAGS} ${FMOD_LIB} ${Boost_LIBRARIES} ${SFML_LIBRARY_DIR})
