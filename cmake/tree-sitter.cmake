CPMAddPackage(
  NAME tree-sitter
  GIT_REPOSITORY https://github.com/tree-sitter/tree-sitter.git
  VERSION 0.24.4
  DOWNLOAD_ONLY YES
)

if (tree-sitter_ADDED)
    add_library(tree-sitter)
    target_sources(tree-sitter PRIVATE
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
    CPMAddPackage(
        NAME ${NAME}
        GIT_REPOSITORY ${REPO}
        VERSION ${VERSION}
        DOWNLOAD_ONLY YES
    )

    if ("${${NAME}_ADDED}")
        add_library(${NAME})

        file(GLOB maybe_scanner "${${NAME}_SOURCE_DIR}/src/scanner.c")
        target_sources(${NAME} PRIVATE
            "${${NAME}_SOURCE_DIR}/src/parser.c"
            ${maybe_scanner}
        )
        target_include_directories(${NAME} PRIVATE
            $<BUILD_INTERFACE:${${NAME}_SOURCE_DIR}/src> PUBLIC
            $<INSTALL_INTERFACE:include>
        )
        target_link_libraries(${NAME} INTERFACE tree-sitter)
        target_compile_options(${NAME} PRIVATE
            "$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wno-unused-but-set-variable>"
        )
    endif()
endfunction(add_grammar_from_repo)

add_grammar_from_repo(tree-sitter-cpp
    https://github.com/tree-sitter/tree-sitter-cpp.git
    0.23.4
)

add_grammar_from_repo(tree-sitter-c-sharp
    https://github.com/tree-sitter/tree-sitter-c-sharp.git
    0.23.1
)

add_grammar_from_repo(tree-sitter-java
    https://github.com/tree-sitter/tree-sitter-java.git
    0.23.4
)

set(tree-sitter_LIBRARIES
    tree-sitter
    tree-sitter-cpp
    tree-sitter-c-sharp
    tree-sitter-java
)
