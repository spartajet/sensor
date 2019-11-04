set(SOURCES "simple_test.c")
add_executable(simple_test_ubuntu ${SOURCES})
target_link_libraries(simple_test_ubuntu sensor ${SERIALPORT_LIB})
install(TARGETS simple_test_ubuntu DESTINATION bin)