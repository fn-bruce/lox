add_library(lox)

target_include_directories(lox
  PUBLIC
    ${lox_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(lox
  PUBLIC
    lox.cpp
    token.cpp
    scanner.cpp
    expr.cpp
    stmt.cpp
    parser.cpp
    environment.cpp
    interpreter.cpp
    ast_printer.cpp
    runtime_error.cpp
)

add_executable(lox_repl)
set_target_properties(lox_repl PROPERTIES OUTPUT_NAME "lox")

target_include_directories(lox_repl
  PUBLIC
    ${lox_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(lox_repl
  PRIVATE
    main.cpp
)

target_link_libraries(lox_repl PRIVATE lox)
