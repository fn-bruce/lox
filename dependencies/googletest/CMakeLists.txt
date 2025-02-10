FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
  message(STATUS "Fetching Google Test v1.16")

  FetchContent_MakeAvailable(googletest)

  if (MSVC AND NOT USE_STATIC_RUNTIME)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  endif()
endif()
