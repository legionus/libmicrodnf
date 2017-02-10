set(name "microdnf")
set(libname "lib${name}")

set(SOURCES
	init.c
	repo.c
	loader.c
	plugin.c
)

set(HEADERS
	libmicrodnf.h
)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LINK_FLAGS} -Wl,--version-script=${CMAKE_SOURCE_DIR}/src/${libname}.ver")

add_library(${libname} SHARED ${SOURCES})

set_target_properties(${libname} PROPERTIES OUTPUT_NAME "${name}")
set_target_properties(${libname} PROPERTIES SOVERSION "0")
target_link_libraries(${libname} ${GLIB2_LIBRARIES} ${GMODULE2_LIBRARIES})

install(FILES ${HEADERS} DESTINATION "${INCLUDE_INSTALL_DIR}/${libname}")
install(TARGETS ${libname} LIBRARY DESTINATION ${LIB_INSTALL_DIR} ARCHIVE DESTINATION ${LIB_INSTALL_DIR})
