cmake_minimum_required(VERSION 3.10.2)

project(player)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lboost_system -lfmod -lboost_filesystem")

find_package(Boost REQUIRED)

set(FMOD_INC  ${CMAKE_SOURCE_DIR}/inc/)
set(FMOD_LIB  ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmod.so
              ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmod.so.12
              ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmod.so.12.0
              ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmodL.so
              ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmodL.so.12
              ${CMAKE_SOURCE_DIR}/lib/x86_64/libfmodL.so.12.0 )

set(SOURCE_FILES play.cpp player.cpp)

include_directories(${FMOD_INC} ${Boost_INCLUDE_DIRS})
add_executable(playerV1 ${SOURCE_FILES})
target_link_libraries(playerV1 ${Boost_LIBRARIES} ${FMOD_LIB})