

cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)

project(Omega)

find_package(MPI REQUIRED)

include_directories(${MPI_C_INCLUDE_PATH})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

aux_source_directory(./src DIR_SRCS)

add_executable(Omega.x ${DIR_SRCS})

target_link_libraries(Omega.x ${MPI_LIBRARIES})
