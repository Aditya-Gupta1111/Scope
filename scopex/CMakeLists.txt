cmake_minimum_required(VERSION 3.16)
project(scopex VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    QuickControls2
    SerialPort
    Charts
    Core
)

qt_standard_project_setup(REQUIRES 6.8)

# Add executable
qt_add_executable(appscopex
    main.cpp
    serialhandler.cpp
    serialhandler.h
)

# Add QML module
qt_add_qml_module(appscopex
    URI "ScopeX"
    VERSION "1.0"
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES
        Main.qml
        ScopeChart.qml
        DFTChart.qml
)

target_link_libraries(appscopex
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::SerialPort
        Qt6::Charts
        Qt6::Core
)

# Installation (optional)
include(GNUInstallDirs)
install(TARGETS appscopex
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
