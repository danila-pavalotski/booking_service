cmake_minimum_required(VERSION 3.16)

################################################################################
## 3RD-PARTY
## dependencies for the project
################################################################################
project(3rdparty LANGUAGES CXX)

################################################################################
## SETTINGS
## basic 3rd-party settings before use
################################################################################
SET(PARENT ${PARENT}_BOOKING_SERVICE_3RDPARTY)
# Disable self-overwriting of parameters inside included subdirectories.
SET(${PARENT}_SUBMODULE_CACHE_OVERWRITE                     OFF CACHE BOOL "" FORCE)


SET(${PARENT}_SUBMODULE_NHOLMANN_JSON                       ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_NHOLMANN_JSON)
    SET(${PARENT}_NHOLMANN_JSON                             ON  CACHE BOOL "" FORCE)
endif()

SET(${PARENT}_SUBMODULE_GOOGLE_TEST                         ON  CACHE BOOL "" FORCE)
if (${PARENT}_SUBMODULE_GOOGLE_TEST)
    SET(${PARENT}_GOOGLE_TEST                               ON  CACHE BOOL "" FORCE)
endif()

if (${PARENT}_NHOLMANN_JSON)
    add_subdirectory(nholmann)
endif()

if (${PARENT}_GOOGLE_TEST)
    add_subdirectory(googletest)
endif()

