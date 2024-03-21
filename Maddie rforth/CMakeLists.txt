FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	r_forth
	r-forth.c
	token.c
	token.h
	int_stack.c
	int_stack.h)

add_executable(
        int_stack_tests
        int_stack_tests.cc
        int_stack.c
)

target_link_libraries(
        int_stack_tests
        gtest_main
        -lpthread
)


include(GoogleTest)
gtest_discover_tests(int_stack_tests)