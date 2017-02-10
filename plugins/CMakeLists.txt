add_library(repo-aptrpm SHARED repo-aptrpm.c)
target_link_libraries(repo-aptrpm
	libmicrodnf
)
install(TARGETS repo-aptrpm LIBRARY DESTINATION ${PKG_PLUGINDIR})

add_library(transport-curl SHARED transport-curl.c)
target_link_libraries(transport-curl
	libmicrodnf
)
install(TARGETS transport-curl LIBRARY DESTINATION ${PKG_PLUGINDIR})
