cmake_minimum_required(VERSION 3.15)
project(nqueens CXX)

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_20)

set (CMAKE_CXX_STANDARD 20)

include_directories(src src/Headers)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

file(GLOB SOURCES "src/Sources/*.cpp")
add_executable(nqueens ${SOURCES})



if(CMAKE_BUILD_TYPE MATCHES Release)
  set_target_properties(nqueens PROPERTIES RUNTIME_OUTPUT_DIRECTORY output/release)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set_target_properties(nqueens PROPERTIES RUNTIME_OUTPUT_DIRECTORY output/debug)
endif()

# find_package(SDL REQUIRED)
# include_directories(${SDL_INCLUDE_DIRS})
# target_link_libraries(game PRIVATE ${SDL_LIBRARIES})


