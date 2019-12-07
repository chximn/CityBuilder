project(city_builder)
cmake_minimum_required(VERSION 3.1.0)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-Wall -Wpedantic)
endif()

foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()


find_package(BISON)
find_package(FLEX)


include_directories(parser expressions types commands ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB COMMANDS_HEADERS
	commands/command.hh
)

add_library(libcommands
	commands/command.cc
	${COMMANDS_HEADERS}
)

file(GLOB EXPRESSION_HEADERS
    expressions/expression.hh
    expressions/expressionBinaire.hh
    expressions/expressionUnaire.hh
    expressions/constante.hh
    expressions/variable.hh
	expressions/contexte.hh
)

add_library(libexpressions
    expressions/expressionBinaire.cc
    expressions/expressionUnaire.cc
    expressions/constante.cc
	expressions/variable.cc
	expressions/contexte.cc
    ${EXPRESSION_HEADERS}
)

file(GLOB TYPE_HEADERS
	types/degree.hh
	types/point.hh
	types/house.hh
	types/color.hh
    types/city.hh
)

add_library(libtypes
	types/point.cc
	types/house.cc
	types/degree.cc
	types/color.cc
    types/city.cc
	${TYPE_HEADERS}
)

add_library(GUI
	GUI/city.cc
)

target_link_libraries(GUI Qt5::Widgets)

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
target_link_libraries(${PROJECT_NAME} GUI libexpressions libtypes libcommands)
