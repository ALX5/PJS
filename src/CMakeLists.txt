cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(PJS)

SET(CMAKE_BUILD_TYPE Debug CACHE STRING "default to debug" FORCE)

########################################### OPENNI ################################################
    
    	find_package(PkgConfig)
    	if(${CMAKE_VERSION} VERSION_LESS 2.8.2)
    	  pkg_check_modules(PC_OPENNI openni-dev)
    	else()
    	  pkg_check_modules(PC_OPENNI QUIET openni-dev)
    	endif()
     
    	set(OPENNI_DEFINITIONS ${PC_OPENNI_CFLAGS_OTHER})
     
    	#add a hint so that it can find it without the pkg-config
    	find_path(OPENNI_INCLUDE_DIR XnStatus.h
    		HINTS ${NESTK_ROOT_DIRS_HINTS} ${PC_OPENNI_INCLUDEDIR} ${PC_OPENNI_INCLUDE_DIRS} /usr/include/openni /usr/include/ni
    	        PATHS "$ENV{PROGRAMFILES}/OpenNI/Include" "$ENV{PROGRAMW6432}/OpenNI/Include"
    	        PATH_SUFFIXES openni)
    	find_path(NITE_INCLUDE_DIR XnVSessionManager.h
        	HINTS ${NESTK_ROOT_DIRS_HINTS} ${PC_OPENNI_INCLUDEDIR} ${PC_OPENNI_INCLUDE_DIRS} /usr/include/openni /usr/include/nite
                PATHS "$ENV{PROGRAMFILES}/PrimeSense/NITE/Include" "$ENV{PROGRAMW6432}/PrimeSense/NITE/Include"
                PATH_SUFFIXES openni)

    	#add a hint so that it can find it without the pkg-config
    	find_library(OPENNI_LIBRARY
    	  	NAMES OpenNI64 OpenNI
    	        HINTS ${NESTK_ROOT_DIRS_HINTS} ${PC_OPENNI_LIBDIR} ${PC_OPENNI_LIBRARY_DIRS} /usr/lib
    	        PATHS "$ENV{PROGRAMFILES}/OpenNI/Lib${OPENNI_SUFFIX}" "$ENV{PROGRAMW6432}/OpenNI/Lib${OPENNI_SUFFIX}"
    	        PATH_SUFFIXES lib)
    	find_library(NITE_LIBRARY
                NAMES XnVNite XnVNITE_1_3_1 XnVNITE_1_4_0 XnVNite_1_4_2 XnVNite_1_5_2
                HINTS ${NESTK_ROOT_DIRS_HINTS} ${PC_OPENNI_LIBDIR} ${PC_OPENNI_LIBRARY_DIRS} /usr/lib
                PATHS "$ENV{PROGRAMFILES}/PrimeSense/NITE/Lib${OPENNI_SUFFIX}" "$ENV{PROGRAMW6432}/PrimeSense/NITE/Lib${OPENNI_SUFFIX}"
                PATH_SUFFIXES lib)
     
    	set(OPENNI_INCLUDE_DIRS ${OPENNI_INCLUDE_DIR} ${NITE_INCLUDE_DIR})
    	if(APPLE)
      		set(OPENNI_LIBRARIES ${OPENNI_LIBRARY} ${NITE_LIBRARY} usb)
    	else()
      		set(OPENNI_LIBRARIES ${OPENNI_LIBRARY} ${NITE_LIBRARY})
    	endif()
     
    	include(FindPackageHandleStandardArgs)
    	find_package_handle_standard_args(OpenNI DEFAULT_MSGOPENNI_LIBRARY OPENNI_INCLUDE_DIR)
     
    	mark_as_advanced(OPENNI_LIBRARY OPENNI_INCLUDE_DIR)
    	if(OPENNI_FOUND)
      		include_directories(${OPENNI_INCLUDE_DIRS})
      		link_directories(${OPENNI_LIBRARY})
      		add_definitions(${OPENNI_DEFINITIONS})
      		message(STATUS "OpenNI found (include: ${OPENNI_INCLUDE_DIR}, lib: ${OPENNI_LIBRARY})")
        endif(OPENNI_FOUND)

############################################## PCL ##################################################

        find_package(PCL 1.3 REQUIRED COMPONENTS common io)
        include_directories(${PCL_INCLUDE_DIRS})
        link_directories(${PCL_LIBRARY_DIRS})
        add_definitions(${PCL_DEFINITIONS})

############################################# OpenGL ################################################

   	# FIND GLUT
   	find_package(GLUT REQUIRED)
   	include_directories(${GLUT_INCLUDE_DIRS})
	link_directories(${GLUT_LIBRARY_DIRS})
   	add_definitions(${GLUT_DEFINITIONS})
   	if(NOT GLUT_FOUND)
       		message(ERROR " GLUT not found!")
   	endif(NOT GLUT_FOUND)

   	# FIND OPENGL
        find_package(OpenGL REQUIRED)
        include_directories(${OpenGL_INCLUDE_DIRS})
        link_directories(${OpenGL_LIBRARY_DIRS})
        add_definitions(${OpenGL_DEFINITIONS})
        if(NOT OPENGL_FOUND)
                message(ERROR " OPENGL not found!")
        endif(NOT OPENGL_FOUND)

############################################# Boost ################################################

        set(BOOST_ROOT D:/boost_1_53_0)
        FIND_PACKAGE( Boost COMPONENTS program_options REQUIRED )
        INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
        link_directories(${Boost_LIBRARY_DIRS})
        add_definitions(${Boost_DEFINITIONS})


############################################# OpenCV ################################################  

    	include_directories(${PROJECT_SOURCE_DIR}/Calibration)
    	include_directories(${PROJECT_SOURCE_DIR}/Distortion)
    	include_directories(${PROJECT_SOURCE_DIR}/Tracking)
    	include_directories(${PROJECT_SOURCE_DIR}/Environment)
		include_directories(${PROJECT_SOURCE_DIR}/Tests)

add_executable (PJS

		Calibration/Calibration.h Calibration/Calibration.cpp
		Calibration/Calib.cpp Calibration/Calib.h
                Distortion/Plane.cpp
                Distortion/Plane2d.cpp
                Distortion/Plane3d.cpp
		Distortion/TestPlanes.cpp
		Distortion/Utils.cpp
		Distortion/Surface.cpp

		Environment/Projection.cpp
		Environment/UserPlane.cpp
		Environment/User.cpp
		Environment/TestProjection.cpp
                Environment/GeometryUtils.cpp
		
		Tests/PlaneTests.cpp
		Tests/AffineTests.cpp
		Tests/X11Tests.cpp
		Tests/DummyTracker.cpp
		Tests/Visualizer.cpp
		Tests/PeriodicVisualizer.cpp
		Tests/RealTimeVisualizer.cpp

		Tracking/Tracking.cpp Tracking/Tracking.h
		EventHandler.cpp
		Main.cpp Main.h)
     
	find_package( OpenCV REQUIRED )


target_link_libraries (PJS ${OPENNI_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${OpenCV_LIBS}  ${PCL_COMMON_LIBRARIES} ${PCL_IO_LIBRARIES})#${Boost_LIBRARIES}

