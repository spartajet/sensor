set(SOURCES "simple_test.c")
add_executable(simple_test_win32 ${SOURCES})
target_link_libraries(simple_test_win32 sensor ${SERIALPORT_LIB})
install(TARGETS simple_test_win32 DESTINATION bin)