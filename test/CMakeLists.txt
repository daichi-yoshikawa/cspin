#add_executable(test_cspin ${test_sources})

#target_include_directories(test_cspin
#  PUBLIC ${PROJECT_SOURCE_DIR}/include
#         ${BOOST_INCLUDE_DIR}
#)
#target_link_libraries(test_cspin cspin)

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
