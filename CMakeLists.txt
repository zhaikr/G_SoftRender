cmake_minimum_required(VERSION 3.5)

project(softrender VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

#add 3rd-lib
include_directories(./lib)
set(PROJECT_SOURCES
        basicdatastructure.hpp
        rendermath.hpp
        main.cpp
        softrender.h
        softrender.cpp
        softrender.ui
        softrenderwidget.h
        softrenderwidget.cpp
        softrenderwidget.ui
        framebuffer.h
        framebuffer.cpp
        softrendercore.h
        softrendercore.cpp
        model.h
        model.cpp
        mesh.h
        mesh.cpp
        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(softrender
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET softrender APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(softrender SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(softrender
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(softrender PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(softrender PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS softrender
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(softrender)
endif()
