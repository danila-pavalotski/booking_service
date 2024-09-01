cmake_minimum_required(VERSION 3.16)

################################################################################
## PROJECT
## Name/Version
################################################################################
project(BookingService VERSION 0.1.0)

################################################################################
## SETTINGS
## basic project settings before use
################################################################################
# If this project is used as a submodule, the variable should be overridden
# to "OFF" in the top-level application (to disable forced cache rewriting)
option(${PARENT}_SUBMODULE_CACHE_OVERWRITE "Enable forced cache rewriting" ON)
if (${PARENT}_SUBMODULE_CACHE_OVERWRITE)
    SET(REWRITE_FORCE "FORCE")
else()
    SET(REWRITE_FORCE "")
endif()


#if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
#    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#    conan_basic_setup()
#endif()

## Link the libraries provided by Conan
#target_link_libraries(CMAKE_PROJECT_NAME ${CONAN_LIBS})

################################################################################
## CONFIGURATION
## project configuration
################################################################################
SET(${PARENT}_BOOKING_SERVICE                   ON  CACHE BOOL "" ${REWRITE_FORCE})
SET(${PARENT}_BOOKING_SERVICE_TEST              ON  CACHE BOOL "" ${REWRITE_FORCE})
SET(${PARENT}_BOOKING_SERVICE_TESTS             ON  CACHE BOOL "" ${REWRITE_FORCE})

################################################################################
## INCLUDING SUBDIRECTORIES
## Adding subdirectories according to the project configuration
################################################################################
add_subdirectory(3rdparty)

if (${PARENT}_BOOKING_SERVICE)
    add_subdirectory(src)
endif()

if (${PARENT}_BOOKING_SERVICE_TEST)
    add_subdirectory(test)
endif()

if (${PARENT}_BOOKING_SERVICE_TESTS)
    add_subdirectory(tests)
endif()


