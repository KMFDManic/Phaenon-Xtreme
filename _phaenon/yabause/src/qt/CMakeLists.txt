project( yabause-qt )

yab_port_start()

option(YAB_USE_QT5 "Use Qt 5 if available." ON)

if(YAB_USE_QT5) 
	find_package(Qt5 COMPONENTS Widgets QUIET)
endif()

if(Qt5_FOUND) 
	message(STATUS "Qt5 Found")

	if( YAB_WANT_OPENGL )
        	find_package(Qt5OpenGL)
	endif()

	include_directories(${Qt5Widgets_INCLUDE_DIRS})
	add_definitions(${Qt5Widgets_DEFINITIONS}) 

	if (WIN32)
        	find_package(Qt5Core)
	endif()
	find_package(Qt5Multimedia REQUIRED)
	add_definitions(-DHAVE_QT_MULTIMEDIA=1)

    # Since Qt5's cmake script doesn't set it, we will have to
    SET(QT_BINARY_DIR "${_qt5Core_install_prefix}/bin")
    if (MSYS2_BUILD)
        SET(QT_PLUGINS_DIR "${_qt5Core_install_prefix}/share/qt5/plugins")
    else()
        SET(QT_PLUGINS_DIR "${_qt5Core_install_prefix}/plugins")
    endif()

else() 
	set( QT_USE_QTCORE TRUE )
	set( QT_USE_QTGUI TRUE )
	set ( QT_USE_QTMULTIMEDIA TRUE )
	if( YAB_WANT_OPENGL )
		set( QT_USE_QTOPENGL TRUE )
	endif()
	if (WIN32)
		set( QT_USE_QTMAIN TRUE )
	endif()
	
	find_package(Qt4)

	if (NOT QT4_FOUND)
		message(STATUS "NO QT4_FOUND OR Qt5_FOUND")
		return ()
	endif ()

	message (WARNING "Qt4 is deprecated. Support will be removed in the future.")

	if (QT_QTMULTIMEDIA_FOUND)
		add_definitions(-DHAVE_QT_MULTIMEDIA=1)
	endif ()

	# dunno what it does exactly ... but seem required
	include( ${QT_USE_FILE} )
endif() 

# qt resources file
set( yabause_qt_RESOURCES resources/resources.qrc )

if ( WIN32 )
	# Windows port libraries
	set( yabause_qt_windows_LIBRARIES
		vfw32 legacy_stdio_definitions.lib )

	# resources
	set ( yabause_qt_windows_RESOURCES
		resources/icons/yabause.rc )
endif ( WIN32 )

if(APPLE)
    find_library(AUDIO_LIBRARY AudioUnit)
    set(yabause_qt_macosx_LIBRARIES ${AUDIO_LIBRARY})
endif()

# qt forms
set( yabause_qt_FORMS
	ui/UIYabause.ui
	ui/UISettings.ui
	ui/UIAbout.ui
	ui/UICheats.ui
	ui/UICheatAR.ui
	ui/UICheatRaw.ui
	ui/UICheatSearch.ui
	ui/UIBackupRam.ui
	ui/UIPortManager.ui
	ui/UIPadSetting.ui 
	ui/UI3DControlPadSetting.ui 
    ui/UIWheelSetting.ui 
    ui/UIMissionStickSetting.ui 
    ui/UIDoubleMissionStickSetting.ui 
	ui/UIGunSetting.ui
	ui/UIMouseSetting.ui 
    ui/UIDebugCPU.ui
    ui/UIDebugSCSP.ui
    ui/UIDebugSCSPDSP.ui
    ui/UIDebugVDP1.ui
    ui/UIDebugVDP2.ui
    ui/UIDebugVDP2Viewer.ui
    ui/UIHexInput.ui
    ui/UIMemoryTransfer.ui 
    ui/UIMemoryEditor.ui 
    ui/UIMemorySearch.ui )

# pure C headers
set( yabause_qt_HEADERS
	QtYabause.h
	CommonDialogs.h
	PerQt.h
	Arguments.h )

