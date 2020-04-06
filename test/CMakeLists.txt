add_executable(test_cspin ${test_sources})

target_include_directories(test_cspin
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(test_cspin cspin)
