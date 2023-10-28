cmake_minimum_required(VERSION 3.16)

project(User VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON) # qrc
find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appUser
    main.cpp
    settings.h settings.cpp
)

qt_add_qml_module(appUser
    URI User
    VERSION 1.0
    QML_FILES Main.qml LoginDialog.qml BooksPage.qml BookDelegate.qml CommentPage.qml UserPage.qml StorePage.qml
    script.js
    RESOURCES qml.qrc
    QML_FILES CommentDelegate.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appUser PROPERTIES
    #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appUser
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appUser
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appUser
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
