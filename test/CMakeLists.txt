#add_executable(test_cspin ${test_sources})

#target_include_directories(test_cspin
#  PUBLIC ${PROJECT_SOURCE_DIR}/include
#         ${BOOST_INCLUDE_DIR}
#)
#target_link_libraries(test_cspin cspin)

add_executable(test_timer_event ${PROJECT_SOURCE_DIR}/test/test_timer_event.cpp)
target_include_directories(test_timer_event
  PUBLIC ${PROJECT_SOURCE_DIR}/include
         ${BOOST_INCLUDE_DIR})
target_link_libraries(test_timer_event cspin)

add_executable(test_shared_memory ${PROJECT_SOURCE_DIR}/test/test_shared_memory.cpp)
target_include_directories(test_shared_memory
  PUBLIC ${PROJECT_SOURCE_DIR}/include
         ${BOOST_INCLUDE_DIR})
target_link_libraries(test_shared_memory cspin)

add_executable(test_udp_sender ${PROJECT_SOURCE_DIR}/test/test_udp_sender.cpp)
target_include_directories(test_udp_sender
  PUBLIC ${PROJECT_SOURCE_DIR}/include
         ${BOOST_INCLUDE_DIR})
target_link_libraries(test_udp_sender cspin)

add_executable(test_udp_receiver ${PROJECT_SOURCE_DIR}/test/test_udp_receiver.cpp)
target_include_directories(test_udp_receiver
  PUBLIC ${PROJECT_SOURCE_DIR}/include
         ${BOOST_INCLUDE_DIR})
target_link_libraries(test_udp_receiver cspin)

add_executable(test_tcp_client ${PROJECT_SOURCE_DIR}/test/test_tcp_client.cpp)
target_include_directories(test_tcp_client
  PUBLIC ${PROJECT_SOURCE_DIR}/include
         ${BOOST_INCLUDE_DIR})
target_link_libraries(test_tcp_client cspin)

add_executable(test_tcp_server ${PROJECT_SOURCE_DIR}/test/test_tcp_server.cpp)
target_include_directories(test_tcp_server
  PUBLIC ${PROJECT_SOURCE_DIR}/include
         ${BOOST_INCLUDE_DIR})
target_link_libraries(test_tcp_server cspin)
