option(OPTION_TES3MP_PRE07 "Temporary. Pre 0.7.0 compatible mode." OFF)

set(BROWSER_UI
        ${CMAKE_SOURCE_DIR}/files/tes3mp/ui/Main.ui
        ${CMAKE_SOURCE_DIR}/files/tes3mp/ui/ServerInfo.ui
        )
set(BROWSER
        main.cpp
        MainWindow.cpp
        ServerModel.cpp
        ServerInfoDialog.cpp
        MySortFilterProxyModel.cpp
        netutils/HTTPNetwork.cpp
        netutils/Utils.cpp
        netutils/QueryClient.cpp
        PingUpdater.cpp
        PingHelper.cpp
        QueryHelper.cpp
        Settings.cpp
        ${CMAKE_SOURCE_DIR}/files/tes3mp/browser.rc
        )

set(BROWSER_HEADER_MOC
        MainWindow.hpp
        ServerModel.hpp
        ServerInfoDialog.hpp
        MySortFilterProxyModel.hpp
        PingUpdater.hpp
        PingHelper.hpp
        QueryHelper.hpp
        )

set(BROWSER_HEADER
        ${BROWSER_HEADER_MOC}
        netutils/HTTPNetwork.hpp
        netutils/Utils.hpp
        netutils/QueryClient.hpp
        Types.hpp
        Settings.hpp
        )

source_group(browser FILES ${BROWSER} ${BROWSER_HEADER})

set(QT_USE_QTGUI 1)

# Set some platform specific settings
if(WIN32)
    set(GUI_TYPE WIN32)
    set(QT_USE_QTMAIN TRUE)
endif(WIN32)

if (DESIRED_QT_VERSION MATCHES 4)
    message(SEND_ERROR "QT4 is not supported.")
    #include(${QT_USE_FILE})
    #QT4_ADD_RESOURCES(RCC_SRCS ${CMAKE_SOURCE_DIR}/files/launcher/launcher.qrc)
    #QT4_WRAP_CPP(MOC_SRCS ${BROWSER_HEADER_MOC})
    #QT4_WRAP_UI(UI_HDRS ${BROWSER_UI})
else()
    QT5_ADD_RESOURCES(RCC_SRCS ${CMAKE_SOURCE_DIR}/files/launcher/launcher.qrc)
    QT5_WRAP_CPP(MOC_SRCS ${BROWSER_HEADER_MOC})
    QT5_WRAP_UI(UI_HDRS ${BROWSER_UI})
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})
if(NOT WIN32)
    include_directories(${LIBUNSHIELD_INCLUDE_DIR})
endif(NOT WIN32)

# Main executable
add_executable(tes3mp-browser
        ${GUI_TYPE}
        ${BROWSER}
        ${BROWSER_HEADER}
        ${RCC_SRCS}
        ${MOC_SRCS}
        ${UI_HDRS}
        )

set_property(TARGET tes3mp-browser PROPERTY CXX_STANDARD 14)

if (OPTION_TES3MP_PRE07)
    target_compile_definitions(tes3mp-browser PRIVATE TES3MP_PRE07)
endif (OPTION_TES3MP_PRE07)


if (WIN32)
    INSTALL(TARGETS tes3mp-browser RUNTIME DESTINATION ".")
endif (WIN32)

target_link_libraries(tes3mp-browser
        ${SDL2_LIBRARY_ONLY}
        ${RakNet_LIBRARY}
        components
        )

if (DESIRED_QT_VERSION MATCHES 4)
#    target_link_libraries(tes3mp-browser ${QT_QTGUI_LIBRARY} ${QT_QTCORE_LIBRARY})
#    if(WIN32)
#        target_link_libraries(tes3mp-browser ${QT_QTMAIN_LIBRARY})
#    endif(WIN32)
else()
    qt5_use_modules(tes3mp-browser Widgets Core)
endif()

if (BUILD_WITH_CODE_COVERAGE)
    add_definitions (--coverage)
    target_link_libraries(tes3mp-browser gcov)
endif()
