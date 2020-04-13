cmake_minimum_required(VERSION 3.1)
project(CSPIN VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)

set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/3rd_party)
set(BOOST_INCLUDE_DIR ${THIRD_PARTY_DIR}/boost-1.72.0)
add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
add_definitions(-DBOOST_SYSTEM_NO_DEPRECATED)

file(GLOB_RECURSE sources "src/[a-zA-Z]*.cpp")
file(GLOB_RECURSE test_sources "test/[a-zA-Z]*.cpp")

if(VERBOSE)
  message(STATUS "sources: ${sources}")
  message(STATUS "test_sources: ${test_sources}")
endif()

add_library(cspin SHARED ${sources})
target_include_directories(cspin
  PUBLIC ${PROJECT_SOURCE_DIR}/include
         ${BOOST_INCLUDE_DIR}
)
# rt is needed for shared memory.
#target_link_libraries(cspin pthread rt boost_system)
target_link_libraries(cspin pthread rt)
target_compile_options(cspin PRIVATE -Wall -Werror -pedantic-errors -Wextra -Wconversion -Wsign-conversion)

add_subdirectory(test)