# C headers needing moc
set( yabause_qt_MOC_HEADERS
	ui/UIYabause.h
	ui/UISettings.h
	ui/UIAbout.h
	ui/UICheats.h
	ui/UICheatAR.h
	ui/UICheatRaw.h
	ui/UICheatSearch.h
	ui/UIBackupRam.h
	ui/UIPortManager.h
	ui/UIControllerSetting.h
	ui/UIPadSetting.h
	ui/UI3DControlPadSetting.h
    ui/UIWheelSetting.h
    ui/UIMissionStickSetting.h
    ui/UIDoubleMissionStickSetting.h
	ui/UIGunSetting.h
	ui/UIMouseSetting.h
	ui/UIShortcutManager.h
    ui/UIDebugCPU.h
    ui/UIDebugM68K.h
    ui/UIDebugSCSP.h
    ui/UIDebugSCSPChan.h
    ui/UIDebugSCSPDSP.h
    ui/UIDebugSCUDSP.h
    ui/UIDebugSH2.h
    ui/UIDebugVDP1.h
    ui/UIDebugVDP2.h
    ui/UIDebugVDP2Viewer.h
    ui/UIDisasm.h
    ui/UIHexInput.h
    ui/UIMemoryTransfer.h
    ui/UIHexEditor.h
    ui/UIMemoryEditor.h
    ui/UIMemorySearch.h
	YabauseGL.h
	VolatileSettings.h
	Settings.h
	YabauseThread.h )

# C sources
set( yabause_qt_SOURCES
	main.cpp
	QtYabause.cpp
	CommonDialogs.cpp
	PerQt.c
	ui/UIYabause.cpp
	ui/UISettings.cpp
	ui/UIAbout.cpp
	ui/UICheats.cpp
	ui/UICheatAR.cpp
	ui/UICheatRaw.cpp
	ui/UICheatSearch.cpp
	ui/UIBackupRam.cpp
	ui/UIPortManager.cpp
	ui/UIControllerSetting.cpp
	ui/UIPadSetting.cpp
	ui/UI3DControlPadSetting.cpp
    ui/UIWheelSetting.cpp
    ui/UIMissionStickSetting.cpp
    ui/UIDoubleMissionStickSetting.cpp
	ui/UIGunSetting.cpp
	ui/UIMouseSetting.cpp
	ui/UIShortcutManager.cpp
    ui/UIDebugCPU.cpp
    ui/UIDebugM68K.cpp
    ui/UIDebugSCSP.cpp
    ui/UIDebugSCSPChan.cpp
    ui/UIDebugSCSPDSP.cpp
    ui/UIDebugSCUDSP.cpp
    ui/UIDebugSH2.cpp
    ui/UIDebugVDP1.cpp
    ui/UIDebugVDP2.cpp
    ui/UIDebugVDP2Viewer.cpp
    ui/UIDisasm.cpp
    ui/UIHexInput.cpp
    ui/UIMemoryTransfer.cpp
    ui/UIHexEditor.cpp
    ui/UIMemoryEditor.cpp
    ui/UIMemorySearch.cpp
	Settings.cpp
	VolatileSettings.cpp
	YabauseThread.cpp
	Arguments.cpp )

if( OPENGL_FOUND )
	set( yabause_qt_SOURCES ${yabause_qt_SOURCES} YabauseGL.cpp )
else()
	set( yabause_qt_SOURCES ${yabause_qt_SOURCES} YabauseSoftGL.cpp )
endif()

if(Qt5_FOUND) 
	QT5_ADD_RESOURCES( yabause_qt_RCC_RESOURCES ${yabause_qt_RESOURCES} )
	QT5_WRAP_UI( yabause_qt_UI_FORMS ${yabause_qt_FORMS} )
	QT5_WRAP_CPP( yabause_qt_MOC_SOURCES ${yabause_qt_MOC_HEADERS} )
else() 
	QT4_ADD_RESOURCES( yabause_qt_RCC_RESOURCES ${yabause_qt_RESOURCES} )
	QT4_WRAP_UI( yabause_qt_UI_FORMS ${yabause_qt_FORMS} )
	QT4_WRAP_CPP( yabause_qt_MOC_SOURCES ${yabause_qt_MOC_HEADERS} )
endif() 

