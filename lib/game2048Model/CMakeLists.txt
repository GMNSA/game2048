cmake_minimum_required(VERSION 3.5)

project(TestLib LANGUAGES CXX)
set(OUT_NAME Model2048)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-g3 -Wall -Wextra -Werror")


set(HEADERS
    includes/game2048model.hpp
    )

set(SOURCES
    srcs/game2048model.cpp
    )



add_library(${OUT_NAME} SHARED ${SOURCES} ${HEADERS})

find_package(Qt5 COMPONENTS Core REQUIRED)


set_target_properties(${OUT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 20
        CMAKE_CXX_STANDARD_REQUIRED ON
        )


target_include_directories(${OUT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/includes
        ${CMAKE_CURRENT_BINARY_DIR}
        )


target_link_libraries(${OUT_NAME}
        PUBLIC
        Qt5::Core
        )


