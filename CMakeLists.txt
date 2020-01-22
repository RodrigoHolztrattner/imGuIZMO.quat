cmake_minimum_required(VERSION 3.1.1 FATAL_ERROR)

############
# INCLUDES #
############
include(FetchContent)

if(WIN32)
	# Resource VersionInfo
	set(PROJECT_PRODUCT_NAME "imGuIZMO.quat")
endif()

################
# DEPENDENCIES #
################

macro(PrintFetchMessage target_string)
	string(CONCAT end_string "Fetching " ${target_string})
	message(STATUS "")
	message(STATUS "################################")
	message(STATUS "# ${end_string}")
	message(STATUS "################################")
	message(STATUS "")
endmacro()

##########
# CONFIG #
##########

set(PROJECT_NAME "imGuIZMO.quat")
project(${PROJECT_NAME} VERSION 1.0.0 DESCRIPTION "blob")

###########
# PROJECT #
###########

SET(CMAKE_CXX_FLAGS "/Zi /sdl /MP /Oi /Gy /permissive- /GR- /TP /EHsc")
SET(CMAKE_CXX_FLAGS_DEBUG "/ZI /sdl /MP /JMC /permissive- /GR- /TP /EHsc /MDd /Od")

add_library(${PROJECT_NAME} STATIC
  imGuIZMO.quat/vgMath.h
  imGuIZMO.quat/vGizmoMath
  imGuIZMO.quat/vGizmo.h
  imGuIZMO.quat/vgConfig.h
  imGuIZMO.quat/imGuIZMOquat.h
  imGuIZMO.quat/imGuIZMOquat.cpp)

###########
# INSTALL #
###########

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT library)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON)    
	

add_definitions(-DUNICODE 
	-D_UNICODE)