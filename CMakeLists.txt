project(city_builder)
cmake_minimum_required(VERSION 3.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-Wall -Wpedantic)
endif()

find_package(BISON)
find_package(FLEX)


include_directories(parser expressions ${CMAKE_CURRENT_BINARY_DIR})
file(GLOB EXPRESSION_HEADERS 
    expressions/contexte.hh
    expressions/expression.hh
    expressions/expressionBinaire.hh
    expressions/expressionUnaire.hh
    expressions/constante.hh
    expressions/variable.hh
    )

add_library(libexpressions 
    expressions/contexte.cc
    expressions/expressionBinaire.cc
    expressions/expressionUnaire.cc
    expressions/constante.cc
    expressions/variable.cc
    ${EXPRESSION_HEADERS}
    )

BISON_TARGET(parser parser/parser.yy ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp VERBOSE ${CMAKE_CURRENT_BINARY_DIR}/automate.txt)
FLEX_TARGET(scanner parser/scanner.ll  ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)
add_executable(${PROJECT_NAME}
    parser/main.cc
    parser/driver.hh
    parser/driver.cc
    parser/scanner.hh
    parser/scanner.ll
    parser/parser.yy
    ${BISON_parser_OUTPUTS}
    ${FLEX_scanner_OUTPUTS}
)
target_link_libraries(${PROJECT_NAME} libexpressions)