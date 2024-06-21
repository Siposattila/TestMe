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
	    test/main.cpp
        test/test.cpp
        test/test2.cpp
    )

    add_executable(UnitTests)

    target_sources(UnitTests PRIVATE ${UnitTests_SOURCES})
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${UnitTests_SOURCES})

    target_link_libraries(UnitTests
        gtest
        gtest_main
    )

    add_test(UnitTests UnitTests)
endif()