set( yabause_qt_SOURCES ${yabause_qt_SOURCES} resources/icons/yabause.icns )
set_source_files_properties( resources/icons/yabause.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources )

add_executable( yabause-qt WIN32
	${yabause_qt_windows_SOURCES}
	${yabause_qt_windows_RESOURCES}
	${yabause_qt_RCC_RESOURCES}
	${yabause_qt_HEADERS}
	${yabause_qt_MOC_HEADERS}
	${yabause_qt_SOURCES}
	${yabause_qt_UI_FORMS}
	${yabause_qt_MOC_SOURCES} )

if (Qt5_FOUND)
include_directories(
	.
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/ui
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5OpenGL_INCLUDE_DIRS} 
	${Qt5Multimedia_INCLUDE_DIRS} )
else()
include_directories(
	.
	${CMAKE_CURRENT_BINARY_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/ui
	${QT_INCLUDE_DIR}
	${QT_QTCORE_INCLUDE_DIR}
	${QT_QTGUI_INCLUDE_DIR}
	${QT_QTOPENGL_INCLUDE_DIR} )
endif()

# APPLE // not necessary mac os x, but i don't care ;)
if (APPLE)
	set_target_properties( yabause-qt PROPERTIES MACOSX_BUNDLE true )
	set_target_properties( yabause-qt PROPERTIES MACOSX_BUNDLE_ICON_FILE yabause.icns )
	set_target_properties( yabause-qt PROPERTIES MACOSX_BUNDLE_LONG_VERSION_STRING "${YAB_VERSION}" )
	set_target_properties( yabause-qt PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME Yabause )
	set_target_properties( yabause-qt PROPERTIES MACOSX_BUNDLE_SHORT_VERSION_STRING "${YAB_VERSION}" )
	set_target_properties( yabause-qt PROPERTIES MACOSX_BUNDLE_COPYRIGHT "(c) Yabause Team" )
endif (APPLE)

target_link_libraries( yabause-qt yabause )
target_link_libraries( yabause-qt ${YABAUSE_LIBRARIES} )
target_link_libraries( yabause-qt ${PORT_LIBRARIES} )
target_link_libraries( yabause-qt ${yabause_qt_windows_LIBRARIES} )
target_link_libraries( yabause-qt ${yabause_qt_macosx_LIBRARIES} )
target_link_libraries( yabause-qt ${LIBCHDR_LIBRARIES} )
target_link_libraries( yabause-qt ${zlib_STATIC_LIBRARIES} )
if (Qt5_FOUND)
	target_link_libraries( yabause-qt ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${Qt5Core_QTMAIN_LIBRARIES} ${Qt5Multimedia_LIBRARIES})
else()
	target_link_libraries( yabause-qt ${QT_LIBRARIES} )
endif()

yab_port_success(yabause-qt)
configure_file(yabause.desktop.in ${YAB_PORT_NAME}.desktop)

if (WIN32)
	install(TARGETS yabause-qt DESTINATION ".")
	if (GLUT_FOUND)
		install(FILES ${GLUT_INCLUDE_DIR}/../freeglut.dll DESTINATION ".")
	endif ()
	if (SDL_FOUND)
		get_filename_component(SDL_BINARY_DIR ${SDL_LIBRARY} PATH)
		install(DIRECTORY ${SDL_BINARY_DIR}/
			DESTINATION "."
			FILES_MATCHING PATTERN "SDL.dll")
	endif ()
	if (SDL2_FOUND)
		if (NOT MSYS2_BUILD)
			get_filename_component(SDL2_BINARY_DIR ${SDL2_LIBRARY} PATH)
			install(DIRECTORY ${SDL2_BINARY_DIR}/
				DESTINATION "."
				FILES_MATCHING PATTERN "SDL2.dll")
		else ()
			install(FILES ${QT_BINARY_DIR}/SDL2.dll DESTINATION ".")
		endif ()
	endif ()
	if(Qt5_FOUND) 
		install(FILES ${QT_BINARY_DIR}/Qt5Core.dll DESTINATION ".")
		install(FILES ${QT_BINARY_DIR}/Qt5Gui.dll DESTINATION ".")
		install(FILES ${QT_BINARY_DIR}/Qt5OpenGL.dll DESTINATION ".")
		install(FILES ${QT_BINARY_DIR}/Qt5Widgets.dll DESTINATION ".")
		install(FILES ${QT_BINARY_DIR}/Qt5Multimedia.dll DESTINATION ".")
		install(FILES ${QT_BINARY_DIR}/Qt5Network.dll DESTINATION ".")
		if (NOT MSYS2_BUILD)
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "icudt*.dll")
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "icuin*.dll")
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "icuuc*.dll")
		else()
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libicudt*.dll" PATTERN "libicudtd*.dll" EXCLUDE)
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libicuin*.dll" PATTERN "libicuind*.dll" EXCLUDE)
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libicuuc*.dll" PATTERN "libicuucd*.dll" EXCLUDE)
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libbz2-*.dll")
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libfreetype-*.dll")
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libglib*.dll")
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libgraphite2*.dll")
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libharfbuzz-*.dll" PATTERN "libharfbuzz-gobject*.dll" EXCLUDE PATTERN "libharfbuzz-icu*.dll" EXCLUDE)
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libpcre16*.dll" PATTERN "libpcre-*.dll")
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libiconv*.dll")
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libintl*.dll")
			install(DIRECTORY ${QT_BINARY_DIR}/ DESTINATION "." FILES_MATCHING PATTERN "libpng*.dll")
		endif()
		install(FILES ${QT_PLUGINS_DIR}/platforms/qwindows.dll DESTINATION "platforms")
	else()
		install(FILES ${QT_BINARY_DIR}/QtCore4.dll DESTINATION ".")
		install(FILES ${QT_BINARY_DIR}/QtGui4.dll DESTINATION ".")
		install(FILES ${QT_BINARY_DIR}/QtOpenGL4.dll DESTINATION ".")
		if (QT_QTMULTIMEDIA_FOUND)
			install(FILES ${QT_BINARY_DIR}/QtMultimedia4.dll DESTINATION ".")        
		endif()
	endif()

	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../AUTHORS    DESTINATION "." RENAME AUTHORS.txt)
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../ChangeLog  DESTINATION "." RENAME ChangeLog.txt)
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../COPYING    DESTINATION "." RENAME COPYING.txt)
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../../win_template/readme.txt     DESTINATION "." RENAME README.txt)
	#install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../README     DESTINATION "." RENAME README.txt)
	#install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../../README.WIN DESTINATION "." RENAME README.WIN.txt)
	install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/donate.png DESTINATION "." )
	
	if (MINGW)
		get_filename_component( Mingw_Path ${CMAKE_CXX_COMPILER} PATH )
		if("${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "x86_64" OR "${CMAKE_SYSTEM_PROCESSOR}" STREQUAL "AMD64")
			install(DIRECTORY ${Mingw_Path}/
				DESTINATION "."
				FILES_MATCHING PATTERN "libgcc_s_*.dll" PATTERN "libstdc++-*.dll" PATTERN "libwinpthread-*.dll")
		else()
			install(DIRECTORY ${Mingw_Path}/
				DESTINATION "."
				FILES_MATCHING PATTERN "libgcc_s_*.dll" PATTERN "mingwm10.dll")
		endif()
	endif ()

	if (YAB_USE_SSF AND ZLIB_FOUND)
		if (NOT MSYS2_BUILD)
			install(FILES ${ZLIB_INCLUDE_DIRS}/../zlib1.dll DESTINATION ".")
		else()
			install(FILES ${QT_BINARY_DIR}/zlib1.dll DESTINATION ".")
		endif()
	endif()
	
  if (MSVC)    
    set (CMAKE_EXE_LINKER_FLAGS /SAFESEH:NO )
	endif (MSVC)
	
else ()
	install(TARGETS yabause-qt DESTINATION "bin")
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${YAB_PORT_NAME}.desktop DESTINATION "share/applications")
	install(FILES "doc/yabause.1" DESTINATION "${YAB_MAN_DIR}/man1" RENAME "${YAB_PORT_NAME}.1")
	install(FILES "resources/icons/yabause.png" DESTINATION "share/pixmaps")
endif ()
