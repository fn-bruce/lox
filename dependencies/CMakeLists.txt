include(FetchContent)

#===============================
# Options and initial settings |
#===============================

message(STATUS "Fetching third party libraries")
option(LINK_DEPS_STATIC CACHE ON)

set(GOOGLETEST_VERSION 1.16)

if (NOT LINK_DEPS_STATIC)
  set(BUILD_SHARED_LIBS ON)
else()
  set(BUILD_SHARED_LIBS OFF)
endif()


#============================
# FetchContent declarations |
#============================

if(BUILD_TESTING)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
endif()

#============================

if(BUILD_TESTING)
  add_subdirectory(googletest)
endif()
