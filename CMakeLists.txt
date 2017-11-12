cmake_minimum_required(VERSION 3.7)
project(toxtUtil)

string(COMPARE EQUAL ${CMAKE_BUILD_TYPE} "Debug" IS_DEBUG)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/tests)

set(SOURCES util.cpp)

set(CMAKE_CXX_STANDARD 14)

# TODO Consider making this MSVC-friendly
set(WARNINGS "-Wall -Wextra -pedantic")
set(SANITIZERS "-fsanitize=address -fsanitize=leak -fsanitize=undefined")
set(DEBUG_SPECIFIC "-Og -g ${SANITIZERS}")
set(RELEASE_SPECIFIC "-Werror -O2")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${WARNINGS} ${DEBUG_SPECIFIC}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${WARNINGS} ${RELEASE_SPECIFIC}")

add_library(${CMAKE_PROJECT_NAME} ${SOURCES})

if (${IS_DEBUG})
  # clang-tidy stuff TODO turn into command such that it only runs when necessary.
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  add_custom_target(tidy ALL
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} ${SOURCES} -checks=performance-*,cppcoreguidelines-*,modernize-*,readability-*,clang-analyzer-* -header-filter=.*
    DEPENDS ${SOURCES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )

  # test stuff
  add_library(catch_main ${TEST_DIR}/catch.cpp)
  add_executable(test_exe ${TEST_DIR}/tests.cpp)
  target_include_directories(test_exe PUBLIC ${PROJECT_SOURCE_DIR})
  target_link_libraries(test_exe ${CMAKE_PROJECT_NAME} catch_main)

  add_custom_target(run_test ALL
    COMMAND test_exe
    DEPENDS test_exe
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()


