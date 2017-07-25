cmake_minimum_required(VERSION 2.8.0 FATAL_ERROR)

project(main)

#find_package(MPI REQUIRED)

#include_directories(${MPI_C_INCLUDE_PATH})
include_directories(${CMAKE_HOME_DIRECTORY}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
#set(CMAKE_CXX_FLAGS "-std=c++11")
#set (CMAKE_CXX_STANDARD 11)
#add_compile_options(-std=c++11)
add_definitions(-std=c++11)
#set(CMAKE_CXX_FLAGS -DTEST)
#set(HAVE_MPI ${HAVE_MPI})
#set(CMAKE_CXX_FLAGS "-DHAVE_MPI=${HAVE_MPI}")
#set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS})

aux_source_directory(./src DIR_CXXS)
aux_source_directory(./src/classLib DIR_CLASSES)
#aux_source_directory(./src/tinyxml2 DIR_XMLS)
#aux_source_directory(./src/classManager DIR_CLASSMANAGERS)

#set(DIR_SRCS ${DIR_CXXS} ${DIR_XMLS} ${DIR_CLASSMANAGERS})
set(DIR_SRCS ${DIR_CXXS} ${DIR_CLASSES})
add_executable(main.x ${DIR_SRCS})

#target_link_libraries(main.x ${MPI_LIBRARIES})
