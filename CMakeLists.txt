project(libmicrodnf C)
cmake_minimum_required(VERSION 2.6)

include(CheckCCompilerFlag)
include(GNUInstallDirs)

include(${CMAKE_SOURCE_DIR}/VERSION.cmake)
set(VERSION "${LIBREPO_MAJOR}.${LIBREPO_MINOR}.${LIBREPO_PATCH}")

set(CMAKE_C_FLAGS       "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -std=c99 -Wall -Wextra -ggdb -O0 -DDEBUG")

# Find necessare libraries
find_package(PkgConfig)

pkg_check_modules(GLIB2 glib-2.0 REQUIRED)
pkg_check_modules(GMODULE2 gmodule-2.0 REQUIRED)

set(PKG_LIBDIR ${CMAKE_INSTALL_FULL_LIBDIR}/libmicrodnf)
set(PKG_PLUGINDIR ${CMAKE_INSTALL_FULL_LIBDIR}/libmicrodnf/plugins)
set(PKG_DATADIR ${CMAKE_INSTALL_FULL_DATADIR}/libmicrodnf)
add_definitions(-DPACKAGE_LIBDIR="${PKG_LIBDIR}")
add_definitions(-DPACKAGE_DATADIR="${PKG_DATADIR}")

# Set libmicrodnf log domain
add_definitions( -DG_LOG_DOMAIN="libmicrodnf" )

# Enable large file support
add_definitions(-D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE)

# Add include dirs
include_directories(${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src)
include_directories(${GLIB2_INCLUDE_DIRS} ${GMODULE2_INCLUDE_DIRS})

if(NOT LIB_INSTALL_DIR)
	set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/usr/lib")
endif(NOT LIB_INSTALL_DIR)

if(NOT INCLUDE_INSTALL_DIR)
	set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/usr/include")
endif(NOT INCLUDE_INSTALL_DIR)

# Subdirs
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(plugins)
