CPMAddPackage(
  NAME googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  VERSION 1.15.2
  OPTIONS "INSTALL_GTEST OFF" "gtest_force_shared_crt ON"
)

function(cxx_test NAME SRC LIBS)
    add_executable(${NAME} "test/${NAME}.cpp")
    file(GLOB ${NAME}_SOURCES "${SRC}/*.cpp")
    target_sources(${NAME} PRIVATE ${${NAME}_SOURCES})
    target_link_libraries(${NAME} PRIVATE ${LIBS})
    target_compile_features(${NAME} PRIVATE cxx_std_20)
    add_test(${NAME} ${NAME})
endfunction()

if (googletest_ADDED)
    enable_testing()
    set(gtest_LIBRARIES
        gtest
        gtest_main
        gmock
    )

    cxx_test(testme_input_test "src/testme_input"
        "${tree-sitter_LIBRARIES};${gtest_LIBRARIES}"
    )
    cxx_test(testme_logger_test "src/testme_logger"
        ${gtest_LIBRARIES}
    )

    file(COPY ${CMAKE_SOURCE_DIR}/test/data DESTINATION ${CMAKE_BINARY_DIR})
endif()
