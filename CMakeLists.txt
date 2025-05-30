cmake_minimum_required(VERSION 3.16)

project(signatureProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)
find_package(Qt6 REQUIRED COMPONENTS PrintSupport)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainWindow.cpp
        src/mainWindow.h
        src/mainWindow.ui
)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(AddGitSubmodule)

add_git_submodule("${PROJECT_SOURCE_DIR}/external/Catch2")
add_git_submodule("${PROJECT_SOURCE_DIR}/external/spdlog")
add_git_submodule("${PROJECT_SOURCE_DIR}/external/yaml-cpp")
#add_git_submodule("${PROJECT_SOURCE_DIR}/external/inja")
add_git_submodule("${PROJECT_SOURCE_DIR}/external/json")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(signatureProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/headerWidget.h src/headerWidget.cpp
        src/rowWidget.h src/rowWidget.cpp
        src/database/databaseManager.h src/database/databaseManager.cpp src/database/Queries.h
        src/logger/logger.h src/logger/logger.cpp
        src/structures/rowData.h
        src/signature/signatureWindow.h src/signature/signatureWindow.cpp src/signature/signatureWindow.ui
        src/signature/signatureCanvas.h src/signature/signatureCanvas.cpp
        src/signature/signatureSaver.h src/signature/signatureSaver.cpp
        src/config/configManager.h src/config/configManager.cpp
        src/toolBar/toolBarManager.h src/toolBar/toolBarManager.cpp
        src/printManager/printManager.h src/printManager/printManager.cpp
        src/printManager/templateRenderer.h src/printManager/templateRenderer.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET signatureProject APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(signatureProject SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(signatureProject
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(signatureProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
#target_link_libraries(signatureProject PUBLIC Catch2::Catch2WithMain)
target_link_libraries(signatureProject PRIVATE spdlog::spdlog)
target_link_libraries(signatureProject PRIVATE Qt6::Sql)
target_link_libraries(signatureProject PRIVATE yaml-cpp::yaml-cpp)
target_link_libraries(signatureProject PRIVATE Qt6::PrintSupport)
target_link_libraries(signatureProject PRIVATE nlohmann_json::nlohmann_json)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.signatureProject)
endif()
set_target_properties(signatureProject PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS signatureProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(signatureProject)
endif()
