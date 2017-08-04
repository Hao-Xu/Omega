# Generation of the documentation
cmake_minimum_required(VERSION 2.8)
project (Omega)

option(BUILD_DOCUMENTATION "Use Doxygen to create the HTML documentation" ON)
if(BUILD_DOCUMENTATION)
    FIND_PACKAGE(Doxygen)
    if (DOXYGEN_FOUND)
        # set input and output files
	# set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
	# set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/test2)
        add_custom_target (doc ALL
		#${DOXYGEN_EXECUTABLE} Doxyfile
		#            WORKING_DIRECTORY "./doc")
            ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
                   )

    else (DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")

    endif(DOXYGEN_FOUND)

endif()


