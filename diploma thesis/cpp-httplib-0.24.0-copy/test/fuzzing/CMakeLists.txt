file(GLOB HTTPLIB_CORPUS corpus/*)
add_executable(httplib_S-test-fuzz
    server_fuzzer.cc
    standalone_fuzz_target_runner.cpp
)
target_link_libraries(httplib_S-test-fuzz PRIVATE httplib_S)
add_test(
    NAME httplib_S-test-fuzz
    COMMAND httplib_S-test-fuzz ${HTTPLIB_CORPUS}
)
