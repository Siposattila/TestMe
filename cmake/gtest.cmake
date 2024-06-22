message(STATUS "Fetching gtest (v1.14.0)")
FetchContent_Declare(gtest
	GIT_REPOSITORY "https://github.com/google/googletest"
	GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(gtest)

if (gtest_POPULATED)
    message(STATUS "Fetching gtest (v1.14.0) - done")

    enable_testing()

    set(UnitTests_SOURCES
        test1
        test2
    )

    foreach (unitTest IN LISTS UnitTests_SOURCES)
        add_executable(${unitTest} "test/${unitTest}.cpp")

        target_link_libraries(${unitTest}
            gtest
            gtest_main
        )

        add_test(${unitTest} ${unitTest})
    endforeach()
endif()
