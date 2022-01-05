cmake_minimum_required(VERSION 3.5)

project(Game2048QMLModel LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

set(QML_IMPORT_PATH ${CMAKE_CURRENT_LIST_DIR}/qml
  CACHE STRING "Qt Creator 5.15 extra qml import paths"
  FORCE)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)

set(PROJECT_SOURCES
        qml.qrc
        res.qrc
        javascript/js.qrc
        srcs/main.cpp
        srcs/game2048logic.cpp
        srcs/model2048.cpp
)

set(PROJECT_HEADERS
		includes/game2048logic.hpp
        includes/model2048.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Game2048QMLModel
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
    )
else()
    if(ANDROID)
        add_library(Game2048QMLModel SHARED
            ${PROJECT_SOURCES}
			${PROJECT_HEADERS}
        )
    else()
        add_executable(Game2048QMLModel
          ${PROJECT_SOURCES}
		  ${PROJECT_HEADERS}
        )
    endif()
endif()

target_include_directories(Game2048QMLModel
	PUBLIC
	${CMAKE_CURRENT_LIST_DIR}/includes
    ${CMAKE_CURRENT_LIST_DIR}/lib/includes
    )

target_compile_definitions(Game2048QMLModel
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(Game2048QMLModel
  PRIVATE
  Qt${QT_VERSION_MAJOR}::Core
  Qt${QT_VERSION_MAJOR}::Quick
  Model2048
  )


add_subdirectory(tests)
add_subdirectory(lib)
