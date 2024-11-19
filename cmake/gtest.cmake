message(STATUS "Fetching gtest (v1.15.2)")
FetchContent_Declare(gtest
	GIT_REPOSITORY "https://github.com/google/googletest"
	GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(gtest)

if (gtest_POPULATED)
    message(STATUS "Fetching gtest (v1.15.2) - done")

    enable_testing()

    set(UnitTests
        input_test
    )

    file(GLOB input_test_SOURCES src/input/*.cpp)

    foreach (unitTest IN LISTS UnitTests)
        add_executable(${unitTest} "test/${unitTest}.cpp")

        target_sources(${unitTest} PRIVATE "${${unitTest}_SOURCES}")
        target_link_libraries(${unitTest}
            gtest
            gtest_main
        )
        target_compile_features(${unitTest} PRIVATE
        	cxx_std_20
        )

        add_test(${unitTest} ${unitTest})
    endforeach()

    file(COPY ${CMAKE_SOURCE_DIR}/test/data DESTINATION ${CMAKE_BINARY_DIR})
endif()
