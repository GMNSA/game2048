cmake_minimum_required(VERSION 3.5)

project(PROJECT_NAME} LANGUAGES CXX)
set(OUT_NAME TestGame2048)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "-g3 -Wall -Wextra -Werror")

set(LIB_GAME_2048_CODE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../lib)
set(LIB_GAME_2048_CODE_HEADERS${CMAKE_CURRENT_SOURCE_DIR}/../../lib/game2048Model/includes)

add_compile_definitions(FOR_TEST)

set(HEADERS
	includes/tst_game2048.hpp
    )

set(SOURCES
	srcs/tst_game2048.cpp
    )

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../srcs)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../includes)

find_package(Qt5 COMPONENTS Core Test REQUIRED)

add_executable(${OUT_NAME} ${SOURCES} ${HEADERS})
add_test(NAME OUT_NAME COMMAND OUT_NAME)
enable_testing()



set_target_properties(${OUT_NAME}
        PROPERTIES
        CMAKE_CXX_STANDARD 20
        CMAKE_CXX_STANDARD_REQUIRED ON
        )


target_include_directories(${OUT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/includes
        ${LIB_GAME_2048_CODE_HEADERS}
        ${LIB_GAME_2048_CODE_PATH}
        )



target_link_libraries(${OUT_NAME}
        PUBLIC
        Qt5::Core
        Qt5::Test
        Model2048
        )


