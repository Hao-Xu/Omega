

cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)

project(Omega)

find_package(MPI REQUIRED)

include_directories(${MPI_C_INCLUDE_PATH})
include_directories(${CMAKE_HOME_DIRECTORY}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})

aux_source_directory(./src DIR_SRCS)
aux_source_directory(./src/tinyxml2 DIR_XMLS)

add_executable(Omega.x ${DIR_SRCS} ${DIR_XMLS})

target_link_libraries(Omega.x ${MPI_LIBRARIES})
