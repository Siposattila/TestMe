CPMAddPackage(
  NAME googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  VERSION 1.15.2
  OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt ON"
)

if (googletest_ADDED)
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
            gmock
        )
        target_compile_features(${unitTest} PRIVATE
        	cxx_std_20
        )

        add_test(${unitTest} ${unitTest})
    endforeach()

    file(COPY ${CMAKE_SOURCE_DIR}/test/data DESTINATION ${CMAKE_BINARY_DIR})
endif()
