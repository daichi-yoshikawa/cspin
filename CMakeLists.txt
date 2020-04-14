cmake_minimum_required(VERSION 3.1)
project(CSPIN VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/3rd_party)
set(BOOST_INCLUDE_DIR ${THIRD_PARTY_DIR}/boost-1.72.0)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
add_definitions(-DBOOST_SYSTEM_NO_DEPRECATED)

file(GLOB_RECURSE test_sources "test/[a-zA-Z]*.cpp")

if(VERBOSE)
  message(STATUS "test_sources: ${test_sources}")
endif()

add_library(cspin INTERFACE)
target_include_directories(cspin
  INTERFACE ${PROJECT_SOURCE_DIR}/include
            ${BOOST_INCLUDE_DIR}
)
# rt is needed for shared memory.
target_link_libraries(cspin INTERFACE pthread rt)
target_compile_options(cspin INTERFACE -Wall -Werror -pedantic-errors -Wextra -Wconversion -Wsign-conversion)

add_subdirectory(test)
