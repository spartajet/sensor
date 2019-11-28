set(SOURCES "simple_test.c")
add_executable(simple_test_x64 ${SOURCES})
target_link_libraries(simple_test_x64 sensor ${SERIALPORT_LIB})
install(TARGETS simple_test_x64 DESTINATION bin)