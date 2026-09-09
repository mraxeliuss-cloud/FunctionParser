cmake_minimum_required(VERSION 3.20)
project(FunctionParser VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Opciones de build
option(BUILD_SHARED_LIBS "Build shared library" OFF)
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)

# Biblioteca principal
add_library(FunctionParser
# aún vacío, TBI
)

# Directorios de inclusión públicos
target_include_directories(FunctionParser
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_library(FunctionParser::FunctionParser ALIAS FunctionParser)

if(BUILD_EXAMPLES)
    add_executable(parser_cli examples/example_cli.cpp)
    target_link_libraries(parser_cli PRIVATE FunctionParser)
endif()

# Para el catch2
if(BUILD_TESTS)
    # Si no tienes un framework de pruebas, puedes empezar con un main simple
    add_executable(parser_tests tests/test_main.cpp)
    target_link_libraries(parser_tests PRIVATE FunctionParser)
endif()

install(DIRECTORY include/ DESTINATION include)