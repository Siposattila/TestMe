message(STATUS "Fetching tree-sitter (v0.22.6)")
FetchContent_Declare(tree-sitter
    GIT_REPOSITORY https://github.com/tree-sitter/tree-sitter.git
    GIT_TAG v0.22.6
)
FetchContent_MakeAvailable(tree-sitter)

if (tree-sitter_POPULATED)
    message(STATUS "Fetching tree-sitter (v0.22.6) - done")
    add_library(tree-sitter STATIC
        "${tree-sitter_SOURCE_DIR}/lib/src/lib.c"
    )

    target_include_directories(tree-sitter
        PRIVATE
            $<BUILD_INTERFACE:${tree-sitter_SOURCE_DIR}/lib/src>
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${tree-sitter_SOURCE_DIR}/lib/include>
    )
    target_compile_options(tree-sitter PRIVATE
        "$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wno-conversion>"
    )
endif()

function(add_grammar_from_repo NAME REPO VERSION)
    message(STATUS "Fetching ${NAME} (${VERSION})")
    FetchContent_Declare(${NAME}
        GIT_REPOSITORY ${REPO}
        GIT_TAG ${VERSION}
    )
    FetchContent_MakeAvailable(${NAME})

    if ("${${NAME}_POPULATED}")
        message(STATUS "Fetching ${NAME} (${VERSION}) - done")
        add_library(${NAME})

        file(GLOB maybe_scanner "${${NAME}_SOURCE_DIR}/src/scanner.c")
        target_sources(${NAME}
            PRIVATE
                "${${NAME}_SOURCE_DIR}/src/parser.c"
                ${maybe_scanner}
        )
        target_include_directories(${NAME}
            PRIVATE
                # parser.h is stored within the src directory, so we need to include
                # src in the search paths
                $<BUILD_INTERFACE:${${NAME}_SOURCE_DIR}/src>
            PUBLIC
                $<INSTALL_INTERFACE:include>
        )

        target_link_libraries(${NAME} INTERFACE
            tree-sitter
        )
        target_compile_options(${NAME} PRIVATE
            "$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wno-unused-but-set-variable>"
        )
    endif()
endfunction(add_grammar_from_repo)

add_grammar_from_repo(tree-sitter-cpp
    https://github.com/tree-sitter/tree-sitter-cpp.git
    v0.22.2
)

add_grammar_from_repo(tree-sitter-c-sharp
    https://github.com/tree-sitter/tree-sitter-c-sharp.git
    v0.21.2
)

add_grammar_from_repo(tree-sitter-java
    https://github.com/tree-sitter/tree-sitter-java.git
    v0.21.0
)

target_link_libraries(TestMe PRIVATE
    tree-sitter
    tree-sitter-cpp
    tree-sitter-c-sharp
    tree-sitter-java
)
